#ifndef UNIFORM_H
#define UNIFORM_H

template <typename T>

struct Uniform
{
    /* CONSTRUCTORS */

    Uniform() = delete;
    Uniform(const char* name, T value) :
        name(name),
        value(value)
    {}

    /* PUBLIC MEMBERS */
    
    const char* name;
    T value;

}; // Uniform

#endif // UNIFORM_H