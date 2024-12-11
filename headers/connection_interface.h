#pragma once

#include <thread>
#include <cstdint>
#include <string>

namespace fried_communication
{

enum ConnectionType : uint8_t
{
    TCP_SERVER,
    TCP_CLIENT,
    END
};

std::string connectionTypeToString(const ConnectionType& type);
std::string connectionTypeToString(const uint8_t& type);

class Connection
{
public:
    virtual ~Connection() = default;
    friend class FriedCommunication;

protected:
    virtual void create() = 0;
    virtual void close() = 0;

    ConnectionType m_connectionType { ConnectionType::END };
};

} // fried_communication
