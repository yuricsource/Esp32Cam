#pragma once

#include <cassert>
#include <array>
namespace Middleware
{
namespace Common
{
using std::array;

using IpAddress = array<char, 64>;
static_assert(sizeof(IpAddress) == 64, "Array has invalid size.");

} // namespace Common
} // namespace Middleware