#pragma once

#include <string>
#include <queue>
#include <thread>
#include <mutex>

namespace fried_communication
{

class ParserInterface
{
public:
    ParserInterface() = default;
    virtual ~ParserInterface();

    void pushIncomingData(const char* data, const size_t& size);
    void start();
    void stop();

private:
    std::queue<std::string> m_incomingData;
    std::thread* m_parseThread { nullptr };
    std::mutex m_parsingMutex;
    bool m_parsingThreadRunning { false };

    virtual void parse(const char* data, const size_t& size);
    void processIncomingData();
};

} // fried_communication
