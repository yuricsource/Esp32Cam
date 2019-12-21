
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
#include "Leds.h"
#include "TimeLimit.h"
#include "SdCard.h"
#include "Camera/Camera.h"

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
	Camera &GetCamera() { return _camera; };
	uint32_t Milliseconds();
	void TimerCallback();
	ResetReason GetResetReason();
	char *GetResetReasonAsString();
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
	Spiffs _spiffs;
	esp_chip_info_t _mcuInfo;
	MacAddress _macAdrress;
	Camera _camera;
	SdCard _sdCard;
	Leds _leds;
};
} // namespace Hal

#endif /* HAL_SYSTEM_H_ */
