
#include <iostream>
#include <thread>
#include <chrono>
#include <memory>
#include <string>
#include <sstream>
#include <cstring>
#include <esp_attr.h>
#include <freertos/FreeRTOS.h>
#include <freertos/task.h>
#include <esp_log.h>
#include "Hardware.h"
#include "Logger.h"
#include "Rng.h"
#include "CircularBuffer.h"
#include "DebugAssert.h"
#include "ApplicationAgent.h"
#include "ConfigurationAgent.h"

using Applications::ApplicationAgent;
using Middleware::Configuration::ConfigurationAgent;
using Middleware::Utilities::Logger;
using Hal::Hardware;

extern "C" void app_main(void)
{
	Hardware::Instance();
	ConfigurationAgent::Instance();
	ConfigurationAgent::Instance()->UseDefaultConfiguration();
	ApplicationAgent::Instance();
	ApplicationAgent::Instance()->Initialize();
	ApplicationAgent::Instance()->GetWifi().Start();
	ApplicationAgent::Instance()->GetHttpServer().Start();
 	
	Logger::LogInfo("WebCamera using ESP32\n");


	for(;;)
	{
		vTaskDelay(1000);
	}
}
