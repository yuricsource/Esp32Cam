
#ifndef HAL_WIFIDRIVER_H_
#define HAL_WIFIDRIVER_H_

#include "Gpio.h"
#include "HalCommon.h"
#include <array>
#include "esp_wifi.h"

namespace Hal
{
using std::array;

class WifiDriver
{
public:
	WifiDriver();
	~WifiDriver();
	void ResetDriver();
	bool Enable();
	bool Disable();
	inline bool IsEnabled(){return _isEnabled;};
	bool SetSsid(const char* ssid, uint8_t len);
	bool SetPassword(const char* passwd, uint8_t len);
	bool Configure(WifiConfiguration wifiConfiguration);
	bool SetStaticIp(ip_addr_t ip);
	bool SetStaticIp(const char* ip, uint8_t len);
	bool UseDhcp();
private:
	bool _isEnabled = false;
	bool _isConnected = false;
	WifiAuthenticationMode _authentication = WifiAuthenticationMode::Open;
	WifiConfiguration _wifiConfiguration = WifiConfiguration::Client;
	uint8_t _channel;

	array<char,WifiSsidMaxLength> _ssid = {};
	array<char,WifiPasswordMaxLength> _password = {};
};

} // namespace Hal

// wifi_config_t wifi_config = {
// .ap = {
// 	.ssid = EXAMPLE_ESP_WIFI_SSID,
// 	.ssid_len = strlen(EXAMPLE_ESP_WIFI_SSID),
// 	.password = EXAMPLE_ESP_WIFI_PASS,
// 	.max_connection = EXAMPLE_MAX_STA_CONN,
// 	.authmode = WIFI_AUTH_WPA_WPA2_PSK
// },
//                  |          (A) USER CODE                 |
//                  |                                        |
//     .............| init          settings      events     |
//     .            +----------------------------------------+
//     .               .                |           *
//     .               .                |           *
// --------+        +===========================+   *     +-----------------------+
//         |        | new/config     get/set    |   *     |                       |
//         |        |                           |...*.....| init                  |
//         |        |---------------------------|   *     |                       |
//   init  |        |                           |****     |                       |
//   start |********|  event handler            |*********|  DHCP                 |
//   stop  |        |                           |         |                       |
//         |        |---------------------------|         |                       |
//         |        |                           |         |    NETIF              |
//   +-----|        |                           |         +-----------------+     |
//   | glue|----<---|  esp_netif_transmit       |--<------| netif_output    |     |
//   |     |        |                           |         |                 |     |
//   |     |---->---|  esp_netif_receive        |-->------| netif_input     |     |
//   |     |        |                           |         + ----------------+     |
//   |     |....<...|  esp_netif_free_rx_buffer |...<.....| packet buffer         |
//   +-----|        |                           |         |                       |
//         |        |                           |         |         (D)           |
//   (B)   |        |          (C)              |         +-----------------------+
// --------+        +===========================+
// communication                                                NETWORK STACK
// DRIVER                   ESP-NETIF
//
// ........ Initialization line from user code to ESP-NETIF and communication driver
// --<--->-- Data packets going from communication media to TCP/IP stack and back
// ******** Events aggregated in ESP-NETIF propagates to driver, user code and network stack
// | User settings and runtime configuration


#endif /* HAL_WIFIDRIVER_H_ */
