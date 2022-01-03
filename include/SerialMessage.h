#include <unordered_map>
#include <atomic>
#include <functional>
#include <thread>
#include "SerialReader.h"

#pragma once


// message types
enum Messages : uint8_t
{
    SendAll = 0,        // Send all
    Brightness = 1,     // change brighness
    FFTScale = 2,       // update FFTScale
    DBScale = 3,        // update DB Scale
    SilentModeMsg = 10,
    MusicModeMsg = 11,      // change to music mode
    AmbientModeMsg = 12,    // change to ambient
    Red = 6,            // change r component of ambient
    Green = 7,          // change g component of ambient
    Blue = 8,           // change b component of ambient
    FreqPerBin = 9      // for placing bins
};

// state
enum States : uint8_t
{
    SilentMode,
    MusicMode,
    AmbientMode
};




class MessageHandler
{
public:

    MessageHandler();
    ~MessageHandler();

    bool SetDevice(SerialReader::Device device);
    void SetMessageHandler(Messages type, std::function<void(float)> f);
    void Start();
    void Stop();

private:

    void OnMessage(const MessageFormat& in);
    std::atomic<bool> m_stop {false}; 
    SerialReader m_reader;
    std::unordered_map<Messages, std::function<void(float)>> m_handler;

    std::thread m_reading;
    std::thread m_thread;
};

