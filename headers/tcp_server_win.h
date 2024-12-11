#pragma once

#include "connection_interface.h"

#include <cstdint>
#include <string>
#include <winsock2.h>
#include <ws2tcpip.h>

#pragma comment(lib, "ws2_32.lib")

namespace fried_communication
{

class TCPServer final : public Connection
{
public:
    TCPServer(const std::string& ip, const uint16_t& port);
    ~TCPServer() override;

    [[nodiscard]] inline std::string ip() const { return m_ip; }
    [[nodiscard]] inline uint16_t port() const { return m_port; }

private:
    void create() override;
    void close() override;

    SOCKET m_serverSocket { INVALID_SOCKET };
    SOCKET m_acceptSocket { INVALID_SOCKET };
    std::string m_ip;
    uint16_t m_port { UINT16_MAX };
};

} // fried_communication
