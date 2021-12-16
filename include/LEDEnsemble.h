#include "LED_common.h"
#include "LEDVisualizer.h"


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

    Ensemble(Audio::Streamer* streamer);
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

};

