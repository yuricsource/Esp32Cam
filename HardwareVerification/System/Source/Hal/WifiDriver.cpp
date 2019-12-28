
#include "WifiDriver.h"
#include "string.h"
#include "lwip/sockets.h"
#include "esp_err.h"
#include "nvs_flash.h"
#include "nvs.h"
#include "esp_wifi.h"

namespace Hal
{

WifiDriver::WifiDriver()
{
	tcpip_adapter_init();
	esp_err_t ret = nvs_flash_init();
	if (ret == ESP_ERR_NVS_NO_FREE_PAGES || ret == ESP_ERR_NVS_NEW_VERSION_FOUND)
	{
		assert(nvs_flash_erase() == ESP_OK);
		ret = nvs_flash_init();
	}
	assert(ret == ESP_OK);
	wifi_init_config_t cfg = WIFI_INIT_CONFIG_DEFAULT();
	assert(esp_wifi_init(&cfg) == ESP_OK);
}
WifiDriver::~WifiDriver()
{
}

bool WifiDriver::SetSsid(const char *ssid, uint8_t len)
{
	if (_ssid.size() < len)
		return false;

	memset(_ssid.data(), 0, _ssid.size());
	memcpy(_ssid.data(), ssid, len);

	return true;
}

bool WifiDriver::SetPassword(const char *passwd, uint8_t len)
{
	if (_password.size() < len)
		return false;
	memset(_password.data(), 0, _password.size());
	memcpy(_password.data(), passwd, len);

	return true;
}

bool WifiDriver::Configure(WifiConfiguration wifiConfiguration)
{
	if (_isEnabled)
		return false;

	_wifiConfiguration = wifiConfiguration;

	return true;
}

bool WifiDriver::UseDhcp()
{
	return false;
}

void WifiDriver::ResetDriver()
{
	Disable();
	Enable();
}

bool WifiDriver::Enable()
{
	if (_isEnabled)
		return true;

	wifi_config_t wifi_config = {};
    strcpy((char *)wifi_config.sta.ssid, _ssid.data());
    strcpy((char *)wifi_config.sta.password, _password.data());

	if (_wifiConfiguration == WifiConfiguration::Client)
    	esp_wifi_set_mode(WIFI_MODE_AP);
    else if (_wifiConfiguration == WifiConfiguration::HotSpot)
		esp_wifi_set_mode(WIFI_MODE_STA);
	else if (_wifiConfiguration == WifiConfiguration::Mesh)
		esp_wifi_set_mode(WIFI_MODE_APSTA);
		
	ESP_ERROR_CHECK(esp_wifi_set_config(WIFI_IF_STA, &wifi_config));
    ESP_ERROR_CHECK(esp_wifi_start());
    ESP_ERROR_CHECK(esp_wifi_set_ps(WIFI_PS_NONE));
	// if (esp_wifi_init(&cfg) == ESP_OK)
	// 	_isEnabled = true;
	// else
	// 	_isEnabled = false;

	return _isEnabled;
}

bool WifiDriver::Disable()
{
	if (_isEnabled == false)
		return true;

	if (esp_wifi_deinit() == ESP_OK)
		_isEnabled = false;
	else
		_isEnabled = true;

	return _isEnabled == false;
}
} // namespace Hal
