#include "WifiService.h"
#include "Logger.h"

namespace Applications
{

using Hal::Hardware;
using Middleware::Logger;

void WifiService::Run()
{
    Hardware *_hardware = Hardware::Instance();
    for(;;)
    {
        vTaskDelay(100);
        Logger::LogInfo(Logger::LogSource::Wifi,"Wifi running...");
    }
}

} // namespace Applications