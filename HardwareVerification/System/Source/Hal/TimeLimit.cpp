/*
 * TimeLimit.cpp
 *
 *  Created on: 1 Jun 2019
 *      Author: yuri
 */

#include "TimeLimit.h"
#include "System.h"

namespace Hal
{

TimeLimit::TimeLimit()
	: startTicks(System::Instance()->Milliseconds())
{
}

void TimeLimit::Reset()
{
	startTicks = System::Instance()->Milliseconds();
}

bool TimeLimit::IsTimeUp(uint32_t time) const
{
	return (System::Instance()->Milliseconds() - startTicks) >= time;
}

uint32_t TimeLimit::ElapsedTime() const
{
	return (System::Instance()->Milliseconds() - startTicks);
}

} // namespace Hal
