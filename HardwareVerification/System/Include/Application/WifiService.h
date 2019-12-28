#pragma once
#include "Hardware.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "thread.hpp"
#include "Hardware.h"
#include "esp_err.h"
#include "nvs_flash.h"
#include "nvs.h"
#include "esp_wifi.h"

namespace Applications
{

class WifiService : public cpp_freertos::Thread
{
public:
    WifiService() : cpp_freertos::Thread("WIFISVC", /*configWIFISVC_STACK_DEPTH*/ 1024 * 2, 3)
    {
    }

    inline bool IsConnected()
    {
        return _connected;
    }

protected:
    void Run() override;

private:
    enum class WiFiState : uint8_t
    {
        Idle,
        ResetAdapter,
        WaitingTransmitter,
        StaticIpRequest,
        StaticIpDone,
        DhcpStart,
        DhcpRequest,
        DhcpWaiting,
        DhcpDone
    };

    WiFiState _wiFiState = WiFiState::Idle;
    bool _connected = false;
    wifi_init_config_t cfg = WIFI_INIT_CONFIG_DEFAULT();
private:
    /// @brief	Hide Copy constructor.
    WifiService(const WifiService &) = delete;

    /// @brief	Hide Assignment operator.
    WifiService &operator=(const WifiService &) = delete;

    /// @brief	Hide Move constructor.
    WifiService(WifiService &&) = delete;

    /// @brief	Hide Move assignment operator.
    WifiService &operator=(WifiService &&) = delete;
};

} // namespace Applications