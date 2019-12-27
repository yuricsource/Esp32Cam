#pragma once
#include "Hardware.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "thread.hpp"

namespace Applications
{

class WifiService : public cpp_freertos::Thread
{
public:
    WifiService() :
		cpp_freertos::Thread("WIFISVC", /*configWIFISVC_STACK_DEPTH*/ 1024, 3)
    {

    }

    inline bool IsConnected()
    {
        return false;
    }

protected:
    void Run() override;

private:
    /// @brief	Hide Copy constructor.
    WifiService(const WifiService &) = delete;

    /// @brief	Hide Assignment operator.
    WifiService &operator=(const WifiService &) = delete;

    /// @brief	Hide Move constructor.
    WifiService(WifiService &&) = delete;

    /// @brief	Hide Move assignment operator.
    WifiService &operator=(WifiService &&) = delete;
};

} // namespace Applications