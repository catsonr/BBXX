#ifndef FILESYSTEMSTATE_H
#define FILESYSTEMSTATE_H

#include <SDL3/SDL.h>

#include <efsw/efsw.hpp>

#include <stdio.h>
#include <string>
#include <fstream>
#include <sstream>
#include <functional>
#include <filesystem>
namespace fs = std::filesystem;


/*
    LiveFiles are files that BBXX watches for changes
    if a change to the file in 'path' is detected, 'callback' is ran
*/
struct LiveFile
{
    /* CONSTRUCTORS */

    LiveFile() = delete;
    LiveFile(fs::path path, std::function<void()> callback) :
        path(std::move(path)),
        callback(std::move(callback))
    {}

    /* PUBLIC MEMBERS */

    fs::path path;
    std::function<void()> callback;
};

struct FileSystemState; // forward declare

/*
   BBXX uses efsw as a simple file watcher
   the AssetsListener::handleFileAction is (basically) a callback for any changes that happen in 'assets/'
*/
class AssetsListener : public efsw::FileWatchListener
{
private:
    FileSystemState& filesystemstate;

public:
    /* CONSTRUCTORS */
    AssetsListener() = delete;
    AssetsListener(FileSystemState& filesystemstate) : filesystemstate(filesystemstate) {}

    void handleFileAction(efsw::WatchID watchid, const std::string& dir, const std::string& filename, efsw::Action action, std::string oldFilename) override;
};

struct FileSystemState
{
    /* CONSTRUCTORS */
    
    FileSystemState() : assetslistener(*this) {}

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
    
    bool init();
    /* returns the content of a assets file */
    std::string read_file(const fs::path& path) const;
    /*
        returns the absolute path to a file in the assets folder
        e.g.:
            if you have some 'assets/shaders/shader.glsl'
            call get_path("shaders/shader.glsl")
                -> returns "/Users/user/path/to/assets/shaders/shader.glsl"
    */
    fs::path get_path(const char* path) const;
    fs::path get_path(const fs::path& path) const;
    /*
        adds a LiveFile to be watched, if it isn't already
        a LiveFile is simply a path to a file, and a callback to be ran when it is modified
    */
    void watch_file(LiveFile livefile);
    /* returns true if filesystemstate is watching for changes in given file, returns false otherwise */
    bool watching_file(fs::path path) const;
    void handle_file_change(fs::path path);
    void cleanup();

private:
    
    /* PRIVATE MEMBERS */
    
    /*
        whether or not BBXX listens for any file changes in assets/
        note that this will always be disabled for web builds, no matter the value of live
    */
    bool live { true };
    std::vector<LiveFile> live_files;
    
    /* EFSW stuff */
    efsw::FileWatcher filewatcher;
    AssetsListener assetslistener;
    efsw::WatchID assets_watchID;
}; // FileSystemState


#endif // FILESYSTEM_H