#ifndef UNIFORM_H
#define UNIFORM_H

#include <BBXX/gl.h>

#include <glm/glm.hpp>

//using UniformType = std::variant<int, float, glm::vec2, glm::vec3, glm::vec4, glm::mat4>;

struct Uniform
{
    /* CONSTRUCTORS */

    Uniform() = delete;
    Uniform(const char* name, GLenum gl_type, GLint location) :
        name(name),
        gl_type(gl_type),
        location(location)
    {}

    /* PUBLIC MEMBERS */
    
    std::string name;
    const void* value { nullptr };
    
    GLenum gl_type;
    GLint location;

}; // Uniform

#endif // UNIFORM_H