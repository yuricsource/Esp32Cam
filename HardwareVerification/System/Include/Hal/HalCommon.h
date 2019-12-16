/*
 * HalCommon.h
 *
 *  Created on: 21 May 2019
 *      Author: yuri
 */

#ifndef INCLUDE_HAL_HALCOMMON_H_
#define INCLUDE_HAL_HALCOMMON_H_

#include "esp_system.h"
#include <stdio.h>
#include "esp_err.h"

namespace Hal
{
enum class I2sBus : uint8_t
{
	Bus_0,
	Bus_1,
};

enum class I2sChannelFormat : uint8_t
{
	ChannelFormatRightAndLeft,
	ChannelFormatAllRight,
	ChannelFormatAllLeft,
	ChannelFormatOnlyRight,
	ChannelFormatOnlyLeft,
};

enum class I2sDacMode : uint8_t
{
	DacDisable,
	DacRightChannelEnable,
	DacLeftChannelEnable,
	DacBothChannelsEnable,
};

enum class I2sCommunicationStandardFormat : uint8_t
{
	CommunicationFormatI2s = 0x01,		   /*!< I2S communication format I2S*/
	CommunicationFormatI2sMSB = 0x02,	  /*!< I2S format MSB*/
	CommunicationFormatI2sLSB = 0x04,	  /*!< I2S format LSB*/
	CommunicationFormatI2s_PCM = 0x08,	 /*!< I2S communication format PCM*/
	CommunicationFormatI2sPCMShort = 0x10, /*!< PCM Short*/
	CommunicationFormatI2sPCMLong = 0x20,  /*!< PCM Long*/
};

enum class I2sBitSample : uint8_t
{
	Sample8Bits = 8,
	Sample16Bits = 16,
	Sample24Bits = 24,
	Sample32Bits = 32
};

enum class I2sChannelMode : uint8_t
{
	ChannelMono = 1,
	ChannelStereo = 2
};

enum class I2cBus : uint8_t
{
	Bus_0,
	Bus_1,
};

enum class I2cSpeed : uint8_t
{
	Speed_80K = 0,
	Speed_100K,
	Speed_400K,
	Speed_500K,
	Speed_600K,
	Speed_800K,
	Speed_1000K,
	Speed_1300K
};

enum class ResetReason : uint8_t
{
	Unknown = 0,
	PowerOn = 1,
	ExternalReset = 2,
	SoftwareReset = 3,
	ExceptionPanicReset = 4,
	IntWatchDog = 5,
	TaskWatchDog = 6,
	WatchDog = 7,
	DeepSleep = 8,
	Brownout = 9,
	Sdio = 10
};

/* Interrupt numbers for level 1 exception handler. */
enum class Preemption
{
	WdevFiq = 0,
	Slc = 1,
	Spi = 2,
	Rtc = 3,
	Gpio = 4,
	Uart = 5,
	Tick = 6,
	Soft = 7,
	WatchDogTime = 8,
	TIMER0 = 9,
	TIMER1 = 10
};

enum class TimerSelect : uint8_t
{
	Timer0 = 0,
	Timer1 = 1
};

enum class UartPort : uint8_t
{
	Uart0 = 0,
	Uart1 = 1
};

enum class DataBit : uint8_t
{
	Data5Btis = 0,
	Data6Btis = 1,
	Data7Btis = 2,
	Data8Btis = 3
};

enum class Parity : uint8_t
{
	None = 0,
	Even = 1,
	Odd = 2
};

enum class StopBit : uint8_t
{
	StopBit1 = 1,
	StopBit1_5 = 2,
	StopBit2 = 3
};

enum class HardwareFlowControl : uint8_t
{
	Disable = 0,
	ControlRts = 1,
	ControlCts = 2,
	ControlCtsRts = 3,
};

enum class I2cMode : uint8_t
{
	Slave = 0,
	Master = 1
};

enum class I2cPort : uint8_t
{
	I2c0 = 0,
	I2c1 = 1
};

enum class CameraPixelFormat : uint8_t
{
	CameraPixelFormatRGB565 = 0,	//!< RGB, 2 bytes per pixel (not implemented)
	CameraPixelFormatYUV422 = 1,	//!< YUYV, 2 bytes per pixel (not implemented)
	CameraPixelFormatGrayScale = 2, //!< 1 byte per pixel
	CameraPixelFormatJPEG = 3,		//!< JPEG compressed
};

enum class CameraFrameSize : uint8_t
{
	CameraFrameSizeQQVGA = 4, //!< 160x120
	CameraFrameSizeQVGA = 8,  //!< 320x240
	CameraFrameSizeVGA = 10,  //!< 640x480
	CameraFrameSizeSVGA = 11, //!< 800x600
	CameraFrameSizeSXGA = 12, //	1280* 1024
	CameraFrameSizeUXGA = 13, //1600*1200
};

enum class CameraModel : uint16_t
{
	CameraNone = 0,
	CameraUnknown = 1,
	CameraOV7725 = 7725,
	CameraOV2640 = 2640,
};

enum class CameraErrorCode : uint8_t
{
	CameraNotDetected,
	CameraFailedToSetFrameSize,
	CameraNotSupported
};

using MacAddress = uint8_t[6];

static constexpr uint32_t TimeBaseClock = 80000000;

} // namespace Hal
#endif /* INCLUDE_HAL_HALCOMMON_H_ */
