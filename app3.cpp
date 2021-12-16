#include <LEDEnsemble.h>

// pass card & device to function, e.g. "hw:1,0" -> card 1, device 0
int main(int argc, char **argv)
//int main()
{

    std::string device;
    
    if (argc > 1)
        device = argv[1];
    else
        device = "hw:1,0";
    
    std::cout << "[INFO] Starting Audio Streamer on device: " << device << std::endl;


    // Initialize Audio Stream
    Audio::Streamer streamer(device);

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