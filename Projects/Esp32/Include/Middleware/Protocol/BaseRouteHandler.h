#pragma once

#include "TimeLimit.h"
#include "BaseConnection.h"

namespace Middleware
{
namespace Protocol
{

using Hal::TimeLimit;

class BaseRouteHandler
{
public:
	enum class ConnectionMode
	{
		ConnectionNotConfigured = 0,
		TestConnection,
		DataConnection
	};

	enum class ConnectionExecutionResult
	{
		Success,
		Working,
		Error
	};

public:
	BaseRouteHandler();

	~BaseRouteHandler()
	{
	}

	const BaseConnection &GetConnection()
	{
		return *_connection;
	}

	ConnectionExecutionResult GetResult()
	{
		return _executionResult;
	}

	bool IsTerminated() const
	{
		return DoIsTerminated();
	}

	bool Start(ConnectionMode connectionMode, RemoteConnection *address, uint8_t processingIndex, uint8_t processingLogicalId)
	{
		return DoStart(connectionMode, address, processingIndex, processingLogicalId);
	}

	void Terminate()
	{
		DoTerminate();
	}

	void Process()
	{
		DoProcess();
	}

protected:
	BaseConnection *_connection = nullptr;
	ConnectionExecutionResult _executionResult;
	RemoteConnection _remoteConnection;

	virtual void ReceivedData(const uint8_t *data, uint16_t length) = 0;

	virtual void ConnectionStateChanged(ConnectionState state, ConnectionChangeReason reason) = 0;

	virtual bool SendFrame(const uint8_t *data, uint16_t length) = 0;

	const RemoteConnection &GetRemoteConnection()
	{
		return _remoteConnection;
	}


private:
	virtual void DoSetConnection() = 0;

	virtual bool DoIsTerminated() const = 0;

	virtual bool DoStart(ConnectionMode connectionMode, RemoteConnection *address, uint8_t processingIndex, uint8_t processingLogicalId) = 0;

	virtual void DoTerminate() = 0;

	virtual void DoProcess() = 0;

private:
	/// @brief	Hide Copy constructor.
	BaseRouteHandler(const BaseRouteHandler &) = delete;

	/// @brief	Hide Assignment operator.
	BaseRouteHandler &operator=(const BaseRouteHandler &) = delete;

	/// @brief	Hide Move constructor.
	BaseRouteHandler(BaseRouteHandler &&) = delete;

	/// @brief	Hide Move assignment operator.
	BaseRouteHandler &operator=(BaseRouteHandler &&) = delete;
};

} // namespace Protocol
} // namespace Middleware