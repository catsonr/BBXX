#ifndef FILESYSTEMSTATE_H
#define FILESYSTEMSTATE_H

#include <SDL3/SDL.h>

#include <efsw/efsw.hpp>

#include <stdio.h>
#include <string>
#include <fstream>
#include <sstream>
#include <filesystem>
namespace fs = std::filesystem;

/*
   BBXX uses efsw as a simple file watcher
   the AssetsListener::handleFileAction is (basically) a callback for any changes that happen in 'assets/'
*/
class AssetsListener : public efsw::FileWatchListener
{
public:
    void handleFileAction(efsw::WatchID watchid, const std::string& dir,
                          const std::string& filename, efsw::Action action,
                          std::string oldFilename) override
   {
       switch( action )
       {
            case efsw::Actions::Add:
                printf("[AssetsListener::handleFileAction] ADDED\n\t%s%s\n", dir.c_str(), filename.c_str());
                break;
            case efsw::Actions::Delete:
                printf("[AssetsListener::handleFileAction] DELETED\n\t%s%s\n", dir.c_str(), filename.c_str());
                break;
            case efsw::Actions::Modified:
                printf("[AssetsListener::handleFileAction] MODIFIED\n\t%s%s\n", dir.c_str(), filename.c_str());
                break;
            case efsw::Actions::Moved:
                printf("[AssetsListener::handleFileAction] RENAMED\n\t%s%s\n", dir.c_str(), filename.c_str());
                break;
       }
   }
};

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
    
    /* whether or not BBXX listens for any file changes in assets/ */
    bool live { true };

    /* PUBLIC METHODS */
    
    bool init();
    std::string read_file(const fs::path& path);
    void cleanup();

    /* EFSW stuff */
private:
    efsw::FileWatcher filewatcher;
    AssetsListener assetslistener;
    efsw::WatchID assets_watchID;
}; // FileSystemState

#endif // FILESYSTEM_H