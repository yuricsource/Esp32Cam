
#ifndef INCLUDE_HAL_FLASH_H_
#define INCLUDE_HAL_FLASH_H_

#include "HalCommon.h"
#include "Gpio.h"
#include "driver/gpio.h"

namespace Hal
{

class Flash
{
public:
	typedef enum
	{
		None = 0,
		EdgePositive = 1,
		EdgeNegative = 2,
		EdgePositiveOrNegative = 3,
		LevelLow = 4,
		LevelHigh = 5
	} InterruptType;

	~Flash();
	Flash();

	bool Read(uint32_t offset, uint32_t *data, size_t size);
	bool Write(uint32_t offset, uint32_t *data, size_t size);
	bool EraseSector(uint32_t sector);
	bool GetMdr5(char* md5, size_t size);
	uint32_t GetRunningPartitionSize();

private:

};

} // namespace Hal

#endif /* INCLUDE_HAL_FLASH_H_ */
