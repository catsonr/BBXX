# architecture

the **BBXX** game engine is a single class (see `BBXX.h`) composed of many smaller *state* managing classes. these classes can all be found within `/include/BBXX`

based off of these state classes are *implementation* classes, which are classes that a developer using BBXX would be interfacing with. these are located in `/include/BEATBOXX`

for example, an important state class is `GLState`, which contains all the data and functions required to draw to the screen with OpenGL. GLState also contains a list of `ShaderProgram`, and each ShaderProgram contains a list of `Uniform`. These are examples of implementation classes. A game developer would be expected to define a shader program and its uniforms, but would need not worry how the shader program is being ran. `BBXX/` is the game engine, and `BEATBOXX/` is how you interact with it

also inside `BEATBOXX/` is `BXCTX.h`, aka "bbxx context". this single struct contains references to all state classes, allowing access to the entirety of the engine. each subclass of `Screen` inherits a reference to BXCTX

## the Screen class

`Screen` (see `include/BEATBOXX/ScreenState/Screen.h`) is the main entrypoint to BBXX, and allows you to easily define what is drawn, where to draw it, and in what order relative to all other screens.

below is an example Screen implmentation, which shows a basic demo of how to attach a shader and its uniforms

``` c++
#include <BBXX/BBXX.h>

struct MyScreen : public Screen
{
    float t { 0.0f };
    glm::mat4 model { 1.0f };

    bool init() override
    {
        // attach new shader program
        // this will be drawn every frame
        bxctx.glstate.shaderprograms.emplace_back(
            "shaders/myawesomeshader.vert",
            "shaders/myawesomeshader.frag" 
        );
        
        ShaderProgram& myawesomeshader = bxctx.glstate.back();
        
        // initialize shader program
        myawesomeshader.init(bxctx.filesystemstate);
        
        // attach uniforms
        myawesomeshader.uniform_attach("u_mVP", &bxctx.glstate.m_VP); // use gloabl view-projection matrix
        myawesomeshader.uniform_attach("u_mVP", &model); // use local model matrix
        myawesomeshader.uniform_attach("u_t", &t); // use local variable t
    }
    
    void iterate() override
    {
        t += 0.1;
    }

};
```
