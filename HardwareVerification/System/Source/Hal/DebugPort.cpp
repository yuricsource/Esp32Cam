/*
 * DebugPort.cpp
 *
 *  Created on: 26 Jun 2019
 *      Author: yuri
 */

#include "DebugPort.h"
#include "driver/uart.h"

namespace Hal
{
DebugPort::DebugPort(Gpio *gpio, UartPort uartPort, uint32_t baudRate, Gpio::GpioIndex txPin, Gpio::GpioIndex rxPin) : _gpio(gpio), _uartPort(uartPort), _baudRate(baudRate), _txPin(txPin), _rxPin(rxPin)
{
	uart_config_t uart_config = {
		.baud_rate = static_cast<int>(_baudRate),
		.data_bits = UART_DATA_8_BITS,
		.parity = UART_PARITY_DISABLE,
		.stop_bits = UART_STOP_BITS_1,
		.flow_ctrl = UART_HW_FLOWCTRL_DISABLE};
	uart_param_config(UART_NUM_0, &uart_config);
	_gpio->SetAlternate(_txPin, Gpio::AltFunc::Uart);
	_gpio->SetAlternate(_rxPin, Gpio::AltFunc::Uart);
}
DebugPort::~DebugPort()
{
}
} // namespace Hal
