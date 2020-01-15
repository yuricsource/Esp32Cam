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

} // namespace Common