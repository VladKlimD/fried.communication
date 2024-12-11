#include "connection_interface.h"

namespace fried_communication
{

std::string connectionTypeToString(const ConnectionType& type)
{
    switch (type)
    {
        case ConnectionType::TCP_SERVER:
            return "TCP_SERVER";
        case ConnectionType::TCP_CLIENT:
            return "TCP_CLIENT";
        default:
            return "UNKNOWN";
    }
}

std::string connectionTypeToString(const uint8_t& type)
{
    return connectionTypeToString(static_cast<ConnectionType>(type));
}

} // fried_communication