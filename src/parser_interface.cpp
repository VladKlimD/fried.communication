#include "parser_interface.h"

#include <iostream>
#include <iomanip>

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

    m_parseThread->join();
    delete m_parseThread;
    m_parseThread = nullptr;
}

void ParserInterface::parse(const char* data, const size_t& size)
{
    std::cout << "Parsing... ";
    for (size_t i = 0; i < size; ++i)
    {
        std::cout << std::hex
                  << std::setw(2)
                  << std::setfill('0')
                  << (static_cast<unsigned int>(static_cast<unsigned char>(data[i])))
                  << " ";
    }
    std::cout << std::endl;
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