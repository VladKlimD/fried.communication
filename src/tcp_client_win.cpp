#include "tcp_client_win.h"

#include <iostream>

namespace fried_communication
{

TCPClient::TCPClient(const std::string& ip, const uint16_t& port) :
    m_ip { ip }, m_port { port }
{
    m_connectionType = ConnectionType::TCP_CLIENT;
}

TCPClient::~TCPClient()
{
    close();
}

void TCPClient::create()
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

    // setup client socket
    m_clientSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    if (m_clientSocket == INVALID_SOCKET)
    {
        std::cerr << "client socket failed!" << WSAGetLastError() << std::endl;
        close();
        return;
    }
    std::cout << "client socket is ok" << std::endl;

    // connect with server
    sockaddr_in clientService{};
    clientService.sin_family = AF_INET;
    InetPton(AF_INET, m_ip.c_str(), &clientService.sin_addr.s_addr);
    clientService.sin_port = htons(m_port);
    if (connect(m_clientSocket, reinterpret_cast<SOCKADDR*>(&clientService), sizeof(clientService)) == SOCKET_ERROR)
    {
        std::cerr << "client socket connect failed!" << std::endl;
        close();
        return;
    }
    std::cout << "client connect ok" << std::endl;
    std::cout << "ready for send and receive data" << std::endl;
}

void TCPClient::close()
{
    if (m_clientSocket != INVALID_SOCKET)
    {
        closesocket(m_clientSocket);
        m_clientSocket = INVALID_SOCKET;
    }

    WSACleanup();
}

} // fried_communication