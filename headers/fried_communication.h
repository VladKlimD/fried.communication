#pragma once

#include "connection_interface.h"

#include <cstdint>
#include <string>
#include <vector>
#include <memory>

#define fCommunication fried_communication::FriedCommunication::instance()

namespace fried_communication
{

class FriedCommunication
{
public:
    inline static FriedCommunication& instance()
    {
        static FriedCommunication friedCommunication;
        return friedCommunication;
    }

    std::shared_ptr<Connection> createTCPServer(const std::string& ip, const uint16_t& port);
    std::shared_ptr<Connection> createTCPClient(const std::string& ip, const uint16_t& port);
    void closeConnection(const std::shared_ptr<Connection>& connection);

private:
    FriedCommunication() = default;
    ~FriedCommunication();

    std::vector<std::shared_ptr<Connection>> m_connections {};
};

} // fried_communication