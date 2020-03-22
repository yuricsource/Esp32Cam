
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
using Configuration::ConfigurationAgent;
using Hal::Hardware;
using Utilities::Logger;

extern "C" void app_main(void)
{
	Hardware * hardware = Hardware::Instance();
	ConfigurationAgent::Instance();
	ApplicationAgent::Instance();

	ApplicationAgent::Instance()->Initialize();
	ApplicationAgent::Instance()->GetWifi().Start();
	ApplicationAgent::Instance()->GetHttpServer().Start();
	ApplicationAgent::Instance()->GetGatewayService().Start();
	ApplicationAgent::Instance()->GetFirmwareUpdateService().Start();

	// ConfigurationAgent::Instance()->UseDefaultConfiguration();

	// hardware->GetSdCard().Mount();

	// esp_partition_iterator_t pi = esp_partition_find(ESP_PARTITION_TYPE_APP, ESP_PARTITION_SUBTYPE_APP_OTA_0, nullptr);

	// if (pi != nullptr)
	// {
	// 	const esp_partition_t* factory = esp_partition_get(pi);
	// }

	// FILE *f = fopen("/sdcard/update.bin", "rb");
	// char* buffer [SPI_FLASH_SEC_SIZE];
	// while(true)
	// {
	// 	int len = fread(&buffer, 1, 512, f);
	// 	if (len == 0)
	// 		break;
	// }
	

// spi_flash_erase_sector(sector) == ESP_OK;
// spi_flash_write(offset, (uint32_t*) data, size) == ESP_OK;
	//esp_ota_get_next_update_partition()
	//esp_partition_find();

	// char test [1024];
	// ConfigurationAgent::Instance()->GetBoardConfiguration()->Serialize(test, 1024);
	// printf("\nTest: %s\n",test);
	// Logger::LogInfo("WebCamera using ESP32\n");

	// esp_https_ota();
	// esp_ota_set_boot_partition();

	for (;;)
	{
		vTaskDelay(1000);
	}
}
