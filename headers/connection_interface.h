#pragma once

#include <cstdint>
#include <string>
#include <thread>

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

    virtual void sendData(const char* data, const size_t& dataSize) = 0;

    [[nodiscard]] inline ConnectionType connectionType() const { return m_connectionType; }
    [[nodiscard]] inline std::string connectionTypeStr() const { return connectionTypeToString(m_connectionType); }
    [[nodiscard]] inline bool isListeningIncomingData() const { return m_isListeningIncomingData; }

protected:
    virtual void create() = 0;
    virtual void close() = 0;
    virtual void checkIncomingData() = 0;

    void listenIncomingData(bool start);

    ConnectionType m_connectionType { ConnectionType::END };

private:
    std::thread* m_checkingIncomingThread { nullptr };
    bool m_isListeningIncomingData { false };
};

} // fried_communication
