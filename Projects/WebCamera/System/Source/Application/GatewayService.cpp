#include "GatewayService.h"
#include "ConfigurationAgent.h"

namespace Applications
{

using Middleware::Configuration::ConfigurationAgent;
// using Applications::GatewayService;

GatewayService::GatewayService() : cpp_freertos::Thread("GWSVC", configGATEWAYSVC_STACK_DEPTH, 3),
    _connectionPath(), _connectionState(ConnectionState::None)
{
    _connectionPath.Protocol = ProtocolType::Websocket;
    _connectionPath.TransportLayer = TransportLayerType::Wifi;
    _connectionPath.Connection = new TcpConnection();
}

void GatewayService::Run()
{
    vTaskDelay(600);

    RemoteConnection *connection = &ConfigurationAgent::Instance()->GetBoardConfiguration()->GetConfiguration()->ServerConfig.connection;

    for (;;)
    {
        switch (_connectionState)
        {
        case ConnectionState::None:
            changeState(ConnectionState::RestartConnection);
            break;

        case ConnectionState::RestartConnection:
            // _connectionPath.Connection->Reset();
            changeState(ConnectionState::TryToConnect);
            break;

        case ConnectionState::TryToConnect:
            _connectionPath.Connection->Connect(*connection);
            changeState(ConnectionState::EstablishConnection);
            break;

        case ConnectionState::EstablishConnection:
            changeState(ConnectionState::Connected);
            break;

        case ConnectionState::Connected:
            break;

        default:
            break;
        }
        vTaskDelay(10);
    }
}

} // namespace Applications
