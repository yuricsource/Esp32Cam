/*
 * SdCard.cpp
 *
 *  Created on: 24 Nov 2019
 *      Author: yuri
 */

#include "SdCard.h"
#include <stdio.h>
#include <string.h>
#include <sys/unistd.h>
#include <sys/stat.h>
#include "esp_err.h"
#include "esp_log.h"
#include "esp_vfs_fat.h"
#include "driver/sdmmc_host.h"
#include "driver/sdspi_host.h"
#include "sdmmc_cmd.h"

// This example can use SDMMC and SPI peripherals to communicate with SD card.
// By default, SDMMC peripheral is used.
// To enable SPI mode, uncomment the following line:

// #define USE_SPI_MODE

// When testing SD and SPI modes, keep in mind that once the card has been
// initialized in SPI mode, it can not be reinitialized in SD mode without
// toggling power to the card.

#ifdef USE_SPI_MODE
// Pin mapping when using SPI mode.
// With this mapping, SD card can be used both in SPI and 1-line SD mode.
// Note that a pull-up on CS line is required in SD mode.
#define PIN_NUM_MISO 2
#define PIN_NUM_MOSI 15
#define PIN_NUM_CLK 14
#define PIN_NUM_CS 13
#endif //USE_SPI_MODE

namespace Hal
{

SdCard::SdCard(Gpio *gpio) : _gpio(gpio)
{
	_gpio->SetMode(Gpio::GpioIndex::Gpio15, Gpio::Mode::Input);
	_gpio->SetPull(Gpio::GpioIndex::Gpio15, Gpio::Pull::Up);
	_gpio->SetMode(Gpio::GpioIndex::Gpio2, Gpio::Mode::Input);
	_gpio->SetPull(Gpio::GpioIndex::Gpio2, Gpio::Pull::Up);
	_gpio->SetMode(Gpio::GpioIndex::Gpio4, Gpio::Mode::Input);
	_gpio->SetPull(Gpio::GpioIndex::Gpio4, Gpio::Pull::Up);
	_gpio->SetMode(Gpio::GpioIndex::Gpio12, Gpio::Mode::Input);
	_gpio->SetPull(Gpio::GpioIndex::Gpio12, Gpio::Pull::Up);
	_gpio->SetMode(Gpio::GpioIndex::Gpio13, Gpio::Mode::Input);
	_gpio->SetPull(Gpio::GpioIndex::Gpio13, Gpio::Pull::Up);
}

bool SdCard::Mount()
{
	if (isMounted)
		return true;
	sdmmc_host_t host = SDMMC_HOST_DEFAULT();

	sdmmc_slot_config_t slot_config = SDMMC_SLOT_CONFIG_DEFAULT();

	esp_vfs_fat_sdmmc_mount_config_t mount_config = {
		.format_if_mount_failed = false,
		.max_files = 5,
		.allocation_unit_size = 16 * 1024};

	sdmmc_card_t *card;
	esp_err_t ret = esp_vfs_fat_sdmmc_mount("/sdcard", &host, &slot_config, &mount_config, &card);

	if (ret != ESP_OK)
	{
		if (ret == ESP_FAIL)
		{
			printf("Failed to mount filesystem. "
				   "If you want the card to be formatted, set format_if_mount_failed = true.");
		}
		else
		{
			printf("Failed to initialize the card (%s). "
				   "Make sure SD card lines have pull-up resistors in place.",
				   esp_err_to_name(ret));
		}
		return false;
	}

	isMounted = true;
	return true;
}

void SdCard::Unmount()
{
	esp_vfs_fat_sdmmc_unmount();
	isMounted = false;
}

bool SdCard::IsMounted()
{
	return isMounted;
}

SdCard::~SdCard()
{
}
} // namespace Hal
