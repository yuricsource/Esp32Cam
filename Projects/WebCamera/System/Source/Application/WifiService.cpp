#include "WifiService.h"
#include "Logger.h"
#include "RTOSExtra.h"
#include "DebugAssert.h"

namespace Applications
{

using Hal::Hardware;
using Middleware::Utilities::Logger;
using Middleware::Configuration::BoardConfiguration;
using Middleware::Configuration::ConfigurationAgent;

void WifiService::ConfigurationUpdated()
{
    BoardConfiguration &configuration = *ConfigurationAgent::Instance()->GetBoardConfiguration();
    _authentication = configuration.GetConfiguration()->WifiConfig.AuthenticationMode;
    _wifiMode = configuration.GetConfiguration()->WifiConfig.WifiMode;
    _channel = configuration.GetConfiguration()->WifiConfig.Channel;
    _useDhcp = configuration.GetConfiguration()->WifiConfig.Settings.Flags.DhcpEnabled;
    ip_addr_copy(_ipAddress, configuration.GetConfiguration()->WifiConfig.IPAddress);
    ip_addr_copy(_maskAddress, configuration.GetConfiguration()->WifiConfig.Mask);
    ip_addr_copy(_gatewayAddress, configuration.GetConfiguration()->WifiConfig.GatewayAddress);
    ip_addr_copy(_dnsServer, configuration.GetConfiguration()->WifiConfig.DnsServer);
    changeState(WifiState::ResetAdapter);
}

void WifiService::changeState(WifiState wifiState)
{
    _wifiState = wifiState;
}


void WifiService::Run()
{
    tcpip_adapter_init();
    DebugAssert(esp_netif_init(), ESP_OK);



    Logger::LogInfo(Logger::LogSource::Wifi, "Running Wifi.");
    for (;;)
    {
        vTaskDelay(100);
        switch (_wifiState)
        {
        case WifiState::Idle:
        {
            _connected = false;
            vTaskDelay(1000);
        }
        break;
        case WifiState::ResetAdapter:
        {
           
            changeState(WifiState::WaitingTransmitter);
        }
        break;
        case WifiState::WaitingTransmitter:
        {
            changeState(WifiState::PrepareWifiConnection);
        }
        break;
        case WifiState::PrepareWifiConnection:
        {
            if (_wifiMode == WifiModeConfiguration::Client)
            {
                if (_useDhcp)
                    changeState(WifiState::DhcpRequest);
                else
                    changeState(WifiState::StaticIpRequest);
            }
            else
            {
                changeState(WifiState::StartHotspot);
            }
        }
        break;
        case WifiState::StaticIpRequest:
        {
            changeState(WifiState::StaticIpDone);
        }
        break;
        case WifiState::StaticIpDone:
        {

        }
        break;
        case WifiState::DhcpRequest:
        {
            changeState(WifiState::DhcpWaiting);
        }
        break;
        case WifiState::DhcpWaiting:
        {
            changeState(WifiState::DhcpDone);
        }
        break;
        case WifiState::DhcpDone:
        {
            
        }
        break;
        case WifiState::StartHotspot:
        {
            if (_useDhcp)
                    changeState(WifiState::StartDhcpServer);
                else
                    changeState(WifiState::StartDhcpServer);
        }
        break;
        case WifiState::SetStaticIp:
        {
            changeState(WifiState::StaticIpDone);
        }
        break;
        case WifiState::StartDhcpServer:
        {
            changeState(WifiState::DhcpDone);
        }
        break;

        default:
            break;
        }
    }
}

} // namespace Applications