/*
    super simple platform agnostic gl header include
    if you ever need opengl functions, just do:
    #include <BBXX/gl.h>
*/

#ifndef BBXX_GL_H
#define BBXX_GL_H

#ifndef __EMSCRIPTEN__
#include <glad/gl.h>
#else
#include <GLES3/gl3.h>
#endif

#endif // BBXX_GL_H