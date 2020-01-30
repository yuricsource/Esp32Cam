#pragma once

#include "BaseRouteHandler.h"

namespace Middleware
{
namespace Protocol
{

class WebsocketPath : public BaseRouteHandler
{
public:

private:
    void receivedData(const uint8_t *data, uint16_t length) override;

    void connectionStateChanged(ConnectionState state, ConnectionChangeReason reason) override;

    bool sendFrame(const uint8_t *data, uint16_t length) override;

	void setConnection() override;

	bool isTerminated() const override;

	bool start(BaseRouteHandler::ConnectionMode connectionMode, RemoteConnection *address, uint8_t processingIndex, uint8_t processingLogicalId) override;

	void terminate() override;

	void process() override;

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