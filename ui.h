#ifndef UI_H
#define UI_H

#include <stdbool.h>

// --- CHANGES ARE HERE ---

// 1. REMOVED the incorrect forward declaration: "struct SimulationState;"
// 2. ADDED a direct include to the header that defines SimulationState.
//    This gives this header file the full, correct definition.
#include "simulation.h"

// These forward declarations are fine because they are for opaque pointers
// and don't have the same typedef conflict.
struct SDL_Window;
struct SDL_Renderer;
union SDL_Event;


#ifdef __cplusplus
extern "C" {
#endif

void ui_init(SDL_Window* window, SDL_Renderer* renderer);
void ui_shutdown();
void ui_process_event(const SDL_Event* event);
bool ui_wants_capture_mouse();

void ui_begin_render();
// 3. REMOVED the "struct" keyword from the function parameter.
void ui_render(SimulationState* state);
void ui_end_render(SDL_Renderer* renderer);

#ifdef __cplusplus
}
#endif

#endif // UI_H