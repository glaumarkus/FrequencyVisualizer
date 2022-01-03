#include <SerialMessage.h>

/*

        float value;
        uint8_t* value_ptr = reinterpret_cast<uint8_t*>(&value);
        uint8_t* byte_ptr = m_buffer[start];

        value_ptr[0] = byte_ptr[3];
        value_ptr[1] = byte_ptr[2];
        value_ptr[2] = byte_ptr[1];
        value_ptr[3] = floatToConvert[0];
        //memcpy(&value, m_buffer, sizeof(float));
        // reverse byte order

        memcpy(&value_ptr[0], m_buffer[start + 3], 1);
        memcpy(&value_ptr[1], m_buffer[start + 2], 1);
        memcpy(&value_ptr[2], m_buffer[start + 1], 1);
        memcpy(&value_ptr[3], m_buffer[start + 0], 1);
        //std::memcpy((void*)&value, (void*)(m_buffer[start + 1]), 4);
        m_msg.push_back({type, value});
*/

void process_message(float in)
{
    std::cout << "received value: " << in << "\n";
}


int main()
{

    // Set up Serial Communication
    MessageHandler handler;
    handler.SetDevice(SerialReader::Device::Arduino);
    handler.SetMessageHandler(Messages::SilentModeMsg, process_message);
    handler.SetMessageHandler(Messages::AmbientModeMsg, process_message);
    handler.SetMessageHandler(Messages::MusicModeMsg, process_message);
    handler.Start();

    std::this_thread::sleep_for(std::chrono::seconds(5));
    handler.Stop();

    return 0;
}