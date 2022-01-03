#include <SerialMessage.h>


MessageHandler::MessageHandler()
{}

MessageHandler::~MessageHandler()
{
    Stop();
    if (m_reading.joinable())
        m_reading.join();
    std::cout << "Stopped Reading Serial\n";
    if (m_thread.joinable())
        m_thread.join();
    std::cout << "Stopped Processing Messages\n";

}

bool MessageHandler::SetDevice(SerialReader::Device device)
{
    return m_reader.SetDevice(device);
}

void MessageHandler::SetMessageHandler(Messages type, std::function<void(float)> f)
{
    m_handler[type] = f;
}

void MessageHandler::Start()
{
    m_reading = std::thread([this]()
    {
        while(!m_stop.load(std::memory_order_relaxed))
        {
            std::this_thread::sleep_for(std::chrono::milliseconds(10));
            m_reader.Read();
        }
            
    });

    m_thread = std::thread([this]()
    {
        while(!m_stop.load(std::memory_order_relaxed))
        {
            auto& queue = m_reader.GetQueue();
            queue.wait();
            auto msg = queue.pop_front();
            OnMessage(msg);
        }
    });
    
}

void MessageHandler::Stop()
{
    m_stop = true;
}

void MessageHandler::OnMessage(const MessageFormat& in)
{
    /*
    e.g.
    1 0.58991
    2 0.172345
    4 1
    5 1
    */

    // call with input
    auto f = m_handler[static_cast<Messages>(in.msg)];
    std::cout << "Received Message: " << (int)in.msg << "\n";
    f(in.val);
}