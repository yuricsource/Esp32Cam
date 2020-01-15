#pragma once

#include <cstdint>
#include <cstring>
#include <array>
#include <bitset>
#include "HalCommon.h"

namespace Common
{
using Hal::ResetReason;

enum class ConnectionType
{
    None = 0,
    Wifi = 1,
    Lora = 2,
    Ethernet = 3
};

char *GetResetReasonAsString(ResetReason reason)
{
    switch (reason)
    {
    case ResetReason::Unknown:
        return (char *)"Unknown";
    case ResetReason::PowerOn:
        return (char *)"Power On";
    case ResetReason::ExternalReset:
        return (char *)"ExternalReset";
    case ResetReason::SoftwareReset:
        return (char *)"Software Reset";
    case ResetReason::ExceptionPanicReset:
        return (char *)"Exception/Panic Reset";
    case ResetReason::IntWatchDog:
        return (char *)"Internal External WatchDog";
    case ResetReason::TaskWatchDog:
        return (char *)"Task WatchDog";
    case ResetReason::WatchDog:
        return (char *)"Other WatchDog";
    case ResetReason::DeepSleep:
        return (char *)"Deep Sleep";
    case ResetReason::Brownout:
        return (char *)"Brownout";
    case ResetReason::Sdio:
        return (char *)"Sdio";
    default:
        return (char *)"";
    }
}

} // namespace Common