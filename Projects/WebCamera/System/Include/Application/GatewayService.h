#pragma once

#include "Hardware.h"
#include "WifiService.h"
#include "HttpServer.h"
#include "TimeLimit.h"
#include "ConfigurationCommon.h"
#include "BaseConnection.h"
#include "BaseRouteHandler.h"
#include "TcpConnection.h"
#include "Logger.h"

namespace Applications
{

using Hal::TimeLimit;
using Middleware::Common::ProtocolType;
using Middleware::Common::TransportLayerType;
using Middleware::Protocol::BaseConnection;
using Middleware::Protocol::BaseRouteHandler;
using Middleware::Protocol::TcpConnection;
using Middleware::Protocol::RemoteConnection;
using Middleware::Utilities::Logger;

class GatewayService : public cpp_freertos::Thread
{
public:
    GatewayService();

private:
    struct RoutePathConnection
    {
        RoutePathConnection() : Connection(nullptr),
                                RouteHandler(nullptr),
                                Used(false)
        {
        }

        BaseConnection *Connection;
        BaseRouteHandler *RouteHandler;
        TransportLayerType TransportLayer;
        ProtocolType Protocol;
        bool Used;

        inline constexpr bool ConnectionValid() const
        {
            return Connection != nullptr;
        }
    };

protected:
    void Run() override;

private:
    RoutePathConnection _connectionPath;

private:
    /// @brief	Hide Copy constructor.
    GatewayService(const GatewayService &) = delete;

    /// @brief	Hide Assignment operator.
    GatewayService &operator=(const GatewayService &) = delete;

    /// @brief	Hide Move constructor.
    GatewayService(GatewayService &&) = delete;

    /// @brief	Hide Move assignment operator.
    GatewayService &operator=(GatewayService &&) = delete;
};

} // namespace Applications