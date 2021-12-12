#pragma once

#include "common.h"

#include "Color.h"
#include "LEDController.h"

constexpr int NUM_LEDS = 10;

class LEDVisualizer
{
public:

    LEDVisualizer(float position, float brightness, std::initializer_list<int> leds);
    ~LEDVisualizer();

    void ProcessInput(const float& input);
    void Update();
    void Render();

private:

    std::vector<int> m_leds; 
    std::vector<Color> m_basecolors;
    std::vector<uint32_t> m_rendercolors; 

};

