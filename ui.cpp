#include "imgui/imgui.h"
#include "imgui/imgui_impl_sdl3.h"
#include "imgui/imgui_impl_sdlrenderer3.h"

#include "simulation.h"
#include "ui.h"
#include<cstdio>
#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif

// Forward declaration for the C function from main.c
// This allows the UI to call back into the C code if needed.
extern "C" {
    void load_preset(SimulationState* state, int preset_index);
    void save_current_preset(SimulationState* state);
    void add_new_line_oscillator(SimulationState* state);
    void add_new_point_oscillator(SimulationState* state);
    void clear_trails(SimulationState* state);
}


// --- Global Data (from original file) ---
const char* G_WAVE_FUNC_NAMES[] = {
    "sin(t)", "cos(t)", "tan(t)", "csc(t)", "sec(t)", "cot(t)",
    "-sin(t)", "-cos(t)", "-tan(t)", "-csc(t)", "-sec(t)", "-cot(t)",
    "0"
};
const char* G_TRAIL_STYLE_NAMES[] = { "Points", "Lines", "Faded Lines" };


// --- UI Function Implementations ---

void ui_init(SDL_Window* window, SDL_Renderer* renderer) {
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO(); (void)io;
    ImGui::StyleColorsDark();
    ImGui_ImplSDL3_InitForSDLRenderer(window, renderer);
    ImGui_ImplSDLRenderer3_Init(renderer);
}

void ui_shutdown() {
    ImGui_ImplSDLRenderer3_Shutdown();
    ImGui_ImplSDL3_Shutdown();
    ImGui::DestroyContext();
}

void ui_process_event(const SDL_Event* event) {
    ImGui_ImplSDL3_ProcessEvent(event);
}

bool ui_wants_capture_mouse() {
    return ImGui::GetIO().WantCaptureMouse;
}

void ui_begin_render() {
    ImGui_ImplSDLRenderer3_NewFrame();
    ImGui_ImplSDL3_NewFrame();
    ImGui::NewFrame();
}

void ui_end_render(SDL_Renderer* renderer) {
    ImGui::Render();
    ImGui_ImplSDLRenderer3_RenderDrawData(ImGui::GetDrawData(), renderer);
}

// This function is the original render_ui function
void ui_render(SimulationState* state) {
    ImGuiIO& io = ImGui::GetIO(); (void)io;
    const ImGuiViewport* viewport = ImGui::GetMainViewport();
    ImGui::SetNextWindowPos(viewport->WorkPos);
    ImGui::SetNextWindowSize(ImVec2(350, viewport->WorkSize.y));
    ImGui::Begin("Controls", NULL, ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoCollapse);
    
    ImGui::ColorEdit4("Background Colour", (float*)&state->background_colour);
    ImGui::ColorEdit4("Default Line Colour", (float*)&state->line_colour);
    ImGui::ColorEdit4("Default Point Colour", (float*)&state->point_colour);
    
    if (ImGui::CollapsingHeader("Time Controls", ImGuiTreeNodeFlags_DefaultOpen)) {
        if (ImGui::Button(state->is_running ? "Pause" : "Play", ImVec2(100, 0))) { state->is_running = !state->is_running; }
        ImGui::SameLine();
        if (ImGui::Button("Single Step", ImVec2(100, 0))) { state->is_running = false; state->time += state->time_step; }
        ImGui::SliderFloat("Time Speed", &state->time_step, 0.0f, 0.1f, "%.4f");
        ImGui::Text("Current Time: %.2f", state->time);
        ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / io.Framerate, io.Framerate);
    }
    
    if (ImGui::CollapsingHeader("View Controls", ImGuiTreeNodeFlags_DefaultOpen)) {
        ImGui::Checkbox("Show Lines", &state->show_lines);
        ImGui::Checkbox("Show Points", &state->show_points);
        bool trails_toggled = ImGui::Checkbox("Show Trails", &state->show_trails);
        if (trails_toggled && !state->show_trails) { clear_trails(state); }
        ImGui::Combo("Trail Style", (int*)&state->trail_style, G_TRAIL_STYLE_NAMES, IM_ARRAYSIZE(G_TRAIL_STYLE_NAMES));
        ImGui::SliderInt("Max Trail Points", &state->max_trail_points, 100, MAX_TRAIL_POINTS);
        ImGui::SliderFloat("Zoom", &state->zoom, 0.1f, 10.0f, "%.2f");
        if (ImGui::IsItemHovered()) { ImGui::SetTooltip("Controls the zoom level of the view."); }
        if (ImGui::Button("Reset View")) { state->camera_x = 0.0f; state->camera_y = 0.0f; state->zoom = 1.0f; }
    }

    if (ImGui::CollapsingHeader("Presets", ImGuiTreeNodeFlags_DefaultOpen)) {
        for (int i = 0; i < state->preset_count; ++i) {
            if (ImGui::Selectable(state->presets[i].name)) { load_preset(state, i); }
        }
    }
    
    ImGui::SeparatorText("Oscillators");
    if (ImGui::BeginTabBar("OscillatorTabs")) {
        if (ImGui::BeginTabItem("Line Oscillators")) {
            if (ImGui::Button("Add New Line Oscillator")) { add_new_line_oscillator(state); }
            for (int i = 0; i < state->line_oscillator_count; ++i) {
                LineOscillator* osc = &state->line_oscillators[i];
                char header_title[128];
                snprintf(header_title, sizeof(header_title), "Line %d: %s###%d", i + 1, osc->name, i);
                if (ImGui::CollapsingHeader(header_title)) {
                    ImGui::PushID(i);
                    ImGui::Checkbox("Enabled", &osc->enabled);
                    ImGui::InputText("Name", osc->name, sizeof(osc->name));
                    ImGui::InputFloat2("Base Position", (float*)&osc->base_x);
                    ImGui::SliderFloat("Amplitude", &osc->amplitude, 0.0f, 500.0f);
                    ImGui::SeparatorText("Point 1 (x, y)");
                    ImGui::Combo("P1 Func X", (int*)&osc->p1_func_x, G_WAVE_FUNC_NAMES, IM_ARRAYSIZE(G_WAVE_FUNC_NAMES));
                    ImGui::SliderFloat("P1 Freq X", &osc->p1_freq_x, 0.0f, 10.0f);
                    ImGui::Combo("P1 Func Y", (int*)&osc->p1_func_y, G_WAVE_FUNC_NAMES, IM_ARRAYSIZE(G_WAVE_FUNC_NAMES));
                    ImGui::SliderFloat("P1 Freq Y", &osc->p1_freq_y, 0.0f, 10.0f);
                    ImGui::ColorEdit4("Point 1 Colour", (float*)&osc->point1_colour);
                    ImGui::SeparatorText("Point 2 (x, y)");
                    ImGui::Combo("P2 Func X", (int*)&osc->p2_func_x, G_WAVE_FUNC_NAMES, IM_ARRAYSIZE(G_WAVE_FUNC_NAMES));
                    ImGui::SliderFloat("P2 Freq X", &osc->p2_freq_x, 0.0f, 10.0f);
                    ImGui::Combo("P2 Func Y", (int*)&osc->p2_func_y, G_WAVE_FUNC_NAMES, IM_ARRAYSIZE(G_WAVE_FUNC_NAMES));
                    ImGui::SliderFloat("P2 Freq Y", &osc->p2_freq_y, 0.0f, 10.0f);
                    ImGui::ColorEdit4("Point 2 Colour", (float*)&osc->point2_colour);
                    ImGui::ColorEdit4("Mid Point Colour", (float*)&osc->mid_point_colour);
                    ImGui::Separator();
                    if (ImGui::Button("Delete Oscillator")) {
                        for (int j = i; j < state->line_oscillator_count - 1; ++j) { state->line_oscillators[j] = state->line_oscillators[j + 1]; }
                        state->line_oscillator_count--;
                        ImGui::PopID();
                        break;
                    }
                    ImGui::PopID();
                }
            }
            ImGui::EndTabItem();
        }
        if (ImGui::BeginTabItem("Point Oscillators")) {
            if (ImGui::Button("Add New Point Oscillator")) { add_new_point_oscillator(state); }
            for (int i = 0; i < state->point_oscillator_count; ++i) {
                PointOscillator* osc = &state->point_oscillators[i];
                char header_title[128];
                snprintf(header_title, sizeof(header_title), "Point %d: %s###%d", i + 1, osc->name, i + MAX_OSCILLATORS);
                if (ImGui::CollapsingHeader(header_title)) {
                    ImGui::PushID(i + MAX_OSCILLATORS);
                    ImGui::Checkbox("Enabled", &osc->enabled);
                    ImGui::InputText("Name", osc->name, sizeof(osc->name));
                    ImGui::InputFloat2("Base Position", (float*)&osc->base_x);
                    ImGui::SliderFloat("Amplitude", &osc->amplitude, 0.0f, 500.0f);
                    ImGui::SeparatorText("Point (x, y)");
                    ImGui::Combo("Func X", (int*)&osc->func_x, G_WAVE_FUNC_NAMES, IM_ARRAYSIZE(G_WAVE_FUNC_NAMES));
                    ImGui::SliderFloat("Freq X", &osc->freq_x, 0.0f, 10.0f);
                    ImGui::Combo("Func Y", (int*)&osc->func_y, G_WAVE_FUNC_NAMES, IM_ARRAYSIZE(G_WAVE_FUNC_NAMES));
                    ImGui::SliderFloat("Freq Y", &osc->freq_y, 0.0f, 10.0f);
                    ImGui::ColorEdit4("Point Colour", (float*)&osc->point_colour);
                    ImGui::Separator();
                    if (ImGui::Button("Delete Oscillator")) {
                        for (int j = i; j < state->point_oscillator_count - 1; ++j) { state->point_oscillators[j] = state->point_oscillators[j + 1]; }
                        state->point_oscillator_count--;
                        ImGui::PopID();
                        break;
                    }
                    ImGui::PopID();
                }
            }
            ImGui::EndTabItem();
        }
        ImGui::EndTabBar();
    }
    
    ImGui::End();
}