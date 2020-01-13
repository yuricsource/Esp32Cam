#pragma once

#include "Hardware.h"
#include "WifiService.h"
#include "HttpServer.h"
#include "TimeLimit.h"
// #include "BaseConnection.h"

namespace Applications
{

using Hal::TimeLimit;

class GatewayService
{
public:
    GatewayService();

private:

// struct RoutePath
// {
// 	RoutePath() :
// 		PathLogicalId(0),
// 		ConfigChanged(false),
// 		Connection(nullptr),
// 		PathHandler(nullptr),
// 		RemoteEnd(),
// 		TestConnectionCount(0)
// 	{
// 	}
    
// 	void ResetPath()
// 	{
// 		PathLogicalId = 0;
// 		ConfigChanged = false;
// 		Connection = nullptr;
// 		PathHandler = nullptr;
// 		RemoteEnd = {};
// 		TestConnectionCount = 0;
// 		TestConnectionTl.Reset();
// 		LastConnectionActiveTl.Reset();
// 	}
    
// 	bool ConfigChanged;
// 	BaseConnection* Connection;
// 	BasePathHandler* PathHandler = nullptr;
// 	LogicalIdType PathLogicalId;
// 	RemoteEndPoint RemoteEnd;
    
// 	/// @brief	Time when connection will be tested.
// 	TimeLimit TestConnectionTl;
// 	/// @brief	Number of successful tests.
// 	uint32_t TestConnectionCount;
    
// 	/// @brief	Time when connection was last active.
// 	TimeLimit LastConnectionActiveTl;
// };

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