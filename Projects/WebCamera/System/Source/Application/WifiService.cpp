#include "WifiService.h"
#include "Logger.h"

namespace Applications
{

using Hal::Hardware;
using Middleware::Logger;

void WifiService::Run()
{
    Hardware *_hardware = Hardware::Instance();
    
    tcpip_adapter_init();
    assert(esp_netif_init() == ESP_OK);

    Logger::LogInfo(Logger::LogSource::Wifi, "Running Wifi.");
    for (;;)
    {
        vTaskDelay(10);
        switch (_wiFiState)
        {
        case WiFiState::Idle:
        {
            _connected = false;
        }
        break;
        case WiFiState::ResetAdapter:
        {
           // esp_wifi_init();
        }
        break;
        case WiFiState::WaitingTransmitter:
        {
        }
        break;
        case WiFiState::StaticIpRequest:
        {
        }
        break;
        case WiFiState::StaticIpDone:
        {
        }
        break;
        case WiFiState::DhcpRequest:
        {
            wifi_config_t wifi_config = {};
            strcpy((char *)wifi_config.sta.ssid, "Yuri_Duda");
            strcpy((char *)wifi_config.sta.password, "Australia2us");
        }
        break;
        case WiFiState::DhcpWaiting:
        {
        }
        break;
        case WiFiState::DhcpDone:
        {
        }
        break;
        default:

            break;
        }
    }
}

} // namespace Applications