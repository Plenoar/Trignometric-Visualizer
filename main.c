#include <stdio.h>
#include <math.h>
#include <string.h>
#include <stdlib.h> // For malloc and free

#include "simulation.h"
#include "ui.h"

#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif

#define EPSILON 1e-6f


LineOscillator G_PRESET_0[] = { 
    { " Rotating Ribcage Carriage ", true, 200.0f, 10.0f, 250.0f, FN_NEG_COS, 1.990f, FN_SIN, 1.0f, FN_NEG_SIN, 1.0f, FN_ZERO, 1.0f, 
      {0.0f, 0.0f, 0.0f, 0.0f}, {0.0f, 0.0f, 0.0f, 1.0f}, {0.0f, 0.241f, 0.976f, 1.0f} }
};

LineOscillator G_PRESET_sigegg[] = { 
    { " EGG Signature ", true, 200.0f, 10.0f, 250.0f, FN_NEG_COS, 9.700f, FN_SIN, 9.905f, FN_NEG_SIN, 10.0f, FN_NEG_COS , 10.0f, 
      {0.0f, 0.0f, 0.0f, 0.0f}, {0.0f, 0.0f, 0.0f, 1.0f}, {1.0f, 0.400f, 0.400f, 1.0f} }
};


LineOscillator G_PRESET_paper[] = { 
    { " Paper ", true, 200.0f, 10.0f, 250.0f, FN_NEG_COS, 1.990f, FN_SIN, 1.0f, FN_NEG_SIN, 1.0f, FN_COS, 1.0f, 
      {0.0f, 0.0f, 0.0f, 0.0f}, {0.0f, 0.0f, 0.0f, 1.0f}, {0.0f, 0.241f, 0.976f, 1.0f} }
};

LineOscillator G_PRESET_1[] = { 
    { " Fabric Pattern", true, 200.0f, 10.0f, 250.0f, FN_NEG_COS, 1.990f, FN_SIN, 1.0f, FN_NEG_SIN, 1.0f, FN_COS, 1.0f, 
      {0.0f, 0.0f, 0.0f, 1.0f}, {0.0f, 0.0f, 0.0f, 1.0f}, {0.0f, 1.0f, 1.0f, 1.0f} }  // Already normalized
};

LineOscillator G_PRESET_2[] = { 
    { " Perfect Harmony ", true, 200.0f, 10.0f, 250.0f, FN_NEG_COS, 1.990f, FN_SIN, 1.0f, FN_NEG_COS, 1.0f, FN_ZERO, 1.0f, 
      {1.0f, 1.0f, 1.0f, 1.0f}, {0.0f, 0.0f, 0.0f, 0.0f}, {0.0f, 1.0f, 1.0f, 1.0f} }
};

LineOscillator G_PRESET_3[] = { 
    { " Takeofff ", true, 200.0f, 10.0f, 250.0f, FN_SIN, 2.995f, FN_NEG_COS, 2.0f, FN_SIN, 1.0f, FN_NEG_TAN, 1.0f, 
      {0.0f, 0.0f, 0.0f, 1.0f}, {0.0f, 0.0f, 0.0f, 1.0f}, {0.800f, 0.760f, 1.0f, 1.0f} }
};

LineOscillator G_PRESET_4[] = { 
    { " Duel in the Midst ", true, 200.0f, 10.0f, 250.0f, FN_NEG_COS, 1.990f, FN_SIN, 1.0f, FN_NEG_SEC, 1.0f, FN_SIN, 1.0f, 
      {0.0f, 0.0f, 0.0f, 1.0f}, {0.0f, 0.0f, 0.0f, 1.0f}, {0.024f, 0.024f, 0.945f, 1.0f} }
};

LineOscillator G_PRESET_5[] = { 
    { " Sandal? ", true, 200.0f, 10.0f, 250.0f, FN_NEG_COS, 1.990f, FN_SIN, 1.0f, FN_NEG_SIN, 1.0f, FN_SIN, 1.0f, 
      {0.180f, 0.169f, 0.169f, 1.0f}, {0.0f, 0.0f, 0.0f, 1.0f}, {0.431f, 0.024f, 0.945f, 1.0f} }
};

LineOscillator G_PRESET_10[] = { 
    { " Wait Dont Leave Me ", true, 200.0f, 10.0f, 250.0f, FN_ZERO, 0.0f, FN_SIN, 1.0f, FN_NEG_SEC, 0.150f, FN_SIN, 10.0f, 
      {0.0f, 0.0f, 0.0f, 1.0f}, {0.0f, 1.0f, 0.0f, 1.0f}, {0.0f, 1.0f, 0.945f, 1.0f} }
};

LineOscillator G_PRESET_cork[] = { 
    { " Flying Cork ", true, 200.0f, 10.0f, 250.0f, FN_NEG_COS, -2.417f, FN_SIN, 2.0f, FN_NEG_SEC, 1.0f, FN_SIN, 1.0f, 
      {0.0f, 0.0f, 0.0f, 1.0f}, {0.200f, 0.100f, 0.100f, 1.0f}, {0.500f, 0.10f, 0.900f, 1.0f} }
};

LineOscillator G_PRESET_aurora[] = { 
    { " Aurora ", true, 200.0f, 10.0f, 250.0f, FN_NEG_COS, 4.0f, FN_SIN, 1.0f, FN_NEG_SIN, 7.0f, FN_SIN, 3.555f, 
      {0.0f, 0.0f, 0.0f, 1.0f}, {0.200f, 0.100f, 0.100f, 1.0f}, {0.700f, 0.300f, 0.900f, 1.0f} }
};


LineOscillator G_PRESET_6[] = { 
    { " Spinning Line ", true, 200.0f, 10.0f, 250.0f, FN_NEG_COS, 1.0f, FN_NEG_SIN, 1.0f, FN_COS, 1.0f, FN_SIN, 1.0f, 
      {1.0f, 0.0f, 0.0f, 1.0f}, {0.0f, 1.0f, 0.0f, 1.0f}, {0.0f, 1.0f, 1.0f, 1.0f} }
};

LineOscillator G_PRESET_7[] = { 
    { " Full Fill ", true, 200.0f, 10.0f, 250.0f, FN_SIN, 1.0f, FN_COS, 1.0f, FN_COS, 1.0f, FN_SIN, 1.0f, 
      {1.0f, 0.0f, 0.0f, 1.0f}, {0.0f, 1.0f, 0.0f, 1.0f}, {0.0f, 1.0f, 1.0f, 1.0f} }
};

LineOscillator G_PRESET_8[] = { 
    { " 1/3 ", true, 200.0f, 10.0f, 250.0f, FN_SIN, 1.0f, FN_COS, 1.0f, FN_NEG_COS, 1.0f, FN_SIN, 1.0f, 
      {1.0f, 0.0f, 0.0f, 1.0f}, {0.0f, 1.0f, 0.0f, 1.0f}, {0.0f, 1.0f, 1.0f, 1.0f} }
};

LineOscillator G_PRESET_9[] = { 
    { "Lissajous", true, 200.0f, 10.0f, 250.0f, FN_SIN, 3.0f, FN_ZERO, 1.0f, FN_ZERO, 1.0f, FN_COS, 2.0f, 
      {1.0f, 0.0f, 0.0f, 1.0f}, {0.0f, 1.0f, 0.0f, 1.0f}, {0.0f, 1.0f, 1.0f, 1.0f} }
};

PointOscillator P_PRESET_10[] = { 
    { "Unit Circle", true, 200.0f, 10.0f, 250.0f, FN_SIN, 1.0f, FN_COS, 1.0f, {1.0f, 0.0f, 0.0f, 1.0f} }
};

// FORWARD DECLARATIONS
void init_simulation(SimulationState* state);
void load_preset(SimulationState* state, int preset_index);
void handle_input(SimulationState* state);
void update_simulation(SimulationState* state);
void cleanup(SimulationState* state);
void clear_trails(SimulationState* state);
float eval_wave_func(WaveFuncType type, float freq, double time);
void add_new_line_oscillator(SimulationState* state);
void add_new_point_oscillator(SimulationState* state);
void get_last_trail_points(PointTrail* trail, int max_points, SDL_FPoint* out_points, int* out_count);

// rendering 

void Render_Prepare(SimulationState* state);
void Render_UI(SimulationState *state);
void Render_End(SimulationState *state);

void Render_LineOscillator(SimulationState *state, LineOscillator *osc);
void Render_PointOscillator(SimulationState *state, PointOscillator *osc);
void Render_Simulation(SimulationState* state);



int main(void)
{
    SimulationState state = {0};
    init_simulation(&state);
    while (!state.quit)
    {
        handle_input(&state);

        Render_Prepare(&state);      // SDL_RenderClear (black background)

        update_simulation(&state);   // All custom SDL_Render* (positions, lines, points, trails) — draws simulation under UI

        ui_begin_render();           // ImGui_ImplSDL3_NewFrame() + ImGui_ImplSDLRenderer3_NewFrame() + ImGui::NewFrame()
        ui_render(&state);           // Build ImGui windows (presets list, controls, etc.)

        ui_end_render(state.renderer);  // ImGui::Render() + ImGui_ImplSDLRenderer3_RenderDrawData() — draws UI on top, clean state
        Render_End(&state);
    }

    cleanup(&state);
    return 0;
}

void init_simulation(SimulationState* state)
{
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        printf("Error: SDL init failed: %s\n", SDL_GetError());
        return;
    }

    SDL_CreateWindowAndRenderer("Wave Visualizer", 1280, 720 , SDL_WINDOW_RESIZABLE , &state->window , &state->renderer);
    if (!state->window || !state->renderer)
    {
        printf("Error: SDL windwo and renderer creation failed for some reason : %s\n", SDL_GetError());
        SDL_Quit();
        return;
    }
    
    // Initialize the UI system
    ui_init(state->window, state->renderer);

    state->time = 0.0;
    state->time_step = 0.01f;
    state->is_running = true;
    state->camera_x = 0.0f;
    state->camera_y = 0.0f;
    state->zoom = 1.0f;
    state->is_panning = false;
    state->max_trail_points = MAX_TRAIL_POINTS;
    state->show_lines = true;
    state->show_points = true;
    state->show_trails = false;
    state->trail_style = TRAIL_POINTS;
    state->line_oscillator_active = false;
    state->point_oscillator_active = false;
    state->line_oscillator_count = 0;
    state->point_oscillator_count = 0;
    state->background_colour = (Color){0.0f, 0.0f, 0.0f, 1.0f};
    state->line_colour = (Color){1.0f, 1.0f, 1.0f, 1.0f};
    state->point_colour = (Color){1.0f, 1.0f, 0.0f, 1.0f};
    state->preset_count = 16;
    state->new_preset_name[0] = '\0';
    state->presets[0] = (Preset){" Rotating Ribcage Carriage",  G_PRESET_0, 1, OS_LINE, NULL , 0.0109,  true , true , true };
    state->presets[1] = (Preset){" EGG Signature ",             G_PRESET_sigegg, 1, OS_LINE, NULL , 0.0006,  true , true , true };
    state->presets[2] = (Preset){" Paper ",                     G_PRESET_paper, 1, OS_LINE, NULL , 0.0109,  true , true , true };
    state->presets[3] = (Preset){" Fabric Pattern ",            G_PRESET_1, 1, OS_LINE, NULL , 0.0905 , true , true , true};
    state->presets[4] = (Preset){" Perfect Harmony",            G_PRESET_2, 1, OS_LINE, NULL , 0.0043 , true , true , true};
    state->presets[5] = (Preset){" Takeoff ",                   G_PRESET_3, 1, OS_LINE, NULL , 0.0284,  true , true , true};
    state->presets[6] = (Preset){" Duel in the Midst ",         G_PRESET_4, 1, OS_LINE, NULL , 0.0109,  true , true , true};
    state->presets[7] = (Preset){" Sandal? ",                   G_PRESET_5, 1, OS_LINE, NULL , 0.0066,  true , true , true};
    state->presets[8] = (Preset){" Wait Dont Leave Me ",        G_PRESET_10, 1, OS_LINE, NULL , 0.0015,       true , true , true};
    state->presets[9] = (Preset){" Cork ",                      G_PRESET_cork, 1, OS_LINE, NULL , 0.0128,       true , true , true};
    state->presets[10] = (Preset){" Aurora ",                    G_PRESET_aurora, 1, OS_LINE, NULL , 0.0204,       true , true , true};
    state->presets[11] = (Preset){" Spinning Line ",             G_PRESET_6, 1, OS_LINE, NULL , 0.0100,       true , true , true};
    state->presets[12] = (Preset){" Full Fill ",                 G_PRESET_7, 1, OS_LINE, NULL , 0.0100,       true , true , true};
    state->presets[13] = (Preset){" 1/3 ",                       G_PRESET_8, 1, OS_LINE, NULL , 0.0100,       true , true , true};
    state->presets[14] = (Preset){" Lissajous ",                 G_PRESET_9, 1, OS_LINE, NULL , 0.0100,       true , true , true};
    state->presets[15] = (Preset){" Unit Circle",                P_PRESET_10, 1, OS_POINT, NULL , 0.0100,      true , true , true};
    state->quit = false;

    clear_trails(state);
    load_preset(state,1);
}

void clear_trails(SimulationState* state)
{
    for (int i = 0; i < MAX_OSCILLATORS * 3; ++i)
    {
        state->line_trails[i].head = 0;
        state->line_trails[i].count = 0;
    }
    for (int i = 0; i < MAX_OSCILLATORS; ++i)
    {
        state->point_trails[i].head = 0;
        state->point_trails[i].count = 0;
    }
}

void get_last_trail_points(PointTrail* trail, int max_points, SDL_FPoint* out_points, int* out_count)
{
    int effective_count = (trail->count > max_points) ? max_points : trail->count;
    *out_count = effective_count;
    
    if (effective_count == 0) return;

    int start_idx = (trail->head - effective_count + MAX_TRAIL_POINTS) % MAX_TRAIL_POINTS;
    for (int i = 0; i < effective_count; ++i) {
        int idx = (start_idx + i) % MAX_TRAIL_POINTS;
        out_points[i] = trail->points[idx];
    }
}

void load_preset(SimulationState* state, int preset_index)
{

    if (preset_index < 0 || preset_index >= state->preset_count) return;
    Preset* preset = &state->presets[preset_index];
    int count = preset->count;
    
    if (count > MAX_OSCILLATORS) count = MAX_OSCILLATORS;
    
    state->line_oscillator_count = 0;
    state->point_oscillator_count = 0;
    memset(state->line_oscillators, 0, sizeof(state->line_oscillators));
    memset(state->point_oscillators, 0, sizeof(state->point_oscillators));
    state->line_oscillator_active = false;
    state->point_oscillator_active = false;
    
    if (preset->type == OS_LINE)
    {
        state->line_oscillator_active = true;
        memcpy(state->line_oscillators, preset->oscillators, count * sizeof(LineOscillator));
        state->line_oscillator_count = count;
    }
    
    else if (preset->type == OS_POINT)
    {
        state->point_oscillator_active = true;
        memcpy(state->point_oscillators, preset->oscillators, count * sizeof(PointOscillator));
        state->point_oscillator_count = count;
    }


    state->time_step = preset->time_step;
    state->show_lines = preset->show_line;
    state->show_points = preset->show_points;
    state->show_trails = preset->show_trail;


    clear_trails(state);
}


void handle_input(SimulationState* state)
{
    SDL_Event event;
    while (SDL_PollEvent(&event))
    {
        ui_process_event(&event);
        
        if (event.type == SDL_EVENT_QUIT || (event.type == SDL_EVENT_WINDOW_CLOSE_REQUESTED && event.window.windowID == SDL_GetWindowID(state->window))) state->quit = true;
        
        if (ui_wants_capture_mouse()) continue;
        switch (event.type)
        {
            case SDL_EVENT_WINDOW_PIXEL_SIZE_CHANGED : 
                SDL_GetWindowSize(state->window, &state->screen_width, &state->screen_height);
                break;
            case SDL_EVENT_MOUSE_BUTTON_DOWN : if (event.button.button == SDL_BUTTON_RIGHT) { state->is_panning = true; } break;
            case SDL_EVENT_MOUSE_BUTTON_UP : if (event.button.button == SDL_BUTTON_RIGHT) { state->is_panning = false; } break;
            case SDL_EVENT_MOUSE_MOTION : if (state->is_panning) { state->camera_x -= event.motion.xrel / state->zoom; state->camera_y -= event.motion.yrel / state->zoom; } break;
            case SDL_EVENT_MOUSE_WHEEL : state->zoom *= (1.0f + event.wheel.y * 0.1f); if (state->zoom < 0.1f) state->zoom = 0.1f; if (state->zoom > 10.0f) state->zoom = 10.0f; break;
            case SDL_EVENT_KEY_DOWN :
                if (event.key.key == SDLK_SPACE || event.key.key == SDLK_P) state->is_running = !state->is_running;
                if (event.key.key == SDLK_ESCAPE) state->quit = true;
        }
    }
}

// all calculations should be done here 
void update_simulation(SimulationState* state)
{
    if (state->is_running) state->time += state->time_step;

    if(state->line_oscillator_active == true)
    {
        for (int i = 0; i < state->line_oscillator_count; ++i)
        {
            LineOscillator* l_osc = &state->line_oscillators[i];
            if (!l_osc->enabled) continue;

            float p1x = l_osc->base_x + l_osc->amplitude * eval_wave_func(l_osc->p1_func_x, l_osc->p1_freq_x, state->time);
            float p1y = l_osc->base_y + l_osc->amplitude * eval_wave_func(l_osc->p1_func_y, l_osc->p1_freq_y, state->time);
            float p2x = l_osc->base_x + l_osc->amplitude * eval_wave_func(l_osc->p2_func_x, l_osc->p2_freq_x, state->time);
            float p2y = l_osc->base_y + l_osc->amplitude * eval_wave_func(l_osc->p2_func_y, l_osc->p2_freq_y, state->time);
            
            l_osc->point1.x = p1x;
            l_osc->point1.y = p1y;
            l_osc->point2.x = p2x;
            l_osc->point2.y = p2y;
            
            if (state->is_running && state->show_trails)
            {
                PointTrail* p1_trail = &state->line_trails[i * 3 + 0];
                PointTrail* p2_trail = &state->line_trails[i * 3 + 1];
                PointTrail* mid_trail = &state->line_trails[i * 3 + 2];
            
                p1_trail->points[p1_trail->head] = (SDL_FPoint){p1x, p1y};
                p2_trail->points[p2_trail->head] = (SDL_FPoint){p2x, p2y};
                mid_trail->points[mid_trail->head] = (SDL_FPoint){(p1x + p2x) / 2.0f, (p1y + p2y) / 2.0f};
            
                p1_trail->head = (p1_trail->head + 1) % MAX_TRAIL_POINTS;
                p2_trail->head = (p2_trail->head + 1) % MAX_TRAIL_POINTS;
                mid_trail->head = (mid_trail->head + 1) % MAX_TRAIL_POINTS;
            
                if (p1_trail->count < MAX_TRAIL_POINTS) p1_trail->count++;
                if (p2_trail->count < MAX_TRAIL_POINTS) p2_trail->count++;
                if (mid_trail->count < MAX_TRAIL_POINTS) mid_trail->count++;

                if(state->show_lines) Render_LineOscillator(state , l_osc);
            }
        }
    }

    if (state->point_oscillator_active == true)
    {
        for (int i = 0; i < state->point_oscillator_count; ++i)
        {
            PointOscillator* p_osc = &state->point_oscillators[i];
            if (!p_osc->enabled) continue;
            float px = p_osc->base_x + p_osc->amplitude * eval_wave_func(p_osc->func_x, p_osc->freq_x, state->time);
            float py = p_osc->base_y + p_osc->amplitude * eval_wave_func(p_osc->func_y, p_osc->freq_y, state->time);
            
            p_osc->point.x = px;
            p_osc->point.y = py;

            if (state->is_running && state->show_trails)
            {
                PointTrail* trail = &state->point_trails[i];
                trail->points[trail->head] = (SDL_FPoint){px, py};
                trail->head = (trail->head + 1) % MAX_TRAIL_POINTS;
                if (trail->count < MAX_TRAIL_POINTS) trail->count++;
            }
            if(state->show_points) Render_PointOscillator(state, p_osc);
    }}
    Render_Simulation(state);
}

void cleanup(SimulationState* state)
{
    for (int i = 0; i < state->preset_count; ++i) if (state->presets[i].alloc_mem) { free(state->presets[i].alloc_mem); }
    ui_shutdown();
    SDL_DestroyRenderer(state->renderer);
    SDL_DestroyWindow(state->window);
    SDL_Quit();
}

float eval_wave_func(WaveFuncType type, float freq, double time)
{
    if(type == FN_ZERO) return 0.0f;

    double arg = time * freq * 2.0 * M_PI;
    switch (type)
    {
        case FN_SIN:     return (float)sin(arg);
        case FN_COS:     return (float)cos(arg);
        case FN_TAN:     return (fabs(sin(arg)) < EPSILON || fabs(cos(arg)) < EPSILON) ? 0.0f : (float)tan(arg);
        case FN_CSC:     return fabs(sin(arg)) < EPSILON ? 0.0f : (float)(1.0 / sin(arg));
        case FN_SEC:     return fabs(cos(arg)) < EPSILON ? 0.0f : (float)(1.0 / cos(arg));
        case FN_COT:     return fabs(tan(arg)) < EPSILON ? 0.0f : (float)(1.0 / tan(arg));
        case FN_NEG_SIN: return -(float)sin(arg);
        case FN_NEG_COS: return -(float)cos(arg);
        case FN_NEG_TAN: return (fabs(sin(arg)) < EPSILON || fabs(cos(arg)) < EPSILON) ? 0.0f : -(float)tan(arg);
        case FN_NEG_CSC: return fabs(sin(arg)) < EPSILON ? 0.0f : -(float)(1.0 / sin(arg));
        case FN_NEG_SEC: return fabs(cos(arg)) < EPSILON ? 0.0f : -(float)(1.0 / cos(arg));
        case FN_NEG_COT: return fabs(tan(arg)) < EPSILON ? 0.0f : -(float)(1.0 / tan(arg));
        default:         return 0.0f;
    }
}

void add_new_line_oscillator(SimulationState* state)
{
    if (state->line_oscillator_count < MAX_OSCILLATORS)
    {
        LineOscillator* new_osc = &state->line_oscillators[state->line_oscillator_count];
        snprintf(new_osc->name, sizeof(new_osc->name), "New Line Oscillator");
        new_osc->enabled = true;
        new_osc->base_x = 450.0f; new_osc->base_y = 450.0f;
        new_osc->amplitude = 50.0f;
        new_osc->p1_func_x = FN_COS; new_osc->p1_freq_x = 1.0f;
        new_osc->p1_func_y = FN_SIN; new_osc->p1_freq_y = 1.0f;
        new_osc->p2_func_x = FN_ZERO; new_osc->p2_freq_x = 1.0f;
        new_osc->p2_func_y = FN_ZERO; new_osc->p2_freq_y = 1.0f;
        new_osc->point1_colour = (Color){1.0f, 0.0f, 0.0f, 1.0f};
        new_osc->point2_colour = (Color){0.0f, 1.0f, 0.0f, 1.0f};
        new_osc->mid_point_colour = (Color){0.0f, 1.0f, 1.0f, 1.0f};
        state->line_oscillator_count++;
        state->line_oscillator_active = true;
    }
}

void add_new_point_oscillator(SimulationState* state)
{
    if (state->point_oscillator_count < MAX_OSCILLATORS)
    {
        PointOscillator* new_osc = &state->point_oscillators[state->point_oscillator_count];
        snprintf(new_osc->name, sizeof(new_osc->name), "New Point Oscillator");
        new_osc->enabled = true;
        new_osc->base_x = 450.0f; new_osc->base_y = 450.0f;
        new_osc->amplitude = 50.0f;
        new_osc->func_x = FN_COS; new_osc->freq_x = 1.0f;
        new_osc->func_y = FN_SIN; new_osc->freq_y = 1.0f;
        new_osc->point_colour = (Color){1.0f, 1.0f, 0.0f, 1.0f};
        state->point_oscillator_count++;
        state->point_oscillator_active = true;
    }
}

void Render_Prepare(SimulationState* state)
{
    SDL_SetRenderDrawColor(state->renderer, (Uint8)(state->background_colour.r * 255), (Uint8)(state->background_colour.g * 255),
                                            (Uint8)(state->background_colour.b * 255), (Uint8)(state->background_colour.a * 255));
    SDL_RenderClear(state->renderer);
}

void Render_UI(SimulationState *state)
{
    ui_begin_render();
    ui_render(state);
}

void Render_End(SimulationState *state)
{
    SDL_RenderPresent(state->renderer);

}

void Render_LineOscillator(SimulationState *state, LineOscillator *osc)
{

    float screen_p1x = (osc->point1.x - state->camera_x) * state->zoom + state->screen_width / 2.0f;
    float screen_p1y = (osc->point1.y - state->camera_y) * state->zoom + state->screen_height / 2.0f;
    float screen_p2x = (osc->point2.x - state->camera_x) * state->zoom + state->screen_width / 2.0f;
    float screen_p2y = (osc->point2.y - state->camera_y) * state->zoom + state->screen_height / 2.0f;
    
    SDL_SetRenderDrawColor(state->renderer, (Uint8)(state->line_colour.r * 255), (Uint8)(state->line_colour.g * 255),
                                            (Uint8)(state->line_colour.b * 255), (Uint8)(state->line_colour.a * 255));
    SDL_RenderLine(state->renderer, screen_p1x, screen_p1y, screen_p2x, screen_p2y);
    
    SDL_SetRenderDrawColor(state->renderer, (Uint8)(osc->point1_colour.r * 255), (Uint8)(osc->point1_colour.g * 255),
                                            (Uint8)(osc->point1_colour.b * 255), (Uint8)(osc->point1_colour.a * 255));
    SDL_RenderPoint(state->renderer, screen_p1x, screen_p1y);
    
    SDL_SetRenderDrawColor(state->renderer, (Uint8)(osc->point2_colour.r * 255), (Uint8)(osc->point2_colour.g * 255),
                                            (Uint8)(osc->point2_colour.b * 255), (Uint8)(osc->point2_colour.a * 255));
    SDL_RenderPoint(state->renderer, screen_p2x, screen_p2y);
}

void Render_PointOscillator(SimulationState *state, PointOscillator *osc)
{
    float screen_px = (osc->point.x - state->camera_x) * state->zoom + state->screen_width / 2.0f;
    float screen_py = (osc->point.y - state->camera_y) * state->zoom + state->screen_height / 2.0f;
    SDL_SetRenderDrawColor(state->renderer, (Uint8)(osc->point_colour.r * 255), (Uint8)(osc->point_colour.g * 255),
                                            (Uint8)(osc->point_colour.b * 255), (Uint8)(osc->point_colour.a * 255));
    SDL_RenderPoint(state->renderer, screen_px, screen_py);
}


void Render_Simulation(SimulationState* state)
{
    // we can optimize this by querying for a screen change and only calculating the dimesions when it is changed 
    if (state->show_trails)
    {
        SDL_FPoint transformed_points[MAX_TRAIL_POINTS];
        for (int i = 0; i < state->point_oscillator_count; ++i)
        {
            if (!state->point_oscillators[i].enabled || !state->point_oscillator_active) continue;
            
            PointTrail* trail = &state->point_trails[i];
            int trail_count;
            get_last_trail_points(trail, state->max_trail_points, transformed_points, &trail_count);
            
            if (trail_count == 0) continue;
            
            for (int j = 0; j < trail_count; ++j)
            {
                transformed_points[j].x = (transformed_points[j].x - state->camera_x) * state->zoom + state->screen_width / 2.0f;
                transformed_points[j].y = (transformed_points[j].y - state->camera_y) * state->zoom + state->screen_height / 2.0f;
            }
            Color col = state->point_oscillators[i].point_colour;
            
            if (state->trail_style == TRAIL_POINTS)
            {
                SDL_SetRenderDrawColor(state->renderer, (Uint8)(col.r * 255), (Uint8)(col.g * 255), (Uint8)(col.b * 255), (Uint8)(col.a * 255));
                SDL_RenderPoints(state->renderer, transformed_points, trail_count);
            }

            else
            {
                for (int j = 1; j < trail_count; ++j) {
                    Uint8 alpha = (Uint8)(col.a * 255);
                    if (state->trail_style == TRAIL_FADED_LINES) alpha = (Uint8)(alpha * ((float)j / trail_count));
                    SDL_SetRenderDrawColor(state->renderer, (Uint8)(col.r * 255), (Uint8)(col.g * 255), (Uint8)(col.b * 255), alpha);
                    SDL_RenderLine(state->renderer, transformed_points[j-1].x, transformed_points[j-1].y, transformed_points[j].x, transformed_points[j].y);
                }
            }
        }

        for (int i = 0; i < state->line_oscillator_count; ++i)
        {
            if (!state->line_oscillators[i].enabled || !state->line_oscillator_active) continue;
        
            for (int trail_type = 0; trail_type < 3; ++trail_type)
            {
                PointTrail* trail = &state->line_trails[i * 3 + trail_type];
                int trail_count;
                get_last_trail_points(trail, state->max_trail_points, transformed_points, &trail_count);
                
                if (trail_count == 0) continue;
                for (int j = 0; j < trail_count; ++j) {
                    transformed_points[j].x = (transformed_points[j].x - state->camera_x) * state->zoom + state->screen_width / 2.0f;
                    transformed_points[j].y = (transformed_points[j].y - state->camera_y) * state->zoom + state->screen_height / 2.0f;
                }
                
                Color col;
                if (trail_type == 0) col = state->line_oscillators[i].point1_colour;
                else if (trail_type == 1) col = state->line_oscillators[i].point2_colour;
                else col = state->line_oscillators[i].mid_point_colour;
                
                if (state->trail_style == TRAIL_POINTS)
                {
                    SDL_SetRenderDrawColor(state->renderer, (Uint8)(col.r * 255), (Uint8)(col.g * 255), (Uint8)(col.b * 255), (Uint8)(col.a * 255));
                    SDL_RenderPoints(state->renderer, transformed_points, trail_count);
                }
                
                else
                {
                    for (int j = 1; j < trail_count; ++j)
                    {
                        Uint8 alpha = (Uint8)(col.a * 255);
                        if (state->trail_style == TRAIL_FADED_LINES) { alpha = (Uint8)(alpha * ((float)j / trail_count)); }
                        SDL_SetRenderDrawColor(state->renderer, (Uint8)(col.r * 255), (Uint8)(col.g * 255), (Uint8)(col.b * 255), alpha);
                        SDL_RenderLine(state->renderer, transformed_points[j-1].x, transformed_points[j-1].y, transformed_points[j].x, transformed_points[j].y);
}}}}}}
    