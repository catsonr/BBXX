#ifndef GLSTATE_H
#define GLSTATE_H

#include <BBXX/FileSystemState.h>

#include <BEATBOXX/GLState/ShaderProgram.h>

#include <SDL3/SDL.h>
#include <glm/glm.hpp>

#include <vector>

struct GLState
{
    /* PUBLIC MEMBERS */
    
    SDL_GLContext gl { nullptr };
    
    glm::mat4 m_view, m_proj, m_VP;
    
    glm::vec3 camera_pos { 0, 0, 4 };
    glm::vec3 camera_target { 0, 0, 0 };
    glm::vec3 camera_up { 0, 1, 0 };
    /* camera settings, only needed for projection */
    //float camera_fov { 45.0f };
    //float camera_near { 0.1f };
    //float camera_far { 100.0f };
    //float camera_aspect_ratio { 1.0f };
    
    /* BEATBOXX CLIENT MEMBERS */
    
    std::vector<ShaderProgram> shaderprograms;
    
    /* PUBLIC METHODS */
    
    bool init(SDL_Window* window, FileSystemState& filesystemstate);
    void iterate(const FileSystemState& filesystemstate);
    void draw(SDL_Window* window, int w, int h, float ds);
    /* sets view-projection matrix based on current camera settings, as well as screen width and height (for aspect ratio) */
    void set_mVP(int w, int h);
}; // GLState

#endif // GLState