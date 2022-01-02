#include <LEDController.h>
#include <Color.h>

LEDController::LEDController(int led_count, int brightness)
{
    // setup & init
    m_strip.freq = TARGET_FREQ;
    m_strip.dmanum = DMA;
    m_strip.channel[0].gpionum = GPIO_PIN;
    m_strip.channel[0].count = led_count;
    m_strip.channel[0].invert = 0;
    m_strip.channel[0].brightness = brightness;
    m_strip.channel[0].strip_type = STRIP_TYPE;
    m_strip.channel[1].gpionum = 0;
    m_strip.channel[1].count = 0;
    m_strip.channel[1].invert = 0;
    m_strip.channel[1].brightness = 0;
    ws2811_init(&m_strip);
}

LEDController::~LEDController()
{
    for (int i = 0; i < m_strip.channel[0].count; i++)
        ChangeLED(i, uBlack);
    Render();
}

void LEDController::ChangeLED(int idx, uint32_t color)
{
    m_strip.channel[0].leds[idx] = color;
}

void LEDController::Render()
{
    ws2811_render(&m_strip);
}

void LEDController::ChangeBrightness(float brightness)
{
    m_strip.channel[0].brightness = brightness;   
}
