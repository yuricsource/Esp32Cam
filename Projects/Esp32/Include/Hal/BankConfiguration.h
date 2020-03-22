
#ifndef INCLUDE_HAL_BANK_CONFIGURATION_H_
#define INCLUDE_HAL_BANK_CONFIGURATION_H_

#include "HalCommon.h"
namespace Hal
{

class BankConfiguration
{
public:
	BankConfiguration();
	~BankConfiguration();

	enum class Bank : uint8_t
	{
		Bank1,
		Bank2,
		Unknown = 255
	};

	struct BankInfo
	{
		LabelName Name;
		Bank BankRunning;
		uint32_t Address;
		size_t Size; 
	};
	
	const BankConfiguration::BankInfo GetCurrentBank();
	const BankConfiguration::BankInfo GetOtherBank();

	bool SetRunningBank(BankConfiguration::Bank nextBank);

private:
	BankInfo currentBank;
	BankInfo otherBank;

};
} // namespace Hal

#endif /* INCLUDE_HAL_BANK_CONFIGURATION_H_ */
