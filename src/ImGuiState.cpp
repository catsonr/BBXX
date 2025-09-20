#include <BBXX/ImGuiState.h>

#include <imgui.h>
#include <backends/imgui_impl_sdl3.h>
#include <backends/imgui_impl_opengl3.h>

#include <stdio.h>

bool ImGuiState::init(SDL_Window* window, SDL_GLContext gl)
{
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO();
    io.IniFilename = nullptr;
    
    if( !ImGui_ImplSDL3_InitForOpenGL(window, gl) ) {
        printf("[ImGuiState::init] failed to init for opengl!\n");
        return false;
    }
    
#ifndef __EMSCRIPTEN__
    ImGui_ImplOpenGL3_Init("#version 330 core");
#else
    ImGui_ImplOpenGL3_Init("#version 300 es");
#endif
    
    return true;
}

void ImGuiState::handle_event(const SDL_Event* event)
{
    ImGui_ImplSDL3_ProcessEvent(event);
}

void ImGuiState::draw()
{
    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplSDL3_NewFrame();
    ImGui::NewFrame();
    
    static bool show = true;
    ImGui::ShowDemoWindow(&show);
    
    ImGui::Render();
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
}