#include "connection_interface.h"

namespace fried_communication
{

std::string connectionTypeToString(const ConnectionType& type)
{
    switch (type)
    {
        case ConnectionType::TCP_SERVER:
            return "TCP_SERVER";
        case ConnectionType::TCP_CLIENT:
            return "TCP_CLIENT";
        default:
            return "UNKNOWN";
    }
}

std::string connectionTypeToString(const uint8_t& type)
{
    return connectionTypeToString(static_cast<ConnectionType>(type));
}

void ConnectionInterface::listenIncomingData(const bool start)
{
    if (start)
    {
        if (m_checkingIncomingThread)
            return;

        m_isListeningIncomingData = true;
        m_checkingIncomingThread = new std::thread(&ConnectionInterface::checkIncomingData, this);
    }
    else
    {
        if (!m_checkingIncomingThread)
            return;

        m_isListeningIncomingData = false;
        m_checkingIncomingThread->detach();

        delete m_checkingIncomingThread;
        m_checkingIncomingThread = nullptr;
    }
}

} // fried_communication