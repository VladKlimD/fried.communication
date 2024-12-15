#include "fried_communication.h"

#include "tcp_server_win.h"
#include "tcp_client_win.h"

namespace fried_communication
{

FConnection FriedCommunication::createTCPServer(const std::string& ip, const uint16_t& port)
{
    FConnection tcpServer { std::make_shared<TCPServer>(TCPServer(ip, port)) };
    tcpServer->create();
    m_connections.push_back(tcpServer);
    return tcpServer;
}

FConnection FriedCommunication::createTCPClient(const std::string& ip, const uint16_t& port)
{
    FConnection tcpClient { std::make_shared<TCPClient>(TCPClient(ip, port)) };
    tcpClient->create();
    m_connections.push_back(tcpClient);
    return tcpClient;
}

void FriedCommunication::closeConnection(const FConnection& connection)
{
    connection->close();
    const std::vector<FConnection>::iterator it
        { std::find(m_connections.begin(), m_connections.end(), connection) };
    m_connections.erase(it);
}

void FriedCommunication::closeAllConnections()
{
    for (const FConnection& connection : m_connections)
        connection->close();
    m_connections.clear();
}

FriedCommunication::~FriedCommunication()
{
    closeAllConnections();
}

} // fried_communication