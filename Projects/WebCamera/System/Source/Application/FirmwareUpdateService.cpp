#include "FirmwareUpdateService.h"
#include "ConfigurationAgent.h"

namespace Applications
{

FirmwareUpdateService::FirmwareUpdateService() : cpp_freertos::Thread("GWSVC", configGATEWAYSVC_STACK_DEPTH, 3)
{
}

FirmwareUpdateService::~FirmwareUpdateService()
{
}

void FirmwareUpdateService::Run()
{
	while (true)
	{
		vTaskDelay(1000);
	}
}

} // namespace Applications
