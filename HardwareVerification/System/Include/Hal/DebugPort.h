/*
 * DebugPort.h
 *
 *  Created on: 26 Jun 2019
 *      Author: yuri
 */

#ifndef HAL_DEBUGPORT_H_
#define HAL_DEBUGPORT_H_

#include "Gpio.h"

namespace Hal
{

class DebugPort
{
public:
	// Gpio Pins for Debug port
	static constexpr Gpio::GpioIndex DebugTx = Gpio::GpioIndex::Gpio1;
	static constexpr Gpio::GpioIndex DebugRx = Gpio::GpioIndex::Gpio3;

	DebugPort(Gpio *gpio, UartPort uartPort, uint32_t baudRate, Gpio::GpioIndex txPin, Gpio::GpioIndex rxPin);

	~DebugPort();

private:
	Gpio *_gpio;
	UartPort _uartPort;
	uint32_t _baudRate;
	DataBit _dataBit = DataBit::Data8Btis;
	Parity _parity = Parity::None;
	StopBit _stopBit = StopBit::StopBit1;
	HardwareFlowControl _flowControl = HardwareFlowControl::Disable;
	Gpio::GpioIndex _txPin;
	Gpio::GpioIndex _rxPin;
};

} // namespace Hal

#endif /* HAL_DEBUGPORT_H_ */
