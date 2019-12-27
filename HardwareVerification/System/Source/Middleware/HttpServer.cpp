#include "HttpServer.h"
#include "Logger.h"
#include "lwip/sockets.h"
#include "tcpip_adapter.h"

#include "lwip/err.h"
#include "lwip/sockets.h"
#include "lwip/sys.h"
#include "Hardware.h"

namespace Middleware
{

HttpServer::HttpServer(uint32_t port) : _port(port)
{
	Logger::LogError(Middleware::Logger::LogSource::HttpServer, "Creating Http Server");
    //nvs_flash_init();
    tcpip_adapter_init();
    //esp_event_loop_create_default();

    /* This helper function configures Wi-Fi or Ethernet, as selected in menuconfig.
     * Read "Establishing Wi-Fi or Ethernet Connection" section in
     * examples/protocols/README.md for more information about this function.
     */
    //example_connect();
}

HttpServer::~HttpServer()
{
}
void HttpServer::StartServer()
{

	for (;;)
	{
		int sock, rc;

		char addr_str[128];
		Logger::LogError(Logger::LogSource::HttpServer, "Creating Socket");
		int addr_family;
		int ip_protocol;
		struct sockaddr_in dest_addr;

		dest_addr.sin_addr.s_addr = htonl(INADDR_ANY);
		dest_addr.sin_family = AF_INET;
		dest_addr.sin_port = htons(_port);
		addr_family = AF_INET;
		ip_protocol = IPPROTO_IP;

		inet_ntoa_r(dest_addr.sin_addr, addr_str, sizeof(addr_str) - 1);

		int listen_sock = socket(addr_family, SOCK_STREAM, ip_protocol);
		if (listen_sock < 0)
		{
			Logger::LogError(Logger::LogSource::HttpServer, "Failed to create socket");
			return;
		}

		int err = bind(listen_sock, (struct sockaddr *)&dest_addr, sizeof(dest_addr));
		if (err != 0)
		{
			Logger::LogError(Logger::LogSource::HttpServer, "Socket unable to bind: errno %d", errno);
			break;
		}
		Logger::LogInfo(Logger::LogSource::HttpServer, "Socket bound, port %d", _port);

		err = listen(listen_sock, 1);
		if (err != 0)
		{
			Logger::LogError(Logger::LogSource::HttpServer, "Error occurred during listen: errno %d", errno);
			return;
		}
		Logger::LogInfo(Logger::LogSource::HttpServer, "Socket listening");

		struct sockaddr_in6 source_addr; // Large enough for both IPv4 or IPv6
		uint addr_len = sizeof(source_addr);
		sock = accept(listen_sock, (struct sockaddr *)&source_addr, &addr_len);
		if (sock < 0)
		{
			Logger::LogError(Logger::LogSource::HttpServer, "Unable to accept connection: errno %d", errno);
			return;
		}
		Logger::LogInfo(Logger::LogSource::HttpServer, "Socket accepted");

		do{
		int len = recv(sock, _rxBuffer.data(), _rxBufferSize, 0);
		// Error occurred during receiving
		if (len < 0)
		{
			Logger::LogError(Logger::LogSource::HttpServer, "recv failed: errno %d", errno);
			break;
		}
		// Connection closed
		else if (len == 0)
		{
			Logger::LogError(Logger::LogSource::HttpServer, "Connection closed");
			break;
		}
		fwrite(_rxBuffer.data(), 1, len, stdout);
		}while(true);
		close(sock);
	}
}

} // namespace Middleware