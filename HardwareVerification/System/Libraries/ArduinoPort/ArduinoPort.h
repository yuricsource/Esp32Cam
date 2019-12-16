/*
 * ArduinoPort.h
 *
 *  Created on: 27 Sep 2019
 *      Author: yuri
 */

#ifndef MAIN_LIBRARIES_ARDUINOPORT_H_
#define MAIN_LIBRARIES_ARDUINOPORT_H_

#include "HalCommon.h"
#include "System.h"
#include "I2c.h"

#define PROGMEM

template <typename T>
uint8_t pgm_read_byte (T address)
{
	return *address;
}

#define Wire					Hal::System::Instance()->GetI2c()
#define beginTransmission		BeginTransmission
#define send					Send
#define endTransmission			EndTransmission
#define requestFrom				RequestFrom
#define receive					Receive
#define millis					Hal::System::Instance()->Milliseconds


#endif /* MAIN_LIBRARIES_ARDUINOPORT_H_ */
