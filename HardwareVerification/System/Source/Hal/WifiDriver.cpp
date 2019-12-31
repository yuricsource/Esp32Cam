
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

bool WifiDriver::SetMode(WifiConfiguration wifiConfiguration)
{
	if (_isEnabled)
		return false;

	_wifiConfiguration = wifiConfiguration;

	return true;
}

bool WifiDriver::SetAuthentication(WifiAuthenticationMode authentication)
{
	if (_isEnabled)
		return false;

	_authentication = authentication;

	return true;
}

void WifiDriver::ResetDriver()
{
	Disable();
	Enable();
}

bool WifiDriver::SetChannel(uint8_t channel)
{
		if (_isEnabled)
		return false;

	_channel = channel;

	return true;
}

bool WifiDriver::Enable()
{
	if (_isEnabled)
		return true;

	wifi_config_t wifi_config = {};

	wifi_mode_t wifiMode = static_cast<wifi_mode_t>(_wifiConfiguration);
	
	esp_interface_t interface;
	if (_wifiConfiguration == WifiConfiguration::HotSpot)
	{
		interface = esp_interface_t::ESP_IF_WIFI_AP;
		wifi_config.ap.authmode = static_cast<wifi_auth_mode_t>(_authentication);
		strcpy((char *)wifi_config.ap.ssid, _ssid.data());
		wifi_config.ap.ssid_len = strlen( _ssid.data());
		wifi_config.ap.max_connection = 4;
		wifi_config.ap.authmode = static_cast<wifi_auth_mode_t>(_authentication);
		strcpy((char *)wifi_config.ap.password, _password.data());
		wifi_config.ap.channel = _channel;
	}
	else if (_wifiConfiguration == WifiConfiguration::Client)
	{
		interface = esp_interface_t::ESP_IF_WIFI_STA;
		strcpy((char *)wifi_config.sta.ssid, _ssid.data());
		strcpy((char *)wifi_config.sta.password, _password.data());
		wifi_config.sta.channel = _channel;
	}
	else
	{
		assert(0);
	}
	esp_wifi_set_mode(wifiMode);
	assert(esp_wifi_set_config(interface, &wifi_config) == ESP_OK);
	assert(esp_wifi_start() == ESP_OK);
	assert(esp_wifi_set_ps(WIFI_PS_NONE) == ESP_OK);

	_isEnabled = true;

	return _isEnabled;
}

bool WifiDriver::Disable()
{
	if (_isEnabled == false)
		return true;

	esp_wifi_stop();
	assert(esp_wifi_stop() == ESP_OK);

	_isEnabled = false;

	return true;
}
} // namespace Hal
