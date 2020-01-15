
#ifndef HAL_SYSTEM_H_
#define HAL_SYSTEM_H_

#include "HalCommon.h"
#include <stdlib.h>
#include <stdio.h>
#include <Spiffs.h>
#include <cstdint>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "TimerInterruptHandler.h"
#include "Gpio.h"
#include "Dwt.h"
#include "DebugPort.h"
#include "Leds.h"
#include "TimeLimit.h"
#include "SdCard.h"
#include "Camera.h"
#include "Rng.h"
#include "WifiDriver.h"
#include "FastDelegate.h"

namespace Hal
{

class Hardware
{
public:
	Hardware();
	~Hardware();
	Gpio &GetGpio() { return _gpio; };
	Leds &GetLeds() { return _leds; };
	Spiffs &GetSpiffs() { return _spiffs; };
	SdCard &GetSdCard() { return _sdCard; };
	//Camera &GetCamera() { return _camera; };
	DebugPort &GetDebugPort() { return _debugPort; };
	Rng &GetRng() { return _rng; };
	WifiDriver &GetWifi() { return _wifiDriver; };

	uint32_t Milliseconds();
	void TimerCallback();
	ResetReason GetResetReason();
	void SoftwareReset();
	uint32_t GetRandomNumber();
	uint32_t GetSystemClockBase();
	void DeepSleep(uint32_t uSeconds);

	static inline Hardware *Instance()
	{
		if (_pHardware == nullptr)
		{
			_pHardware = new Hardware();
		}
		return _pHardware;
	}

private:
	static Hardware *_pHardware;
	Gpio _gpio;
	DebugPort _debugPort;
	Spiffs _spiffs;
	esp_chip_info_t _mcuInfo;
	MacAddress _macAdrress;
	//Camera _camera;
	SdCard _sdCard;
	Leds _leds;
	Rng _rng;
	WifiDriver _wifiDriver;
};
} // namespace Hal

#endif /* HAL_SYSTEM_H_ */
