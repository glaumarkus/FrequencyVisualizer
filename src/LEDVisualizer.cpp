#include <LEDVisualizer.h>
#include <LEDController.h>
#include <Utility.h>

// odd
LEDVisualizer2::LEDVisualizer2(float position, float brightness, std::initializer_list<int> leds) :
    m_leds{leds},
    m_basecolors(leds.size()),
    m_rendercolors(leds.size()),
    m_center(0)
{
    // set center
    m_center = m_leds.size() / 2;

    // thats ok...
    
    // make colors for LEDs
    for (int i = 0; i < m_center; i++)
    {
        auto tmp = Color(
            cosf(PI / 2 * static_cast<float>(i + 1) / (m_center * 2)),                 // r
            sinf(PI  * position),                                    // g
            cosf(PI  * position)                                     // b
        );

        m_basecolors[m_center + 1 + i] = tmp;
        m_basecolors[m_center - 1 - i] = tmp;
    }

    // add middle one
    m_basecolors[m_center] = Color(
        cosf(PI / 2 * m_center / (m_center * 2)),
        sinf(PI * position),                                    
        cosf(PI * position)
    );

    // test
    /*
    for (auto& color : m_basecolors)
        color = Color
        (
            cosf(PI / 4 * position),
            sinf(PI / 6 * position),                                    
            sinf(PI / 2 * position)
        );
    */

   
    // fill rendercolors
    
    for (int i = 0; i < m_leds.size(); i++)
        m_rendercolors[i] = uBlack;
    
}


LEDVisualizer2::LEDVisualizer2(float position, float brightness, const std::vector<int>& leds) :
    m_leds(leds),
    m_basecolors(leds.size()),
    m_rendercolors(leds.size()),
    m_center(0)
{

    // set center
    m_center = m_leds.size() / 2;
    
    // make colors for LEDs
    for (int i = 0; i < m_center; i++)
    {
        auto tmp = Color(
            cosf(PI / 2 * static_cast<float>(i + 1) / (m_center * 2)),                 // r
            sinf(PI  * position),                                    // g
            cosf(PI  * position)                                     // b
        );

        m_basecolors[m_center + 1 + i] = tmp;
        m_basecolors[m_center - 1 - i] = tmp;
    }

    // add middle one
    m_basecolors[m_center] = Color(
        cosf(PI / 2 * m_center / (m_center * 2)),
        sinf(PI * position),                                    
        cosf(PI * position)
    );

        
    for (int i = 0; i < m_leds.size(); i++)
        m_rendercolors[i] = uBlack;

}

LEDVisualizer2::~LEDVisualizer2()
{}

void LEDVisualizer2::ProcessInput(float input)
{                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                      
    // scale to vector size
    input *= (m_center + 1);

    // get floor
    int floors = floorf(input);

    // fill center
    m_rendercolors[m_center] = static_cast<uint32_t>(m_basecolors[m_center]);

    // fill colors
    for (int i = 0; i < m_center; i++)
    {   
        float factor = ApplyLimit(input - i - 1, 0.0f, 1.0f);
        
        if (factor < 0.0001f)
        {
            m_rendercolors[m_center + 1 + i] = uBlack;
            m_rendercolors[m_center - 1 - i] = uBlack;
        }
        else
        {
            m_rendercolors[m_center + 1 + i] = static_cast<uint32_t>(m_basecolors[i] * factor);
            m_rendercolors[m_center - 1 - i] = static_cast<uint32_t>(m_basecolors[i] * factor);
        } 

    } 

}

void LEDVisualizer2::Update()
{}

void LEDVisualizer2::Render()
{
    auto controller = GetController();
    for (int i = 0; i < m_leds.size(); i++)
        controller->ChangeLED(m_leds[i], m_rendercolors[i]);
}




/*
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
    LEDController* controller = controller->Get();
    for (int i = 0; i < m_leds.size(); i++)
        controller->ChangeLED(m_leds[i], uBlack);
    
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
    LEDController* controller = controller->Get();
    for (int i = 0; i < m_leds.size(); i++)
        controller->ChangeLED(m_leds[i], m_rendercolors[i]);
   
}
*/
