#pragma once

#include "common.h"
#include "Color.h"
#include "LEDController.h"


class LEDVisualizer
{
public:

    LEDVisualizer(float position, float brightness, std::initializer_list<int> leds);
    ~LEDVisualizer();

    void ProcessInput(float input);
    void Update();
    void Render();

private:

    std::vector<int> m_leds; 
    std::vector<Color> m_basecolors;
    std::vector<uint32_t> m_rendercolors; 

};

class LEDVisualizer2
{
public:

    LEDVisualizer2(LEDController& controller, float position, const std::vector<int>& leds);
    LEDVisualizer2(LEDController& controller, float position, std::initializer_list<int> leds);
    ~LEDVisualizer2();

    void ProcessInput(float input);
    void Update();
    void Render();

private:

    bool m_flag = false;
    int m_center;
    std::vector<int> m_leds; 
    std::vector<Color> m_basecolors;
    std::vector<uint32_t> m_rendercolors; 
    LEDController& m_controller;

};


