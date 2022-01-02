#include <configreader.h>
#include <LEDController.h>
#include <LEDEnsemble.h>

// pass config files to function
int main(int argc, char **argv)
{

    // Load LED Configuration
    LEDConfiguration Lconfig;
    Lconfig.LoadConfig("../config/led.conf");

    // Initialize LED Controller
    LEDController controller(Lconfig.numLeds, Lconfig.brightness);

    // Load Audio Configuration
    Audio::AudioConfiguration Aconfig;
    Aconfig.LoadConfig("../config/audio.conf");

    // Initialize Audio Stream
    Audio::Streamer streamer(Aconfig);

    // Initialize LED Ensemble
    Ensemble ensemble(Lconfig, controller, &streamer);

    // Start threads
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