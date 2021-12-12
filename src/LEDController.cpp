#include <LEDController.h>


LEDController::LEDController()
{
    // setup & init
    led_strip.freq = TARGET_FREQ;
    led_strip.dmanum = DMA;
    led_strip.channel[0].gpionum = GPIO_PIN;
    led_strip.channel[0].count = LED_COUNT;
    led_strip.channel[0].invert = 0;
    led_strip.channel[0].brightness = 255;
    led_strip.channel[0].strip_type = STRIP_TYPE;
    led_strip.channel[1].gpionum = 0;
    led_strip.channel[1].count = 0;
    led_strip.channel[1].invert = 0;
    led_strip.channel[1].brightness = 0;
    ws2811_init(&m_strip);
}

void LEDController::ChangeLED(int idx, uint32_t color)
{
    m_strip->channel[0].leds[idx] = color;
}

void LEDController::Render()
{
    ws2811_render(&m_strip);
}
