#pragma once

#include "BaseRouteHandler.h"

namespace Middleware
{
namespace Protocol
{

class WebsocketPath : public BaseRouteHandler
{
public:
    void ReceivedData(const uint8_t *data, uint16_t length) override;

    void ConnectionStateChanged(ConnectionState state, ConnectionChangeReason reason) override;

    bool SendFrame(const uint8_t *data, uint16_t length) override;

private:
    /// @brief	Hide Copy constructor.
    WebsocketPath(const WebsocketPath &) = delete;

    /// @brief	Hide Assignment operator.
    WebsocketPath &operator=(const WebsocketPath &) = delete;

    /// @brief	Hide Move constructor.
    WebsocketPath(WebsocketPath &&) = delete;

    /// @brief	Hide Move assignment operator.
    WebsocketPath &operator=(WebsocketPath &&) = delete;
};
} // namespace Protocol
} // namespace Middleware