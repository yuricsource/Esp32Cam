#pragma once

#include "Hardware.h"
#include "WifiService.h"
#include "HttpServer.h"
#include "TimeLimit.h"
 #include "BaseConnection.h"

namespace Applications
{

using Hal::TimeLimit;

class GatewayService
{
public:
    GatewayService();

private:

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