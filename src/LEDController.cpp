#include <LEDController.h>
#include <Color.h>

LEDController::LEDController()
{
    // setup & init
    m_strip.freq = TARGET_FREQ;
    m_strip.dmanum = DMA;
    m_strip.channel[0].gpionum = GPIO_PIN;
    m_strip.channel[0].count = LED_COUNT;
    m_strip.channel[0].invert = 0;
    m_strip.channel[0].brightness = 100;
    m_strip.channel[0].strip_type = STRIP_TYPE;
    m_strip.channel[1].gpionum = 0;
    m_strip.channel[1].count = 0;
    m_strip.channel[1].invert = 0;
    m_strip.channel[1].brightness = 0;
    ws2811_init(&m_strip);
}

LEDController::~LEDController()
{
    for (int i = 0; i < LED_COUNT; i++)
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

static auto led_controller = std::make_shared<LEDController> ();

std::shared_ptr<LEDController> GetController()
{
    return led_controller;
}



/*
LEDController* LEDController::Get()
{
    if (!instance)
    instance = new LEDController;
    return instance;
}


void LEDController::ChangeLED(const int& idx, const uint32_t& color) {
    return this->IChangeLED(idx, color);
}


void LEDController::Render() {
    this->IRender();
}


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


void LEDController::IChangeLED(const int& idx, const uint32_t& color)
{
    m_strip.channel[0].leds[idx] = color;
}


void LEDController::IRender()
{
    ws2811_render(&m_strip);
}


LEDController* LEDController::instance = 0;
*/