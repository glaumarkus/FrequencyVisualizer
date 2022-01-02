#include <configreader.h>
#include <LEDController.h>
#include <LEDEnsemble.h>

// pass card & device to function, e.g. "hw:1,0" -> card 1, device 0
int main(int argc, char **argv)
//int main()
{

    // Load LED Configuration
    LEDConfiguration Lconfig;
    Lconfig.LoadConfig("../config/led.conf");

    // Initialize LED Controller
    LEDController(Lconfig.numLeds, Lconfig.brightness);

    // Load Audio Configuration
    Audio::AudioConfiguration Aconfig;
    Aconfig.LoadConfig("../config/audio.conf");

    // Initialize Audio Stream
    Audio::Streamer streamer(Aconfig);

    // Initialize LED Ensemble
    Ensemble ensemble(&streamer);

    if (ensemble.Initialize())
    {
        // Start Audio Stream
        streamer.Start();

        // Start Ensemble Loop
        ensemble.Start();

    }

    // Stop Audio Stream
    streamer.Stop();

    return 0;
}