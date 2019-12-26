#include "HttpServer.h"
#include "Logger.h"

namespace Middleware
{

HttpServer::HttpServer(uint32_t port) : _port(port)
{
}

HttpServer::~HttpServer()
{
}
void HttpServer::StartServer()
{
	int sock, rc;

	/* create a TCP socket */
	if ((sock = lwip_socket(AF_INET, SOCK_STREAM, 0)) < 0)
	{
		Logger::LogError(Middleware::Logger::LogSource::HttpServer, "Failed to create socket");
		return;
	}
	memset(&_localHost, 0, sizeof(_localHost));
	_localHost.sin_len = sizeof(_localHost);
	_localHost.sin_family = AF_INET;
	_localHost.sin_port = PP_HTONS(_port);
	_localHost.sin_addr.s_addr = INADDR_ANY;

	if (bind(sock, (struct sockaddr *)&_localHost, sizeof(_localHost)) < 0)
	{
		close(sock);
		return; //ERROR_SOCKET_CREATE;
	}
	/* listen for incoming connections (TCP listen backlog = 5) */
	listen(sock, 5);
	uint16_t size = sizeof(_localHost);
	for (;;)
	{
		vTaskDelay(100);

		int Testsock = accept(sock, (struct sockaddr *)&_localHost, (socklen_t *)&size);
		// rc = stream_oper->write_stream(stream_oper);
		// if (rc < 0)
		// {
		// 	MRD_ERR_LOG(MODULE_ETH, "Failed to write");
		// }
		int ret = 0, offset = 0;
		do
		{
			ret = read(Testsock, _rxBuffer.data() + offset, _rxBufferSize);
			offset += ret;
			fwrite(_rxBuffer.data(), 1, ret, stdout);
		} while (ret > 0);
	}
	close(sock);
}

} // namespace Middleware