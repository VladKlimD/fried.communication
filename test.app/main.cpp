#include "fried_communication.h"

#include <iostream>
#include <cstdint>

std::string userInput()
{
    std::string input;
    std::getline(std::cin, input);
    if (input == "exit")
    {
        FCommunication.closeAllConnections();
        std::exit(EXIT_SUCCESS);
    }
    return input;
}

[[noreturn]] int main(int, char**)
{
    std::cout << "**************************" << std::endl;
    std::cout << "Select type of connection:" << std::endl << std::endl;
    for (uint8_t type = (fried_communication::TCP_SERVER); type < fried_communication::END; ++type)
        std::cout << std::to_string(type) << ". " << fried_communication::connectionTypeToString(type) << std::endl;
    std::cout << "**************************" << std::endl << "> ";

    int selectedType { std::stoi(userInput()) };
    if (fried_communication::connectionTypeToString(selectedType) == "UNKNOWN")
    {
        std::cout << "Connection type is unknown";
        return -1;
    }

    std::cout << std::endl << fried_communication::connectionTypeToString(selectedType) << std::endl;
    std::cout << "**************************" << std::endl;
    fried_communication::FConnection connection { nullptr };
    switch (static_cast<fried_communication::ConnectionType>(selectedType))
    {
        case fried_communication::TCP_SERVER:
        {
            std::cout << "Enter IP address: " << std::endl << "> ";
            const std::string ip { userInput() };

            std::cout << "Enter port number: " << std::endl << "> ";
            const uint16_t port { static_cast<uint16_t>(std::stoi(userInput())) };

            connection = FCommunication.createTCPServer(new fried_communication::ParserInterface(), ip, port);
            break;
        }
        case fried_communication::TCP_CLIENT:
        {
            std::cout << "Enter IP address: " << std::endl << "> ";
            const std::string ip { userInput() };

            std::cout << "Enter port number: " << std::endl << "> ";
            const uint16_t port { static_cast<uint16_t>(std::stoi(userInput())) };

            connection = FCommunication.createTCPClient(new fried_communication::ParserInterface(), ip, port);
            break;
        }
        default:
            break;
    }

    while (true)
    {
        std::cout << std::endl << "Type data to send: " << std::endl << "> ";
        std::string data { userInput() };
        connection->sendData(data.data(), data.size());
    }

    FCommunication.closeAllConnections();
}
