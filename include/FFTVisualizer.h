#pragma once

#include <vector>
#include <SDL2/SDL.h>
#include <SDL_ttf.h>
#include <Audio.h>

// constexpr int BINS = 25;
constexpr int BINS = 40;
constexpr int BIN_MARGIN = 2;
constexpr float PI = 3.141592f;
constexpr int FONT_SIZE = 15;

// scale of grouping bins
constexpr float SCALE_EXP = 1.45f;

// max increase
constexpr float MAX_INC = 0.3f;

// max decrease
constexpr float MAX_DECAY = -0.05f;

// bins to skip
constexpr int START = 5;



class CApp
{
public:

    enum class State : uint8_t
    {
        NotInitialized,
        ReadyToRun,
        Running,
		Stopped
    };

    CApp(uint16_t width, uint16_t height, Audio::Streamer* streamer);
    ~CApp();
    
    bool Initialize();
    void Start();
    void Stop();

private:

    // internal loop
    void ProcessInput();
    void Update();
    void Render();

    // dimensions
    uint16_t m_width;
    uint16_t m_heigth;

    // sdl stuff
    SDL_Window* m_window;
    SDL_Renderer* m_renderer;

    // font specific
    TTF_Font* m_font;
    SDL_Surface* m_fontsurface;
    SDL_Texture* m_fonttexture;

    // current state
    State m_state;

    // Streamer pointer
    Audio::Streamer* m_streamer;

    // input stream
	tsqueue<Audio::sample_block>& m_stream;

    // last samples
    Audio::sample_block m_lastSamples;

};

