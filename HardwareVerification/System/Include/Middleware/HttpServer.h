#pragma once

#include <cstdint>
#include <array>
#include "lwip/sockets.h"


namespace Middleware
{

using std::array;

class HttpServer
{
public:
	HttpServer(uint32_t port);
	~HttpServer();
	void StartServer();
private:
	uint16_t _httpResponse = 0;
	uint16_t _packetsCount = 0;
	static constexpr uint16_t _rxBufferSize = 1024;
	array<uint8_t, _rxBufferSize> _rxBuffer;

	static constexpr uint16_t _txBufferSize = 1024;
	array<uint8_t, _txBufferSize> _txBuffer;

	int _connectionTimeout;
	uint32_t _port = 0;

	sockaddr_in _localHost;
};
} // namespace Middleware