#pragma once

#include "connection_interface.h"

#include <cstdint>
#include <string>
#include <vector>
#include <memory>

#define fCommunication fried_communication::FriedCommunication::instance()

namespace fried_communication
{

typedef std::shared_ptr<ConnectionInterface> FConnection;

class FriedCommunication
{
public:
    inline static FriedCommunication& instance()
    {
        static FriedCommunication friedCommunication;
        return friedCommunication;
    }

    FConnection createTCPServer(const std::string& ip, const uint16_t& port);
    FConnection createTCPClient(const std::string& ip, const uint16_t& port);
    void closeConnection(const FConnection& connection);

private:
    FriedCommunication() = default;
    ~FriedCommunication();

    std::vector<FConnection> m_connections {};
};

} // fried_communication