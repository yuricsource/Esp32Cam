
#include <Flash.h>
#include "esp_flash_partitions.h"
#include "esp_image_format.h"
#include "esp_partition.h"
#include "Hardware.h"

namespace Hal
{

Flash::Flash()
{
}

Flash::~Flash()
{
}

bool Flash::Read(uint32_t offset, uint8_t *data, size_t size)
{
    if (data == nullptr || size == 0)
        return false;

	return spi_flash_read(offset, data, size) == ESP_OK;
}

bool Flash::Write(uint32_t offset, uint8_t *data, size_t size)
{
    if (data == nullptr || size == 0)
        return false;

	return spi_flash_write(offset, data, size) == ESP_OK;
}

bool Flash::EraseSector(uint32_t sector)
{
	return spi_flash_erase_sector(sector) == ESP_OK;
}

uint32_t Flash::GetRunningPartitionSize()
{    
	esp_image_metadata_t data;
    const esp_partition_t *running = esp_partition_find_first(ESP_PARTITION_TYPE_APP,
                                                     ESP_PARTITION_SUBTYPE_ANY,
                                                     NULL);

    if (running == nullptr)
		return 0;
    
	const esp_partition_pos_t running_pos  = 
	{
        .offset = running->address,
        .size = running->size,
    };
    
	data.start_addr = running_pos.offset;
    esp_image_verify(ESP_IMAGE_VERIFY, &running_pos, &data);

    return data.image_len;
}

} // namespace Hal
