#pragma once

#include "CircularBuffer.h"
#include "CommonMessageType.h"
#include "ConfigurationCommon.h"
#include "TimeLimit.h"

namespace Middleware
{
namespace Protocol
{

using Hal::TimeLimit;
using Middleware::Utilities::CircularBuffer;

class RouteDataTransferHandler
{
public:
	RouteDataTransferHandler(uint16_t &txPayloadLength);

	~RouteDataTransferHandler();

private:
	/// @brief	Hide Copy constructor.
	RouteDataTransferHandler(const RouteDataTransferHandler &) = delete;

	/// @brief	Hide Assignment operator.
	RouteDataTransferHandler &operator=(const RouteDataTransferHandler &) = delete;

	/// @brief	Hide Move constructor.
	RouteDataTransferHandler(RouteDataTransferHandler &&) = delete;

	/// @brief	Hide Move assignment operator.
	RouteDataTransferHandler &operator=(RouteDataTransferHandler &&) = delete;
};

} // namespace Protocol
} // namespace Middleware