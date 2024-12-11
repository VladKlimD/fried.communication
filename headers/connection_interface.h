#pragma once

#include <cstdint>
#include <string>
#include <memory>

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

class ConnectionInterface
{
public:
    virtual ~ConnectionInterface() = default;
    friend class FriedCommunication;

    [[nodiscard]] inline ConnectionType connectionType() const { return m_connectionType; }
    [[nodiscard]] inline std::string connectionTypeStr() const { return connectionTypeToString(m_connectionType); }

protected:
    virtual void create() = 0;
    virtual void close() = 0;

    ConnectionType m_connectionType { ConnectionType::END };
};

} // fried_communication
