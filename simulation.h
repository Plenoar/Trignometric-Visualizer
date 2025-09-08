#ifndef SIMULATION_H
#define SIMULATION_H

#include <stdbool.h>
#include <SDL3/SDL.h>

#define MAX_OSCILLATORS 16
#define MAX_PRESETS 16
#define MAX_TRAIL_POINTS 4096

typedef struct {
    float r, g, b, a;
} Color;

typedef struct 
{
    float x;
    float y;
}Vec2;

// trig functions 
typedef enum {
    FN_SIN, FN_COS, FN_TAN, FN_CSC, FN_SEC, FN_COT,
    FN_NEG_SIN, FN_NEG_COS, FN_NEG_TAN, FN_NEG_CSC, FN_NEG_SEC, FN_NEG_COT,
    FN_ZERO
} WaveFuncType;

// Enum for oscillator types
typedef enum {
    OS_LINE, OS_POINT
} OscillatorType;

// Enum for trail styles
typedef enum {
    TRAIL_POINTS, TRAIL_LINES, TRAIL_FADED_LINES
} TrailStyle;

// Global names for UI dropdowns
extern const char* G_WAVE_FUNC_NAMES[];
extern const char* G_TRAIL_STYLE_NAMES[];

typedef struct {
    char name[64];
    bool enabled;
    float base_x, base_y, amplitude;

    WaveFuncType p1_func_x; float p1_freq_x;
    WaveFuncType p1_func_y; float p1_freq_y;
    WaveFuncType p2_func_x; float p2_freq_x;
    WaveFuncType p2_func_y; float p2_freq_y;

    Color point1_colour, point2_colour, mid_point_colour;
    Vec2 point1;
    Vec2 point2;
} LineOscillator;

typedef struct {
    char name[64];
    bool enabled;
    float base_x, base_y, amplitude;

    WaveFuncType func_x; float freq_x;
    WaveFuncType func_y; float freq_y;

    Color point_colour;
    Vec2 point;
} PointOscillator;

typedef struct {
    SDL_FPoint points[MAX_TRAIL_POINTS];
    int head, count;
} PointTrail;

// Preset structure
typedef struct {
    const char* name;
    void* oscillators;
    int count;
    OscillatorType type;
    void* alloc_mem;
    float time_step;

    bool show_line , show_points , show_trail;
} Preset;

typedef struct {
    SDL_Window* window;
    SDL_Renderer* renderer;

    double time;
    float time_step;
    bool is_running;
    bool quit;
    
    bool line_oscillator_active;
    LineOscillator line_oscillators[MAX_OSCILLATORS];
    Color line_colour;
    int line_oscillator_count;

    bool point_oscillator_active;
    PointOscillator point_oscillators[MAX_OSCILLATORS];
    Color point_colour;
    int point_oscillator_count;

    bool show_lines, show_points, show_trails;
    TrailStyle trail_style;
    PointTrail line_trails[MAX_OSCILLATORS * 3];
    PointTrail point_trails[MAX_OSCILLATORS];
    Color background_colour;

    int screen_width , screen_height;
    float camera_x, camera_y, zoom;
    bool is_panning;
    int max_trail_points;

    Preset presets[MAX_PRESETS];
    int preset_count;
    char new_preset_name[64];
} SimulationState;

#endif // SIMULATION_H

