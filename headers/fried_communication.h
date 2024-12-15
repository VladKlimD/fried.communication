#pragma once

#include "connection_interface.h"

#include <cstdint>
#include <string>
#include <vector>
#include <memory>

#define FCommunication fried_communication::FriedCommunication::instance()

namespace fried_communication
{

using FConnection = std::shared_ptr<ConnectionInterface>;

class FriedCommunication
{
public:
    inline static FriedCommunication& instance()
    {
        static FriedCommunication friedCommunication;
        return friedCommunication;
    }

    FConnection createTCPServer(ParserInterface* parser, const std::string& ip, const uint16_t& port);
    FConnection createTCPClient(ParserInterface* parser, const std::string& ip, const uint16_t& port);
    void closeConnection(const FConnection& connection);
    void closeAllConnections();

private:
    FriedCommunication() = default;
    ~FriedCommunication();

    std::vector<FConnection> m_connections {};
};

} // fried_communication