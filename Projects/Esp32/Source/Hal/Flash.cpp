
#include <Flash.h>
#include "esp_spi_flash.h"
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

bool Flash::Read(uint32_t offset, uint32_t *data, size_t size)
{
	return spi_flash_read(offset, (uint32_t*) data, size) == ESP_OK;
}

bool Flash::Write(uint32_t offset, uint32_t *data, size_t size)
{
	return spi_flash_write(offset, (uint32_t*) data, size) == ESP_OK;
}

bool Flash::EraseSector(uint32_t sector)
{
	return spi_flash_erase_sector(sector) == ESP_OK;
}

bool Flash::GetMdr5(char* md5return, size_t size)
{
    // uint32_t lengthLeft = getSketchSize();

    // const esp_partition_t *running = esp_ota_get_running_partition();
    // if (!running) {
    //     printf("Partition could not be found");

    //     return false;
    // }
    // const size_t bufSize = SPI_FLASH_SEC_SIZE;
    // std::unique_ptr<uint8_t[]> buf(new uint8_t[bufSize]);
    // uint32_t offset = 0;
    // if(!buf.get()) {
    //     printf("Not enough memory to allocate buffer");

    //     return false;
    // }

    // MD5Builder md5Calculation;
    // md5Calculation.begin();
    // while( lengthLeft > 0) 
	// {
    //     size_t readBytes = (lengthLeft < bufSize) ? lengthLeft : bufSize;
    //     if (Read(running->address + offset, reinterpret_cast<uint32_t*>(buf.get()), (readBytes + 3) & ~3) == false) 
	// 	{
    //         printf("Could not read buffer from flash");

    //         return false;
    //     }
    //     md5Calculation.add(buf.get(), readBytes);
    //     lengthLeft -= readBytes;
    //     offset += readBytes;
    // }
    // md5Calculation.calculate();
	// md5Calculation.output(md5return);
    return true;
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
