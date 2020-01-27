#include "GatewayService.h"

namespace Applications
{

GatewayService::GatewayService() : cpp_freertos::Thread("GWSVC", configGATEWAYSVC_STACK_DEPTH, 3), _connectionPath()
{
    _connectionPath.Protocol = ProtocolType::Websocket;
    _connectionPath.TransportLayer = TransportLayerType::Wifi;
    _connectionPath.Connection = new TcpConnection();
}

void GatewayService::Run()
{
    vTaskDelay(600);
    RemoteConnection connection;
    memcpy(connection.Address.data(), "192.168.0.102", sizeof("192.168.0.102"));
    Logger::LogInfo(Logger::LogSource::FirstGateway,"Connection to google");
    _connectionPath.Connection->Connect(connection);
    
    for (;;)
    {
        vTaskDelay(10);
    }
}

} // namespace Applications
