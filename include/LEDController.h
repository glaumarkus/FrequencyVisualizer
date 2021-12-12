#pragma once

#include "LED_common.h"

class LEDController
{
public:
    
    static LEDController* const led_controller;

private:

    LEDController();

    void ChangeLED(int idx, uint32_t color);
    void Render();

private:

    ws2811_t m_strip;

    constexpr long      TARGET_FREQ     = WS2811_TARGET_FREQ;
    constexpr int       GPIO_PIN        = 18;
    constexpr int       DMA             = 10;
    constexpr uint32_t  STRIP_TYPE      = WS2811_STRIP_GBR;
    constexpr int       LED_COUNT       = 32;


};


LEDController * const LEDController::led_controller = new LEDController();