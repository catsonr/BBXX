#include <BEATBOXX/GLState/ShaderProgram.h>

#include <glm/gtc/type_ptr.hpp>

#include <stdio.h>

bool ShaderProgram::init(FileSystemState& filesystemstate)
{
    const fs::path vertex_shader_path   = filesystemstate.get_path(vertex_assets_path);
    const fs::path fragment_shader_path = filesystemstate.get_path(fragment_assets_path);

    std::string vertex_src   = filesystemstate.read_file(vertex_shader_path).c_str();
    std::string fragment_src = filesystemstate.read_file(fragment_shader_path).c_str();
    
    vertex_src = fix_headers(vertex_src);
    fragment_src = fix_headers(fragment_src);
    
    program = create_program(vertex_src.c_str(), fragment_src.c_str());
    if( program == GL_FALSE) {
        printf("[ShaderProgram::init] failed to initialize!\n");
        return false;
    }
    
    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);
    
    glGenBuffers(1, &vbo);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, unit_quad.size() * sizeof(float), unit_quad.data(), GL_STATIC_DRAW);
    
    glEnableVertexAttribArray(0); // a_pos assumed to be at location = 0
    glVertexAttribPointer(0, stride, GL_FLOAT, GL_FALSE, stride * sizeof(float), (void*)0);
    
    glBindVertexArray(0);
    
    LiveFile fragmentshader_livefile {
        fragment_shader_path,
        [this]() {
            printf("fragment shader changed!!! requesting reload ...\n");
            this->request_reload();
        }
    };
    
    if( !filesystemstate.watching_file(fragment_shader_path) )
        filesystemstate.watch_file(fragmentshader_livefile);
    
    source_uniforms();
    
    return true;
}

void ShaderProgram::request_reload()
{
    reload_requested = true;
}

bool ShaderProgram::reload(const FileSystemState& filesystemstate)
{
    reload_requested = false;

    const fs::path vertex_shader_path   = filesystemstate.get_path(vertex_assets_path);
    const fs::path fragment_shader_path = filesystemstate.get_path(fragment_assets_path);
    
    std::string vertex_src   = filesystemstate.read_file(vertex_shader_path).c_str();
    std::string fragment_src = filesystemstate.read_file(fragment_shader_path).c_str();
    
    vertex_src   = fix_headers(vertex_src);
    fragment_src = fix_headers(fragment_src);
    
    GLuint new_program = create_program(vertex_src.c_str(), fragment_src.c_str());
    if( new_program == GL_FALSE) {
        printf("[ShaderProgram::reload] failed to reload!\n");
        return false;
    }
    
    printf("[ShaderProgram::reload] reloaded!\n");
    
    glDeleteProgram(program);
    program = new_program;
    
    source_uniforms();

    return true;
}

void ShaderProgram::draw()
{
    glUseProgram(program);
    glBindVertexArray(vao);
    
    glDrawArrays(GL_TRIANGLES, 0, unit_quad.size() / stride);
}

std::string ShaderProgram::fix_headers(std::string& SHADERSOURCECODE)
{
#ifdef __EMSCRIPTEN__
    const std::string old_header = "#version 330 core";
    const std::string new_header = "#version 300 es\nprecision highp float;";
    size_t pos = SHADERSOURCECODE.find(old_header);
    if( pos != std::string::npos ) {
        SHADERSOURCECODE.replace(pos, old_header.size(), new_header);
    }
#endif
    
    return SHADERSOURCECODE;
}

GLuint ShaderProgram::compile_shader(GLenum type, const char* SHADERSOURCECODE)
{
    GLuint shader = glCreateShader(type);
    glShaderSource(shader, 1, &SHADERSOURCECODE, NULL);
    glCompileShader(shader);
    GLint success;
    glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
    if( !success ) {
        char log[512];
        glGetShaderInfoLog(shader, 512, NULL, log);
        printf("[ShaderProgram::compile_shader] failed to compile shader!\n<ERROR MESSAGE>\n%s\n<ERROR MESSAGE END>\n", log);
        
        glDeleteShader(shader);
        return GL_FALSE;
    }
    
    return shader;
}

GLuint ShaderProgram::create_program(const char* VERTEX_SOURCECODE, const char* FRAGMENT_SOURCECODE)
{
    GLuint vertex = compile_shader(GL_VERTEX_SHADER, VERTEX_SOURCECODE);
    if ( vertex == GL_FALSE ) {
        printf("[ShaderProgram::create_program] failed to compile vertex shader!\n");
        return GL_FALSE;
    }

    GLuint fragment = compile_shader(GL_FRAGMENT_SHADER, FRAGMENT_SOURCECODE);
    if ( fragment == GL_FALSE ) {
        printf("[ShaderProgram::create_program] failed to compile fragment shader!\n");
        return GL_FALSE;
    }
    
    GLuint program = glCreateProgram();
    glAttachShader(program, vertex);
    glAttachShader(program, fragment);
    glLinkProgram(program);
    
    GLint success;
    glGetProgramiv(program, GL_LINK_STATUS, &success);
    if( success == GL_FALSE ) {
        char log[512];
        glGetProgramInfoLog(program, 512, NULL, log);
        printf("[ShaderProgram::create_program] failed to link program to shaders:\n<ERROR MESSAGE>\n%s\n<ERROR MESSAGE END>\n", log);
        
        return GL_FALSE;
    }
    
    glDeleteShader(vertex);
    glDeleteShader(fragment);
    
    return program;
}

void ShaderProgram::source_uniforms()
{
    printf("[ShaderProgram::source_uniforms] sourcing uniforms ...\n");

    GLint count;
    glGetProgramiv(program, GL_ACTIVE_UNIFORMS, &count);
    for( int i = 0; i < count; i++ )
    {
        char name[512];
        GLenum type;
        glGetActiveUniform(program, (GLuint)i, 100, NULL, NULL, &type, name);
        
        if( uniform_name_is_unique(name) ) {
            printf("[ShaderProgram::source_uniforms] found '%s' of type %i\n", name, type);
            
            GLint location = glGetUniformLocation(program, name);
            if( location != -1 )
                uniforms.push_back({name, type, location});
            else
                printf("[ShaderProgram::source_uniforms] unable to find location for uniform '%s'! ignorning ...\n", name);
        }
    }
}

void ShaderProgram::set_uniforms()
{
    //printf("[ShaderProgram::set_uniforms] setting uniforms ...\n");

    for( const Uniform& uniform : uniforms )
    {
        if( uniform.value != nullptr )
            set_uniform(uniform);
        else
            printf("[ShaderProgram::set_uniforms] cannot set unattached uniform '%s'! ignoring ...\n", uniform.name.c_str());
    }
}

bool ShaderProgram::uniform_name_is_unique(const char* name) const
{
    for( const Uniform& uniform : uniforms )
    {
        if( uniform.name == name ) return false;
    } 
    
    return true;
}

bool ShaderProgram::uniform_attach(const char* name, const void* ptr)
{
    for( Uniform& uniform : uniforms )
    {
        if( uniform.name == name )
        {
            uniform.value = ptr;
            
            printf("[ShaderProgram::uniform_attach] uniform '%s' attached!\n", name);
            return true;
        }
    }
    
    printf("[ShaderProgram::uniform_attach] could not attach; uniform '%s' is not being used!\n", name);
    return false;
}



bool ShaderProgram::set_uniform(const Uniform& uniform)
{
    if( uniform.value == nullptr ) {
        printf("[ShaderProgram::set_uniform] cannot set uniform '%s'. please attach a variable!\n", uniform.name.c_str());
        return false;
    }
    
    switch (uniform.gl_type)
    {
        case GL_INT:
        {
            const int* ptr = static_cast<const int*>(uniform.value);
            glUniform1i(uniform.location, *ptr);
            return true;
            break;
        }

        case GL_FLOAT:
        {
            const float* ptr = static_cast<const float*>(uniform.value);
            glUniform1f(uniform.location, *ptr);
            return true;
            break;
        }

        case GL_FLOAT_VEC2:
        {
            const glm::vec2* ptr = static_cast<const glm::vec2*>(uniform.value);
            glUniform2fv(uniform.location, 1, glm::value_ptr(*ptr));
            return true;
            break;
        }

        case GL_FLOAT_VEC3:
        {
            const glm::vec3* ptr = static_cast<const glm::vec3*>(uniform.value);
            glUniform3fv(uniform.location, 1, glm::value_ptr(*ptr));
            return true;
            break;
        }

        case GL_FLOAT_VEC4:
        {
            const glm::vec4* ptr = static_cast<const glm::vec4*>(uniform.value);
            glUniform4fv(uniform.location, 1, glm::value_ptr(*ptr));
            return true;
            break;
        }

        case GL_FLOAT_MAT2:
        {
            const glm::mat2* ptr = static_cast<const glm::mat2*>(uniform.value);
            glUniformMatrix2fv(uniform.location, 1, GL_FALSE, glm::value_ptr(*ptr));
            return true;
            break;
        }

        case GL_FLOAT_MAT3:
        {
            const glm::mat3* ptr = static_cast<const glm::mat3*>(uniform.value);
            glUniformMatrix3fv(uniform.location, 1, GL_FALSE, glm::value_ptr(*ptr));
            return true;
            break;
        }

        case GL_FLOAT_MAT4:
        {
            const glm::mat4* ptr = static_cast<const glm::mat4*>(uniform.value);
            glUniformMatrix4fv(uniform.location, 1, GL_FALSE, glm::value_ptr(*ptr));
            return true;
            break;
        }
    }

    printf("[ShaderProgram::set_uniform] uniform of type '%i' not supported!\n", uniform.gl_type);
    return false;
}

/*
bool ShaderProgram::set_uniform(const char* name, int value)
{
    glUseProgram(program);
    GLint location = glGetUniformLocation(program, name);
    if( location == -1 ) {
        //printf("[ShaderProgram::set_uniform] failed to find uniform int '%s'\n", name);
        return false;
    }

    glUniform1i(location, value);
    return true;
}

bool ShaderProgram::set_uniform(const char* name, float value)
{
    glUseProgram(program);
    GLint location = glGetUniformLocation(program, name);
    if( location == -1 ) {
        //printf("[ShaderProgram::set_uniform] failed to find uniform float '%s'\n", name);
        return false;
    }

    glUniform1f(location, value);
    return true;
}

bool ShaderProgram::set_uniform(const char* name, glm::vec2 vector)
{
    glUseProgram(program);
    GLint location = glGetUniformLocation(program, name);
    if( location == -1 ) {
        //printf("[ShaderProgram::set_uniform] failed to find uniform vec2 '%s'\n", name);
        return false;
    }

    glUniform2fv(location, 1, glm::value_ptr(vector));
    return true;
}

bool ShaderProgram::set_uniform(const char* name, glm::vec3 vector)
{
    glUseProgram(program);
    GLint location = glGetUniformLocation(program, name);
    if( location == -1 ) {
        //printf("[ShaderProgram::set_uniform] failed to find uniform vec3 '%s'\n", name);
        return false;
    }

    glUniform3fv(location, 1, glm::value_ptr(vector));
    return true;
}

bool ShaderProgram::set_uniform(const char* name, glm::vec4 vector)
{
    glUseProgram(program);
    GLint location = glGetUniformLocation(program, name);
    if( location == -1 ) {
        //printf("[ShaderProgram::set_uniform] failed to find uniform vec4 '%s'\n", name);
        return false;
    }

    glUniform4fv(location, 1, glm::value_ptr(vector));
    return true;
}

bool ShaderProgram::set_uniform(const char* name, glm::mat4& matrix)
{
    glUseProgram(program);
    GLint location = glGetUniformLocation(program, name);
    if( location == -1 ) {
        //printf("[ShaderProgram::set_uniform] failed to find uniform mat4 '%s'\n", name);
        return false;
    }

    glUniformMatrix4fv(location, 1, GL_FALSE, glm::value_ptr(matrix));
    return true;
}
*/