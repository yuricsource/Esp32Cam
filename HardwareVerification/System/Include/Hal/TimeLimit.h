/*
 * TimeLimit.h
 *
 *  Created on: 1 Jun 2019
 *      Author: yuri
 */

#ifndef HAL_TIMELIMIT_H
#define HAL_TIMELIMIT_H

#include <cstdint>
#include "HalCommon.h"

namespace Hal
{

class TimeLimit
{
private:
	uint32_t startTicks;

public:
	TimeLimit();
	void Reset();
	bool IsTimeUp(uint32_t time) const;
	uint32_t ElapsedTime() const;
};

} // namespace Hal

#endif /* __SPG_HAL_TIMELIMIT_H */
