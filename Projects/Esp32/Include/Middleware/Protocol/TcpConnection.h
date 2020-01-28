#pragma once

#include "BaseConnection.h"
#include "TimeLimit.h"
#include "lwip/tcp.h"
#include "DnsClient.h"
#include "Logger.h"

namespace Middleware 
{
namespace Protocol {

using Hal::TimeLimit;
using Hal::Hardware;
// using Middleware::BaseConnection::ConnectStatus;
using Utilities::Logger;

class TcpConnection : public BaseConnection
{
public:
	TcpConnection() : 
		BaseConnection(),
		_port(0), _pcb(nullptr)
	{
	}
	
	~TcpConnection()
	{
		Close();
	}

	uint16_t GetPort();

private:

	uint16_t _port;

	tcp_pcb *_pcb;

	static err_t receiveHandler(void *arg, struct tcp_pcb *pcb, struct pbuf *p, err_t err);
	static void clearPcbHandler(TcpConnection* conn, tcp_pcb *pcb);
	static err_t pollHandler(void *arg, struct tcp_pcb *pcb);
	static void errorHandler(void *arg, err_t err);
	static err_t sentHandler(void *arg, struct tcp_pcb *pcb, u16_t len);
	static err_t connectedHandler(void *arg, struct tcp_pcb *pcb, err_t err);

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