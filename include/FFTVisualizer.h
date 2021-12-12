#pragma once


#include "LED_common.h"
#include <SDL2/SDL.h>
#include <SDL_ttf.h>



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
    /*
    TTF_Font* m_font;
    SDL_Surface* m_fontsurface;
    SDL_Texture* m_fonttexture;
    */

    // current state
    State m_state;

    // Streamer pointer
    Audio::Streamer* m_streamer;

    // input stream
	tsqueue<Audio::sample_block>& m_stream;

    // last samples
    Audio::sample_block m_lastSamples;

#ifdef __arm__

    #include <wiringPiI2C.h>
    #include <ws2811.h>

#endif

};

