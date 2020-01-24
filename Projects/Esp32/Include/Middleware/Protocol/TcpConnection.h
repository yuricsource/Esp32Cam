#pragma once

#include "BaseConnection.h"
#include "TimeLimit.h"
#include "lwip/tcp.h"
#include "DnsClient.h"
namespace Middleware 
{
namespace Protocol {

using Hal::TimeLimit;

class TcpConnection : public BaseConnection
{
public:
	TcpConnection() : 
		BaseConnection()
	{
	}
	
	~TcpConnection()
	{
		Close();
	}
private:

	BaseConnection::ConnectStatus DoConnect(const RemoteConnection &remoteConnection) override;

	bool DoSend(const unsigned char *data, uint16_t length) override;

	void DoClose() override;

	void DoReset() override;

	bool IsReady() override;
private:
	/// @brief	Hide Copy constructor.
	TcpConnection(const TcpConnection&) = delete;
	
	/// @brief	Hide Assignment operator.
	TcpConnection& operator=(const TcpConnection&) = delete;
	
	/// @brief	Hide Move constructor.
	TcpConnection(TcpConnection&&) = delete;
	
	/// @brief	Hide Move assignment operator.
	TcpConnection& operator=(TcpConnection&&) = delete;	
};

}
}