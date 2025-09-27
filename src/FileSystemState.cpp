#include <BBXX/FileSystemState.h>

bool FileSystemState::init()
{
    assets_path = base_path / assets_dir;

    if( !fs::exists(assets_path) ) {
        printf("[FileSystemState::init] could not find assets folder at '%s'! (does it exist?)\n", assets_path.string().c_str());
        return false;
    }
    
#ifndef __EMSCRIPTEN__
    if( live ) {
        assets_watchID = filewatcher.addWatch(assets_path.string(), &assetslistener, true);
        filewatcher.watch();
    }
#endif
    
    return true;
}

std::string FileSystemState::read_file(const fs::path& path) const
{
    fs::path full_path = get_path(path);

    std::ifstream in(full_path, std::ios::in);
    if( !in ) {
        // TODO: better error handling
        printf("[FileSystemState::read_file] failed to read file at '%s' (does it exist?). treating file as empty ...\n", full_path.c_str());
        return "";
    }
    
    std::ostringstream ss;
    ss << in.rdbuf();
    return ss.str();
}

fs::path FileSystemState::get_path(const char* path) const
{
    return fs::absolute( assets_path / path );
}
fs::path FileSystemState::get_path(const fs::path& path) const
{
    return fs::absolute( assets_path / path );
}

void FileSystemState::watch_file(LiveFile livefile)
{
    if( !live ) return;
    
    livefile.path = get_path(livefile.path); // convert relative assets path to absolute path

    if( !fs::exists(livefile.path) ) {
        printf("[FileSystemState::watch_file] '%s' does not exist! ignoring file watch request ...\n", livefile.path.c_str());
        return;
    }

    if( !watching_file(livefile.path) ) {
        printf("[FileSystemState::watch_file] BBXX now watching '%s' for changes!\n", livefile.path.c_str());
        live_files.push_back(std::move(livefile));
    }
}

bool FileSystemState::watching_file(fs::path path) const
{
    if( !live ) return false;
    
    path = get_path(path); // convert relative assets path to absolute path

    if( !fs::exists(path) ) return false;
    
    for( const LiveFile& livefile : live_files )
        if( fs::equivalent(livefile.path, path) ) return true;

    return false;
}

void FileSystemState::handle_file_change(fs::path path)
{
    //printf("[FileSystemState::handle_file_change] for '%s' ...\n", path.c_str());

    for( LiveFile& livefile : live_files )
    {
        if( fs::equivalent(livefile.path, path) )
            livefile.callback();
    }
}


void FileSystemState::cleanup()
{
    filewatcher.removeWatch(assets_watchID);
}




void AssetsListener::handleFileAction(efsw::WatchID watchid, const std::string& dir, const std::string& filename, efsw::Action action, std::string oldFilename)
{
    switch( action )
    {
        case efsw::Actions::Add:
            //printf("[AssetsListener::handleFileAction] ADDED\n\t%s%s\n", dir.c_str(), filename.c_str());
            break;
        case efsw::Actions::Delete:
            //printf("[AssetsListener::handleFileAction] DELETED\n\t%s%s\n", dir.c_str(), filename.c_str());
            break;
        case efsw::Actions::Modified:
            //printf("[AssetsListener::handleFileAction] MODIFIED\n\t%s%s\n", dir.c_str(), filename.c_str());
            filesystemstate.handle_file_change(fs::path(dir) / filename);
            break;
        case efsw::Actions::Moved:
            //printf("[AssetsListener::handleFileAction] RENAMED\n\t%s%s\n", dir.c_str(), filename.c_str());
            break;
    }
}