#include <SerialMessage.h>


void process_message(float in)
{
    std::cout << "received value: " << in << "\n";
}


int main()
{

    // Set up Serial Communication
    MessageHandler handler;
    handler.SetDevice(SerialReader::Device::Arduino);
    handler.SetMessageHandler(Messages::AmbientModeMsg, process_message);
    handler.Start();
    return 0;
}