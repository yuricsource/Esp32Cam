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

	/// @brief	Get reference to the underlying connection
	const BaseConnection &GetConnection()
	{
		return *_connection;
	}

	ConnectionExecutionResult GetResult()
	{
		return _executionResult;
	}

	/// @brief	Check if path is terminated
	bool IsTerminated() const
	{
		return DoIsTerminated();
	}

	/// @brief	Start path processing. Returns False if unable to start.
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
	/// @brief	Set Path Connection
	virtual void DoSetConnection() = 0;

	///	@brief	True if the path handling is terminated.
	virtual bool DoIsTerminated() const = 0;

	/// @brief	Start path processing. Returns False if unable to start.
	virtual bool DoStart(ConnectionMode connectionMode, RemoteConnection *address, uint8_t processingIndex, uint8_t processingLogicalId) = 0;

	/// @brief	Termination request
	virtual void DoTerminate() = 0;

	/// @brief	Main processing call
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