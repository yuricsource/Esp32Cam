/*
 * SdCard.h
 *
 *  Created on: 24 Nov 2019
 *      Author: yuri
 */

#ifndef MAIN_INCLUDE_HAL_SDCARD_H_
#define MAIN_INCLUDE_HAL_SDCARD_H_

#include <cstdint>
#include "HalCommon.h"
#include "Gpio.h"

namespace Hal
{

class SdCard
{
public:
	SdCard(Gpio *gpio);
	~SdCard();
	bool Mount();
	bool IsMounted();
	void Unmount();

private:
	Gpio *_gpio;
	bool isMounted = false;
};
} // namespace Hal

#endif /* MAIN_INCLUDE_HAL_SDCARD_H_ */
