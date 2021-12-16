#pragma once

#include "LED_common.h"

constexpr long      TARGET_FREQ     = WS2811_TARGET_FREQ;
constexpr int       GPIO_PIN        = 18;
constexpr int       DMA             = 10;
constexpr uint32_t  STRIP_TYPE      = WS2811_STRIP_GBR;
constexpr int       LED_COUNT       = 110;

class LEDController
{
public:
    
    LEDController();
    ~LEDController();

    void ChangeLED(int idx, uint32_t color);
    void Render();

private:

    ws2811_t m_strip;

};

std::shared_ptr<LEDController> GetController();



/*
class LEDController {

public:

    LEDController(const LEDController&) = delete;
    LEDController(LEDController&&) = delete;

    LEDController& operator =(const LEDController&) = delete;
    LEDController& operator =(LEDController&&) = delete;

public:

    static LEDController* Get();
    void ChangeLED(const int& idx, const uint32_t& color);
    void Render();

private:
   
    LEDController();
    void IChangeLED(const int& idx, const uint32_t& color);
    void IRender();

private:
    
    static LEDController *instance;
    ws2811_t m_strip;    

};

*/