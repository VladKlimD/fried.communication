#include "fried_communication.h"

#include <iostream>
#include <cstdint>

int main(int, char**)
{
    std::cout << "**************************" << std::endl;
    std::cout << "Select type of connection:" << std::endl << std::endl;
    for (uint8_t type = (fried_communication::TCP_SERVER); type < fried_communication::END; ++type)
        std::cout << std::to_string(type) << ". " << fried_communication::connectionTypeToString(type) << std::endl;
    std::cout << "**************************" << std::endl << "> ";

    int selectedType { fried_communication::END };
    std::cin >> selectedType;
    if (selectedType == fried_communication::END)
    {
        std::cout << "Connection type is unknown";
        return -1;
    }

    std::cout << std::endl << fried_communication::connectionTypeToString(selectedType) << std::endl;
    std::cout << "**************************" << std::endl;
    std::shared_ptr<fried_communication::Connection> connection { nullptr };
    switch (static_cast<fried_communication::ConnectionType>(selectedType))
    {
        case fried_communication::TCP_SERVER:
        {
            std::string ip;
            std::cout << "Enter IP address: " << std::endl << "> ";
            std::cin >> ip;

            uint16_t port;
            std::cout << "Enter port number: " << std::endl << "> ";
            std::cin >> port;

            connection = fCommunication.createTCPServer(ip, port);
            break;
        }
        case fried_communication::TCP_CLIENT:
        {
            std::string ip;
            std::cout << "Enter IP address: " << std::endl << "> ";
            std::cin >> ip;

            uint16_t port;
            std::cout << "Enter port number: " << std::endl << "> ";
            std::cin >> port;

            connection = fCommunication.createTCPClient(ip, port);
            break;
        }
        default:
            break;
    }

    system("pause");
    return 0;
}
