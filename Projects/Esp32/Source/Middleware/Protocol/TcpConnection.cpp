#include "lwip/tcpip.h"
#include <cstring>
#include "Hardware.h"
#include "TcpConnection.h"
#include "Logger.h"
#include "IPParser.h"

namespace Middleware 
{
namespace Protocol 
{

	BaseConnection::ConnectStatus TcpConnection::DoConnect(const RemoteConnection &remoteConnection)
	{
		return ConnectStatus::Failed;
	}

	bool TcpConnection::DoSend(const unsigned char *data, uint16_t length)
    {
        return true;
    }

	void TcpConnection::DoClose()
    {
        return;
    }

	void TcpConnection::DoReset()
    {
        return;
    }

	bool TcpConnection::IsReady()
    {
        return false;
    }

}
}