/*
 * System.cpp
 *
 *  Created on: 19 May 2019
 *      Author: yuri
 */

#include "stdio.h"
#include "wchar.h"
#include "System.h"
#include "soc/rtc.h"

namespace Hal
{

// Singleton class
System *System::_pSystem;

System::System() : _gpio(),
				   _debugPort(&_gpio, UartPort::Uart0, 115200, Gpio::GpioIndex::Gpio1, Gpio::GpioIndex::Gpio3),
				   _leds(&_gpio), _deviceInput(&_gpio),
				   _deviceOutput(&_gpio), _interruptHandler(),
				   _timer(&_interruptHandler, TimerSelect::Timer0),
				   _pwm(&_interruptHandler, TimerSelect::Timer1, &_gpio),
				   _i2c(&_gpio, I2cPort::I2c0, Gpio::GpioIndex::Gpio26, Gpio::GpioIndex::Gpio27),
				   _uart(&_gpio, UartPort::Uart1, 115200, Gpio::GpioIndex::Gpio13, Gpio::GpioIndex::Gpio12),
				   _adc(&_gpio), _spiffs(),
				   _i2s(&_gpio, I2sBus::Bus_0, I2sBitSample::Sample16Bits, I2sChannelMode::ChannelStereo),
				   _sdCard(&_gpio),
				   _camera(&_gpio)
{
	esp_chip_info(&_mcuInfo);
	esp_base_mac_addr_get(_macAdrress);
	printf("SDK Version         : %s\n", (char *)system_get_sdk_version());
	printf("CPU Cores           : %d\n", _mcuInfo.cores);
	printf("CPU Clock           : %d MHz\n", rtc_clk_cpu_freq_value(rtc_clk_cpu_freq_get())); // @suppress("Invalid arguments")
	printf("APB Clock           : %d MHz\n", GetSystemClockBase());
	printf("CPU Revision        : %d\n", _mcuInfo.revision);
	printf("Embedded Flash      : %s\n", (_mcuInfo.features & CHIP_FEATURE_EMB_FLASH) ? "YES" : "NO");
	printf("Wi-Fi Modle         : %s\n", (_mcuInfo.features & CHIP_FEATURE_WIFI_BGN) ? "YES" : "NO");
	printf("Bluetooth Classic   : %s\n", (_mcuInfo.features & CHIP_FEATURE_BT) ? "YES" : "NO");
	printf("Bluetooth LE        : %s\n", (_mcuInfo.features & CHIP_FEATURE_BLE) ? "YES" : "NO");
	printf("MAC Address         : %02X:%02X:%02X:%02X\n",
		   _macAdrress[0],
		   _macAdrress[1],
		   _macAdrress[2],
		   _macAdrress[3]);
	printf("RTC counter         : %d\n", system_get_time());
	printf("MCU Free Heap       : %d\n", esp_get_free_heap_size());
	printf("Reset Reason        : %s\n", GetResetReasonAsString());
	printf("\n");

	if (_pSystem == nullptr)
		_pSystem = this;
	else
		printf("!!! Error: Only one instance of System can be created !!!\n");

	_i2s.Start();
	_spiffs.Mount();
	_timer.Initlialize();
	_timer.AddCallback(this);
}

uint32_t System::GetSystemClockBase()
{
	return rtc_clk_apb_freq_get(); // @suppress("Invalid arguments")
}

void System::SoftwareReset()
{
	system_restart();
}

uint32_t System::GetRandomNumber()
{
	return esp_random();
}

void System::DeepSleep(uint32_t uSeconds)
{
	esp_sleep_enable_timer_wakeup(uSeconds);
	vTaskDelay(20);
	esp_deep_sleep_start();
}

ResetReason System::GetResetReason()
{
	esp_reset_reason_t info = esp_reset_reason();
	return static_cast<ResetReason>(info);
}

char *System::GetResetReasonAsString()
{
	switch (GetResetReason())
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

System::~System()
{
}

void System::TimerCallback()
{
	_leds.Toggle(Hal::Leds::LedIndex::GreenLed);
}

uint32_t System::Milliseconds()
{
	return xTaskGetTickCount() * portTICK_PERIOD_MS;
}

} // namespace Hal
