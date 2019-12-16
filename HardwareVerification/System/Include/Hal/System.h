/*
 * System.h
 *
 *  Created on: 19 May 2019
 *      Author: Yuri A. Rodrigues
 */

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
#include "Leds.h"
#include "I2c.h"
#include "Timer.h"
#include "Dwt.h"
#include "TimeLimit.h"
#include "DeviceInput.h"
#include "DeviceOutput.h"
#include "Adc.h"
#include "Pwm.h"
#include "DebugPort.h"
#include "Uart.h"
#include "Rtc.h"
#include "ExternalInterrupt.h"
#include "Wdt.h"
#include "I2s.h"
#include "SdCard.h"
#include "Camera/Camera.h"

namespace Hal
{

class System : Timer::Callback
{
public:
	System();
	~System();
	Gpio &GetGpio() { return _gpio; };
	Adc &GetAdc() { return _adc; };
	Leds &GetLeds() { return _leds; };
	Timer &GetTimer() { return _timer; };
	I2c &GetI2c() { return _i2c; };
	Pwm &GetPwm() { return _pwm; };
	DebugPort &GetDebugPort() { return _debugPort; };
	DeviceInput &GetDeviceInput() { return _deviceInput; };
	DeviceOutput &GetDeviceOutput() { return _deviceOutput; };
	Uart &GetUart() { return _uart; };
	Rtc &GetRtc() { return _rtc; };
	Wdt &GetWdt() { return _wdt; };
	Spiffs &GetSpiffs() { return _spiffs; };
	I2s &GetI2s() { return _i2s; };
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

	static inline System *Instance()
	{
		if (_pSystem == nullptr)
		{
			_pSystem = new System();
		}
		return _pSystem;
	}

private:
	static System *_pSystem;
	Gpio _gpio;
	DebugPort _debugPort;
	Leds _leds;
	DeviceInput _deviceInput;
	DeviceOutput _deviceOutput;
	TimerInterruptHandler _interruptHandler;
	Timer _timer;
	Pwm _pwm;
	I2c _i2c;
	Uart _uart;
	Adc _adc;
	Rtc _rtc;
	Wdt _wdt;
	Spiffs _spiffs;
	I2s _i2s;
	esp_chip_info_t _mcuInfo;
	MacAddress _macAdrress;
	SdCard _sdCard;
	Camera _camera;
};
} // namespace Hal

#endif /* HAL_SYSTEM_H_ */
