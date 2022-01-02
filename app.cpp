#include <configreader.h>
#include <LEDController.h>
#include <LEDEnsemble.h>
#include <SerialMessage.h>

void process_message(float in)
{
    std::cout << "received value: " << in << "\n";
}

// pass config files to function
int main(int argc, char **argv)
{
    
    // Set up Serial Communication
    MessageHandler handler;
    handler.SetDevice(SerialReader::Device::Arduino);
    handler.SetMessageHandler(Messages::AmbientModeMsg, process_message);
    handler.Start();
    

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