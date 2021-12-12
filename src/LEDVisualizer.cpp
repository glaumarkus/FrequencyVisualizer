#include <LEDVisualizer.h>


LEDVisualizer::LEDVisualizer(float position, float brightness, std::initializer_list<int> leds) :
    m_leds{leds}
{
    // make colors for LEDs
    for (int i = 0; i < m_leds.size(); i++)
        m_colors.emplace_back(
            sinf(PI / 2 * static_cast<float>(i + 1) / m_leds.size()),   // r
            sinf(PI / 2 * position),                                    // g
            cosf(PI / 2 * position)                                     // b
        );
    
    // apply brightness
    for (auto& color : m_colors)
        color *= brightness;

    // fill rendercolors
    for (int i = 0; i < m_leds.size(); i++)
        m_rendercolors.emplace_back(static_cast<uint32_t>(Black));

}


LEDVisualizer::~LEDVisualizer()
{}

void LEDVisualizer::ProcessInput(float input)
{
    // scale to vector size
    input *= m_leds.size();

    // get floor
    int floors = std::floorf(input);

    // fill colors
    for (int i = 0; i < m_leds.size(); i++)
    {   
        float factor = i < input ? 1.0f : ApplyLimit(i - input, 0.0f, 1.0f);
        m_rendercolors[i] = static_cast<uint32_t>(m_basecolors[i] * factor);
    } 

}

void LEDVisualizer::Update()
{}

void LEDVisualizer::Render()
{
    for (int i = 0; i < m_leds.size(); i++)
        led_controller->ChangeLED(m_leds[i], m_rendercolors[i]);
    led_controller->Render();
}