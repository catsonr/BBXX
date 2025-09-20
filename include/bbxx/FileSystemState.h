#ifndef FILESYSTEMSTATE_H
#define FILESYSTEMSTATE_H

#include <SDL3/SDL.h>

#include <fstream>
#include <sstream>
#include <filesystem>
namespace fs = std::filesystem;

#include <string>

struct FileSystemState
{
    /* PUBLIC MEMBERS */
    
    /* the absolute path where BBXX is run from */
    fs::path base_path { SDL_GetBasePath() };
    /* the location of the assets folder, relative to base_path */
/*
    these macros are just a development nicety, and i should really find a
    better solution. in full production this would not be neccessary--only
    the "assets" one is needed--but cmake puts everything in build (and vs code cmaketools puts it in build/Debug)
*/
#ifndef __EMSCRIPTEN__
    fs::path assets_dir { "../examples/minimal/assets" };
#else
    fs::path assets_dir { "assets" };
#endif
    /*
        the absolute path to the actual assets folder on disk
        this is calculated at init() time using base_path / assets_dir
        BBXX treats this as the root of the file system; all file access
        functions are relative to this path
    */
    fs::path assets_path;

    /* PUBLIC METHODS */
    
    std::string read_file(const fs::path& path);

    bool init();
}; // FileSystemState

#endif // FILESYSTEM_H