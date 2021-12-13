#pragma once

#include "LED_common.h"

class LEDController
{
public:
    
    LEDController();
    void ChangeLED(int idx, uint32_t color);
    void Render();

private:

    ws2811_t m_strip;

    static constexpr long      TARGET_FREQ     = WS2811_TARGET_FREQ;
    static constexpr int       GPIO_PIN        = 18;
    static constexpr int       DMA             = 10;
    static constexpr uint32_t  STRIP_TYPE      = WS2811_STRIP_GBR;
    static constexpr int       LED_COUNT       = 10;


};

static LEDController led_controller;