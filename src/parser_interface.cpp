#include "parser_interface.h"

#include <iostream>

namespace fried_communication
{

ParserInterface::~ParserInterface()
{
    stop();
}

void ParserInterface::pushIncomingData(const char* data, const size_t& size)
{
    m_parsingMutex.lock();
    m_incomingData.emplace(data, size);
    m_parsingMutex.unlock();
}

void ParserInterface::start()
{
    if (m_parsingThreadRunning || m_parseThread)
        stop();

    m_parsingThreadRunning = true;
    m_parseThread = new std::thread(&ParserInterface::processIncomingData, this);
}

void ParserInterface::stop()
{
    m_parsingThreadRunning = false;
    if (!m_parseThread)
        return;

    m_parseThread->detach();
    delete m_parseThread;
    m_parseThread = nullptr;
}

void ParserInterface::parse(const char* data, const size_t& size)
{
    std::cout << "Parsing... " << std::string(data, size) << std::endl;
}

void ParserInterface::processIncomingData()
{
    while (m_parsingThreadRunning)
    {
        if (m_incomingData.empty())
            continue;

        m_parsingMutex.lock();
        std::string incomingData { m_incomingData.front() };
        m_incomingData.pop();
        m_parsingMutex.unlock();

        parse(incomingData.data(), incomingData.size());
    }
}

} // fried_communication