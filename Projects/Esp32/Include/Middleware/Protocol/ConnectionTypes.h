#pragma once

#include <cstdint>
#include "FastDelegate.h"
#include "lwip/ip_addr.h"
#include "ConfigurationCommon.h"

namespace Protocol
{

using namespace fastdelegate;
using Common::IpAddress;

enum class ConnectionState
{
	ConnectionNotConfigured = 0,
	Connecting = 1,
	Connected = 2,
	Disconnected = 3
};

enum class ConnectionChangeReason
{
	None = 0,
	Error = 1,
	Timeout = 2,
	Closed = 3
};

using DelegateDataReceived = FastDelegate2<const char *, uint16_t>;
using DelegateConnectionStateChanged = FastDelegate2<ConnectionState, ConnectionChangeReason>;

enum class NonStoppingConnectionStage : uint8_t
{
	Stopped = 0,
	Starting = 1,
	CheckingProgress = 2,
};

struct RemoteConnection
{
	uint16_t Port;
	IpAddress Address;
};

} // namespace Protocol