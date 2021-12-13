#include <LEDController.h>


LEDController::LEDController()
{
    // setup & init
    m_strip.freq = TARGET_FREQ;
    m_strip.dmanum = DMA;
    m_strip.channel[0].gpionum = GPIO_PIN;
    m_strip.channel[0].count = LED_COUNT;
    m_strip.channel[0].invert = 0;
    m_strip.channel[0].brightness = 255;
    m_strip.channel[0].strip_type = STRIP_TYPE;
    m_strip.channel[1].gpionum = 0;
    m_strip.channel[1].count = 0;
    m_strip.channel[1].invert = 0;
    m_strip.channel[1].brightness = 0;
    ws2811_init(&m_strip);
}

void LEDController::ChangeLED(int idx, uint32_t color)
{
    m_strip.channel[0].leds[idx] = color;
}

void LEDController::Render()
{
    ws2811_render(&m_strip);
}
