
#include "BankConfiguration.h"
#include "Hardware.h"
#include "esp_partition.h"
#include "esp_ota_ops.h"
#include <cstring>

namespace Hal
{

BankConfiguration::BankConfiguration()
{
	esp_partition_iterator_t pInterator = esp_partition_find(ESP_PARTITION_TYPE_APP, ESP_PARTITION_SUBTYPE_ANY, nullptr);

	if (pInterator == nullptr)
		printf("Error, Interator failed to fetch the partition information.\n");
	else
	{
		const esp_partition_t *partition1 = esp_partition_get(pInterator);

		currentBank.Address = partition1->address;
		currentBank.BankRunning = ((uint8_t)partition1->subtype == 0) ? Bank::Bank1 : Bank::Bank2;
		memcpy(currentBank.Name.data(), partition1->label, strlen(partition1->label) + 1);
		currentBank.Size = partition1->size;

		if (currentBank.BankRunning == Bank::Bank1)
			pInterator = esp_partition_find(ESP_PARTITION_TYPE_APP, ESP_PARTITION_SUBTYPE_APP_OTA_0, nullptr);
		else
			pInterator = esp_partition_find(ESP_PARTITION_TYPE_APP, ESP_PARTITION_SUBTYPE_APP_FACTORY, nullptr);

		const esp_partition_t *partition2 = esp_partition_get(pInterator);

		otherBank.Address = partition2->address;
		otherBank.BankRunning = ((uint8_t)partition2->subtype == 0) ? Bank::Bank1 : Bank::Bank2;
		memcpy(otherBank.Name.data(), partition2->label, strlen(partition2->label) + 1);
		otherBank.Size = partition2->size;
	}

	// printf("Bank Running from: %d, label: %s\n", (uint8_t)currentBank.BankRunning, currentBank.Name.data());
	// printf("Other Bank: %d, label: %s\n", (uint8_t)otherBank.BankRunning, otherBank.Name.data());
}

const BankConfiguration::BankInfo BankConfiguration::GetCurrentBank()
{
	return currentBank;
}

const BankConfiguration::BankInfo BankConfiguration::GetOtherBank()
{
	return otherBank;
}

bool BankConfiguration::SetRunningBank(BankConfiguration::Bank nextBank)
{
	esp_partition_iterator_t pInterator;
	if (nextBank == Bank::Bank1)
		pInterator = esp_partition_find(ESP_PARTITION_TYPE_APP, ESP_PARTITION_SUBTYPE_APP_FACTORY, nullptr);
	else
		pInterator = esp_partition_find(ESP_PARTITION_TYPE_APP, ESP_PARTITION_SUBTYPE_APP_OTA_0, nullptr);

	if (pInterator == nullptr)
		printf("Error, Interator failed to fetch the partition information.");
	else
	{
		const esp_partition_t *partition = esp_partition_get(pInterator);
		printf("Partiton Type: %d, Sub Type: %d, Adress: %x, size:%x",
						(uint8_t)partition->type, (uint8_t)partition->subtype, partition->address, partition->size);
		printf("Partition Label: %s.", partition->label);
	}

	const esp_partition_t *partition = esp_partition_get(pInterator);

	if (esp_ota_set_boot_partition(partition) != ESP_OK)
		return false;

	return true;
}

BankConfiguration::~BankConfiguration()
{
}

} // namespace Hal
