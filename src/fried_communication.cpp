#include "fried_communication.h"

#include "tcp_server_win.h"
#include "tcp_client_win.h"

namespace fried_communication
{

std::shared_ptr<Connection> FriedCommunication::createTCPServer(const std::string& ip, const uint16_t& port)
{
    std::shared_ptr<Connection> tcpServer { std::make_shared<TCPServer>(TCPServer(ip, port)) };
    tcpServer->create();
    m_connections.push_back(tcpServer);
    return tcpServer;
}

std::shared_ptr<Connection> FriedCommunication::createTCPClient(const std::string& ip, const uint16_t& port)
{
    std::shared_ptr<Connection> tcpClient { std::make_shared<TCPClient>(TCPClient(ip, port)) };
    tcpClient->create();
    m_connections.push_back(tcpClient);
    return tcpClient;
}

void FriedCommunication::closeConnection(const std::shared_ptr<Connection>& connection)
{
    connection->close();
    const std::vector<std::shared_ptr<Connection>>::iterator it
        { std::find(m_connections.begin(), m_connections.end(), connection) };
    m_connections.erase(it);
}

FriedCommunication::~FriedCommunication()
{
    for (const std::shared_ptr<Connection>& connection : m_connections)
        connection->close();
    m_connections.clear();
}

} // fried_communication