#ifndef SHADERPROGRAM_H
#define SHADERPROGRAM_H

#include <BBXX/FileSystemState.h>

#include <BBXX/gl.h>

#include <glm/glm.hpp>

#include <vector>

const std::vector<float> unit_quad {
    -1.0, -1.0, 0.0,
    -1.0,  1.0, 0.0,
     1.0,  1.0, 0.0,
     1.0,  1.0, 0.0,
    -1.0, -1.0, 0.0,
     1.0, -1.0, 0.0,
};
const int stride = 3;

struct ShaderProgram
{
    /* PUBLIC MEMBERS */

    GLuint program { 0 };
    GLuint vao, vbo;

    /* PUBLIC METHODS */
    bool init(const FileSystemState& filesystemstate, const fs::path& vertex_shader_path, const fs::path& fragment_shader_path);
    void draw();
    
    /* 
       sets the given shader source code to have the correct version header, depending on platform target
       all shaders are assumed to start with:
           #version 330 core

       if runnning on web, the header will be replaced with:
           #version 300 es
           precision highp float;
    */
    std::string fix_headers(std::string& SHADERSOURCECODE);
    /*
        returns the shader GLuint on success, and GL_FALSE on failure
        if there was an error compiling, error message will be printed
    */
    GLuint compile_shader(GLenum type, const char* SHADERSOURCECODE);
    /*
        creates a shader program given the vertex and fragment source code
        returns the program GLuint on success, and GL_FALSE on failure
    */
    GLuint create_program(const char* VERTEX_SOURCECODE, const char* FRAGMENT_SOURCECODE);
    
    //bool set_uniform(const char* name, bool value);
    bool set_uniform(const char* name, int value);
    bool set_uniform(const char* name, float value);
    bool set_uniform(const char* name, glm::vec2 value);
    bool set_uniform(const char* name, glm::vec3 value);
    bool set_uniform(const char* name, glm::vec4 value);
    bool set_uniform(const char* name, glm::mat4& value);
}; // ShaderProgram

#endif // SHADERPROGRAM_H