#pragma once

#include <stdint.h>
#include <string>
#include <vector>
#include <memory>

class ConnectionInterface
{
public:
    virtual ~ConnectionInterface() = default;

    // client
    virtual bool connect(const std::string& address, uint32_t port) = 0;
    virtual void disconnect() = 0;

    virtual bool send(const std::vector<uint8_t>& data) = 0;
    virtual std::vector<uint8_t> recieve(const size_t& size) = 0;

    virtual bool isConnected() const = 0;

    // server
    virtual bool startListening(uint32_t port) = 0;
    virtual std::shared_ptr<ConnectionInterface> acceptConnection() = 0;
    virtual void stopListening() = 0;
    virtual bool isListening() const = 0;
};