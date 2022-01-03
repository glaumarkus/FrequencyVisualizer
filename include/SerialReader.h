// C library headers
#include <stdio.h>
#include <cstring>
#include <string.h>
#include <string>
#include <iostream>

// Linux headers
#include <fcntl.h> // Contains file controls like O_RDWR
#include <errno.h> // Error integer and strerror() function
#include <termios.h> // Contains POSIX terminal control definitions
#include <unistd.h> // write(), read(), close()

// queue
#include "../dependencies/RaspberryPiAudio/include/tsqueue.h"

#pragma once

// reader locations
static const std::string ARDUINO = "/dev/ttyACM0";

// buffer size
constexpr size_t BUFFER_SIZE = 256;

// return struct
struct MessageFormat
{
    uint8_t msg;
    float val;
};

class SerialReader
{
public:

    enum class Device
    {
        Arduino
    };

    SerialReader();
    ~SerialReader();

    void Read();        // run in async
    void Write(const std::string& msgOut);
    bool SetDevice(Device device); 
    tsqueue<MessageFormat>& GetQueue();

private:

    void* m_inputprocessor;

    const std::string& GetDevicePath();

    Device m_device;
    int m_port;
    unsigned char m_buffer[BUFFER_SIZE];
    tsqueue<MessageFormat> m_msg;
    
};


