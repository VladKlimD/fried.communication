#pragma once

#include "connection_interface.h"

#include <cstdint>
#include <string>
#include <winsock2.h>
#include <ws2tcpip.h>

#pragma comment(lib, "ws2_32.lib")

namespace fried_communication
{

class TCPClient final : public ConnectionInterface
{
public:
    TCPClient(ParserInterface* parser, const std::string& ip, const uint16_t& port);
    ~TCPClient() override;

    void sendData(const char* data, const size_t& dataSize) override;

    [[nodiscard]] inline std::string ip() const { return m_ip; }
    [[nodiscard]] inline uint16_t port() const { return m_port; }

private:
    void create() override;
    void close() override;
    void checkIncomingData() override;

    SOCKET m_clientSocket { INVALID_SOCKET };
    std::string m_ip;
    uint16_t m_port { UINT16_MAX };
};

} // fried_communication
