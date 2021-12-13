#include <LEDVisualizer.h>
#include "LEDController.h"


LEDVisualizer::LEDVisualizer(float position, float brightness, std::initializer_list<int> leds) :
    m_leds{leds}
{
    // make colors for LEDs
    for (int i = 0; i < m_leds.size(); i++)
        m_basecolors.emplace_back(
            sinf(PI / 2 * static_cast<float>(i + 1) / m_leds.size()),   // r
            sinf(PI / 2 * position),                                    // g
            cosf(PI / 2 * position)                                     // b
        );
    
    // apply brightness
    for (auto& color : m_basecolors)
        color *= brightness;

    // fill rendercolors
    for (int i = 0; i < m_leds.size(); i++)
        m_rendercolors.emplace_back(static_cast<uint32_t>(Black));

}


LEDVisualizer::~LEDVisualizer()
{
    for (int i = 0; i < m_leds.size(); i++)
        led_controller.ChangeLED(m_leds[i], static_cast<uint32_t>(Black));
    
    // this should only happen after everything is done
    led_controller.Render();
}

void LEDVisualizer::ProcessInput(float input)
{
    // scale to vector size
    input *= m_leds.size();

    // get floor
    int floors = floorf(input);

    // fill colors
    for (int i = 0; i < m_leds.size(); i++)
    {   
        float factor = ApplyLimit(input - i, 0.0f, 1.0f);
        //float factor = i < (input - 1) ? 1.0f : ( ( input - i ) < 1.0f ? ApplyLimit(i - input, 0.0f, 1.0f) : 0.0f);
        m_rendercolors[i] = static_cast<uint32_t>(m_basecolors[i] * factor);
    } 

}

void LEDVisualizer::Update()
{}

void LEDVisualizer::Render()
{
    for (int i = 0; i < m_leds.size(); i++)
        led_controller.ChangeLED(m_leds[i], m_rendercolors[i]);
    
    // this should only happen after everything is done
    led_controller.Render();
    
}

// odd

LEDVisualizer2::LEDVisualizer2(float position, float brightness, std::initializer_list<int> leds) :
    m_leds{leds},
    m_center(0)
{
    // set center
    m_center = m_leds.size() / 2;

    // resize 
    m_basecolors.resize(m_leds.size());

    // make colors for LEDs
    for (int i = 0; i < m_center; i++)
    {
        auto tmp = Color(
            sinf(PI / 2 * static_cast<float>(i + 1) / (m_center + 1)),                 // r
            sinf(PI / 2 * position),                                    // g
            cosf(PI / 2 * position)                                     // b
        );

        m_basecolors[m_center + 1 + i] = tmp;
        m_basecolors[m_center - 1 - i] = tmp;
    }

    // add middle one
    m_basecolors[m_center] = Color(
        sinf(PI / 2 * static_cast<float>(1) / (m_center + 1)),
        sinf(PI / 2 * position),                                    // g
        cosf(PI / 2 * position)
    );


    // apply brightness
    for (auto& color : m_basecolors)
        color *= brightness;

    // fill rendercolors
    for (int i = 0; i < m_leds.size(); i++)
        m_rendercolors.emplace_back(static_cast<uint32_t>(Black));

}


LEDVisualizer2::~LEDVisualizer2()
{
    for (int i = 0; i < m_leds.size(); i++)
        led_controller.ChangeLED(m_leds[i], static_cast<uint32_t>(Black));
    
    // this should only happen after everything is done
    led_controller.Render();
}

void LEDVisualizer2::ProcessInput(float input)
{
    // scale to vector size
    input *= (m_center + 1);

    // get floor
    int floors = floorf(input);

    // fill center
    float factor = ApplyLimit(input, 0.0f, 1.0f);
    m_rendercolors[m_center] = static_cast<uint32_t>(m_basecolors[m_center] * factor);

    // fill colors
    for (int i = 0; i < m_center; i++)
    {   
        factor = ApplyLimit(input - i - 1, 0.0f, 1.0f);
        m_rendercolors[m_center + 1 + i] = static_cast<uint32_t>(m_basecolors[i] * factor);
        m_rendercolors[m_center - 1 - i] = static_cast<uint32_t>(m_basecolors[i] * factor);
    } 

}

void LEDVisualizer2::Update()
{}

void LEDVisualizer2::Render()
{
    for (int i = 0; i < m_leds.size(); i++)
        led_controller.ChangeLED(m_leds[i], m_rendercolors[i]);
    
    // this should only happen after everything is done
    led_controller.Render();
    
}