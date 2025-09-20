#include <BBXX/FileSystemState.h>

#include <stdio.h>

bool FileSystemState::init()
{
    assets_path = base_path / assets_dir;

    if( !fs::exists(assets_path) ) {
        printf("[FileSystemState::init] could not find assets folder at '%s'! (does it exist?)\n", assets_path.string().c_str());
        return false;
    }
    
    return true;
}

std::string FileSystemState::read_file(const fs::path& path)
{
    fs::path full_path = assets_path / path;

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