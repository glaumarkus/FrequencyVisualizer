#include <FFTVisualizer.h>

// pass card & device to function, e.g. "hw:1,0" -> card 1, device 0
// int main(int argc, char **argv)
int main()
{

    std::string device = "hw:1,0";
    /*
    if (argc > 1)
        device = argv[1];
    else
        device = "hw:1,0";
    */
    std::cout << "[INFO] Starting Audio Streamer on device: " << device << std::endl;


    // Initialize Audio Stream
    Audio::Streamer streamer(device);
    tsqueue<Audio::sample_block> stream;
    stream.push_back(Audio::sample_block{
        0.1, 1.0, 0.2, 
        0.2, 0.7, 0.3, 
        0.1, 0.5, 0.4, 
        0.32, 0.3, 0.5, 
        0.24, 0.1, 0.8,
        });

    // Initialize SDL Application
    CApp app(1280, 768, streamer.GetFFTSamples());
    //CApp app(400, 200, stream);
    //CApp app(1280, 768, stream);
    if (app.Initialize())
    {
        // Start Audio Stream
        streamer.Start();

        // Start SDL Loop
        app.Start();

    }

    // Stop Audio Stream
    streamer.Stop();

    return 0;
}