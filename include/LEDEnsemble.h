#include "LED_common.h"
#include "LEDVisualizer.h"
#include "configreader.h"


class Ensemble
{
public:

    enum class State : uint8_t
    {
        NotInitialized,
        ReadyToRun,
        Running,
		Stopped
    };

    Ensemble(LEDConfiguration& config, LEDController& controller, Audio::Streamer* streamer);
    ~Ensemble();

    void AddVisualizer(const LEDVisualizer2& vis);
    bool Initialize();
    void Start();
    void Stop();    

private:

    // internal loop
    void ProcessInput();
    void Update();
    void Render();

    // current state
    State m_state;

    // Streamer pointer
    Audio::Streamer* m_streamer;

    // input stream
	tsqueue<Audio::sample_block>& m_stream;

    // last samples
    Audio::sample_block m_lastSamples;

    // visualizers
    std::vector<LEDVisualizer2> m_visualizers;

    // controller
    LEDController& m_controller;

    // mutable config
    LEDConfiguration& m_config;

};

