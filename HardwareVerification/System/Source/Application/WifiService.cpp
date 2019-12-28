#include "WifiService.h"
#include "Logger.h"

namespace Applications
{

using Hal::Hardware;
using Middleware::Logger;

void WifiService::Run()
{
    Hardware *_hardware = Hardware::Instance();
    int a = 0;
    //assert(a == 1);
    //static_assert(sizeof(a) == 4, "Error, 1 is different than 0");
    // esp_err_t ret = nvs_flash_init();
    // if (ret == ESP_ERR_NVS_NO_FREE_PAGES || ret == ESP_ERR_NVS_NEW_VERSION_FOUND)
    // {
    //     ESP_ERROR_CHECK(nvs_flash_erase());
    //     ret = nvs_flash_init();
    // }
    // ESP_ERROR_CHECK(ret);

    //  ESP_ERROR_CHECK(esp_wifi_set_mode(WIFI_MODE_STA));


    // ESP_ERROR_CHECK(esp_wifi_set_config(WIFI_IF_STA, &wifi_config));
    // ESP_ERROR_CHECK(esp_wifi_start());
    // ESP_ERROR_CHECK(esp_wifi_set_ps(WIFI_PS_NONE));
    // printf("Connecting to \"%s\"\n", wifi_config.sta.ssid);
    // xEventGroupWaitBits(s_wifi_event_group, CONNECTED_BIT, false, true, portMAX_DELAY);
    // printf("Connected\n");

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