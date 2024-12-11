#include "tcp_server_win.h"

#include <iostream>

namespace fried_communication
{

TCPServer::TCPServer(const std::string& ip, const uint16_t& port) :
    m_ip { ip }, m_port { port }
{
    m_connectionType = ConnectionType::TCP_SERVER;
}

TCPServer::~TCPServer()
{
    close();
}

void TCPServer::create()
{
    // setup dll
    WSADATA wsaData;
    if (constexpr WORD wVersionRequested { MAKEWORD(2, 2) }; WSAStartup(wVersionRequested, &wsaData) != 0)
    {
        std::cerr << "WSAStartup failed!" << std::endl;
        return;
    }
    std::cout << "sock dll found" << std::endl;
    std::cout << "status: " << wsaData.szSystemStatus << std::endl;

    // setup server socket
    m_serverSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    if (m_serverSocket == INVALID_SOCKET)
    {
        std::cerr << "server socket failed!" << WSAGetLastError() << std::endl;
        close();
        return;
    }
    std::cout << "server socket is ok" << std::endl;

    // bind socket
    sockaddr_in service {};
    service.sin_family = AF_INET;
    InetPton(AF_INET, m_ip.c_str(), &service.sin_addr.s_addr);
    service.sin_port = htons(m_port);
    if (bind(m_serverSocket, reinterpret_cast<SOCKADDR*>(&service), sizeof(service)) == SOCKET_ERROR)
    {
        std::cerr << "server socket bind failed!" << WSAGetLastError() << std::endl;
        close();
        return;
    }
    std::cout << "server socket bind is ok" << std::endl;

    // initiate listen
    if (listen(m_serverSocket, 1) == SOCKET_ERROR)
    {
        std::cerr << "server socket listen failed!" << std::endl;
        close();
        return;
    }
    std::cout << "server socket listen is ok" << std::endl;

    // accept connection from client
    m_acceptSocket = accept(m_serverSocket, nullptr, nullptr);
    if (m_acceptSocket == INVALID_SOCKET)
    {
        std::cerr << "accept socket failed!" << std::endl;
        close();
        return;
    }
    std::cout << "accept socket is ok" << std::endl;
}

void TCPServer::close()
{
    if (m_serverSocket != INVALID_SOCKET)
    {
        closesocket(m_serverSocket);
        m_serverSocket = INVALID_SOCKET;
    }

    if (m_acceptSocket != INVALID_SOCKET)
    {
        closesocket(m_acceptSocket);
        m_acceptSocket = INVALID_SOCKET;
    }

    WSACleanup();
}

} // fried_communication