#pragma once

#include "LED_common.h"

constexpr long      TARGET_FREQ     = WS2811_TARGET_FREQ;
constexpr int       GPIO_PIN        = 18;
constexpr int       DMA             = 10;
constexpr uint32_t  STRIP_TYPE      = WS2811_STRIP_GBR;

class LEDController
{
public:
    
    LEDController(int led_count, int brightness);
    ~LEDController();

    void ChangeBrightness(float brightness);
    void ChangeLED(int idx, uint32_t color);
    void Render();

private:

    ws2811_t m_strip;

};
