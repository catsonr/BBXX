# BBXX GAME ENGINE

**BBXX** is a cross-platform game engine, written in c++

see **https://github.com/catsonr/beatboxx** for version 1.0

## install

`git clone --recurse-submodules https://github.com/catsonr/bbxx/`

(this may take a while due to submodules)

## compiling

**BBXX** is cross platform, meaning it work on window, macos, linux, and your favorite *web browser*.

compiling for desktop is easier than compiling for web, but both targets are considered first class
citizens and will function (almost) exactly the same

### compile (for desktop)

simply compile with cmake

`cd bbxx`

`cmake -B build`

`cmake --build build`

### compiling (for web)

to compile for web you will first need to install and setup emscripten. don't worry, it's not that much work

you can either follow the commands listed below or [in the emscripten docs](https://emscripten.org/docs/getting_started/downloads.html).

`git clone https://github.com/emscripten-core/emsdk.git`

`cd emsdk`

`./emsdk install latest`

`./emsdk activate latest`

emscripten is now installed. it will need to be sourced any time before compiling for web.
in the project root, perform the following commands

`source ./emsdk/emsdk_env.sh`

now you can compile like normal! (but note the *emcmake* command)

`emcmake cmake -B build`

`cmake --build build`

## run BBXX

cmake will automatically compile all example projects in `examples/`

you can run the miminal example with:

`./build/minimal`

or if compiled with emscripten, `emrun build/minimal`
