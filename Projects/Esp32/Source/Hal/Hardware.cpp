
#include "stdio.h"
#include "wchar.h"
#include "Hardware.h"
#include "soc/rtc.h"
#include "Logger.h"
#include "RTOSExtra.h"
#include "CommonTypes.h"

namespace Hal
{

Hardware *Hardware::_pHardware;

Hardware::Hardware() : _gpio(),
					   _debugPort(&_gpio, UartPort::Uart0, 115200, Gpio::GpioIndex::Gpio3, Gpio::GpioIndex::Gpio1),
					   _spiffs(),
					   //_camera(&_gpio),
					   _sdCard(&_gpio),
					   _leds(&_gpio),
					   _rng(),
					   _wifiDriver()
{
	esp_chip_info(&_mcuInfo);
	esp_base_mac_addr_get(_macAdrress);
	printf("SDK Version         		: %s\n", (char *)esp_get_idf_version());
	printf("CPU Cores           		: %d\n", _mcuInfo.cores);
	// printf("CPU Clock           		: %d MHz\n", rtc_clk_cpu_freq_value(rtc_clk_cpu_freq_get()));
	printf("APB Clock           		: %d MHz\n", GetSystemClockBase());
	printf("CPU Revision        		: %d\n", _mcuInfo.revision);
	printf("Embedded Flash      		: %s\n", (_mcuInfo.features & CHIP_FEATURE_EMB_FLASH) ? "YES" : "NO");
	printf("Wi-Fi Modle         		: %s\n", (_mcuInfo.features & CHIP_FEATURE_WIFI_BGN) ? "YES" : "NO");
	printf("Bluetooth Classic   		: %s\n", (_mcuInfo.features & CHIP_FEATURE_BT) ? "YES" : "NO");
	printf("Bluetooth LE        		: %s\n", (_mcuInfo.features & CHIP_FEATURE_BLE) ? "YES" : "NO");
	printf("MAC Address         		: %02X:%02X:%02X:%02X\n",
		   _macAdrress[0],
		   _macAdrress[1],
		   _macAdrress[2],
		   _macAdrress[3]);
	// printf("RTC counter         		: %d\n", system_get_time());
	printf("MCU Free Heap       		: %d\n", esp_get_free_heap_size());
	printf("MCU Project Heap Allocated	: %d\n", configTOTAL_PROJECT_HEAP_SIZE_ALLOCATED);
	printf("Reset Reason        		: %s\n", GetResetReasonAsString(GetResetReason()));
	printf("\n");

	if (_pHardware == nullptr)
		_pHardware = this;
	else
		printf("!!! Error: Only one instance of System can be created !!!\n");

	_spiffs.Mount();
}

uint32_t Hardware::GetSystemClockBase()
{
	return rtc_clk_apb_freq_get();
}

void Hardware::SoftwareReset()
{
	esp_restart();
}

void Hardware::DeepSleep(uint32_t uSeconds)
{
	esp_sleep_enable_timer_wakeup(uSeconds);
	vTaskDelay(20);
	esp_deep_sleep_start();
}

ResetReason Hardware::GetResetReason()
{
	esp_reset_reason_t info = esp_reset_reason();
	return static_cast<ResetReason>(info);
}

char *Hardware::GetResetReasonAsString(ResetReason reason)
{
	switch (reason)
	{
	case ResetReason::Unknown:
		return (char *)"Unknown";
	case ResetReason::PowerOn:
		return (char *)"Power On";
	case ResetReason::ExternalReset:
		return (char *)"ExternalReset";
	case ResetReason::SoftwareReset:
		return (char *)"Software Reset";
	case ResetReason::ExceptionPanicReset:
		return (char *)"Exception/Panic Reset";
	case ResetReason::IntWatchDog:
		return (char *)"Internal External WatchDog";
	case ResetReason::TaskWatchDog:
		return (char *)"Task WatchDog";
	case ResetReason::WatchDog:
		return (char *)"Other WatchDog";
	case ResetReason::DeepSleep:
		return (char *)"Deep Sleep";
	case ResetReason::Brownout:
		return (char *)"Brownout";
	case ResetReason::Sdio:
		return (char *)"Sdio";
	default:
		return (char *)"";
	}
}

Hardware::~Hardware()
{
}

uint32_t Hardware::Milliseconds()
{
	return xTaskGetTickCount() * portTICK_PERIOD_MS;
}

} // namespace Hal
