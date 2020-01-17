#pragma once

#include <cassert>
#include <array>
namespace Middleware
{
namespace Common
{
using std::array;

static constexpr uint8_t IpLength = 64;
using IpAddress = array<char, IpLength>;
static_assert(sizeof(IpAddress) == 64, "Array has invalid size.");

using IpAddress = array<char, IpLength>;
static_assert(sizeof(IpAddress) == 64, "Array has invalid size.");

using IpAddress = array<char, IpLength>;
static_assert(sizeof(IpAddress) == 64, "Array has invalid size.");

} // namespace Common
} // namespace Middleware