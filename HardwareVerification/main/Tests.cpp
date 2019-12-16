/*
 * Tests.cpp
 *
 *  Created on: 24 May 2019
 *      Author: yuri
 */

#include "Tests.h"
#include <cstring>
using Hal::DeviceInput;
using Hal::Dwt;
using Hal::Leds;
using Hal::Hardware;
using Hal::TimeLimit;

const char *testPhrase = "RTC holds the memory with low power";

const char *GetTestPhrase()
{
	return testPhrase;
}

void TestSdCard()
{
	Hardware *system = Hal::Hardware::Instance();
	if (system->GetSdCard().Mount())
	{
		printf("Opening file\n");
		FILE *f = fopen("/sdcard/hello.txt", "w");
		if (f == NULL)
		{
			printf("Failed to open file for writing\n");
			return;
		}
		fprintf(f, "Hello Yuri, how are you!\n");
		fclose(f);
		printf("File written\n");

		// Check if destination file exists before renaming
		struct stat st;
		if (stat("/sdcard/foo.txt", &st) == 0)
		{
			// Delete it if it exists
			unlink("/sdcard/foo.txt");
		}

		// Rename original file
		printf("Renaming file\n");
		if (rename("/sdcard/hello.txt", "/sdcard/foo.txt") != 0)
		{
			printf("Rename failed\n");
			return;
		}

		// Open renamed file for reading
		printf("Reading file\n");
		f = fopen("/sdcard/foo.txt", "r");
		if (f == nullptr)
		{
			printf("Failed to open file for reading\n");
			return;
		}
		char line[64];
		fgets(line, sizeof(line), f);
		fclose(f);
		// strip newline
		char *pos = strchr(line, '\n');
		if (pos)
			*pos = '\0';
		printf("Read from file: '%s'", line);
	}
	else
		printf("Error: SdCard not mounted.\n");
}

void BlinkStatusLed()
{
	Hardware *system = Hal::Hardware::Instance();
#ifdef LED_AS_GPIO
	_system->GetGpio().SetMode(Hal::Gpio::GpioIndex::Gpio2, Hal::Gpio::Mode::Output);
#else
	Leds &led = system->GetLeds();
#endif

	for (int i = 0; i < 10; ++i)
	{
#ifdef LED_AS_GPIO
		_system->GetGpio().Toggle(Hal::Gpio::GpioIndex::Gpio2),
#else
		//led.Toggle(Hal::Leds::LedIndex::BlueLedStatus);
		uint32_t randomNumber = system->GetRandomNumber();
		if (randomNumber % 3 == 0)
			led.Toggle(Hal::Leds::LedIndex::BlueLed);
		else if (randomNumber % 3 == 1)
			led.Toggle(Hal::Leds::LedIndex::RedLed);
		else if (randomNumber % 3 == 2)
			led.Toggle(Hal::Leds::LedIndex::GreenLed);
#endif
			vTaskDelay(1000 / portTICK_PERIOD_MS);
	}
	led.ResetAll();
}

void ReadAdcValue()
{
	printf("\nAdc value: %d, Voltage: %d\n", Hardware::Instance()->GetAdc().GetAdcValue(Hal::Adc::AdcIndex::Adc1Channel6),
		   Hardware::Instance()->GetAdc().GetAdcVoltage(Hal::Adc::AdcIndex::Adc1Channel6));
}

void TestTimer0(bool start)
{
	if (start)
	{
		printf("\nStarting Timer 0 with 5Hz\n");
		Hardware::Instance()->GetTimer().SetTimer(5);
		Hardware::Instance()->GetTimer().Start();
	}
	else
	{
		printf("\nStoping Timer 0\n");
		Hardware::Instance()->GetTimer().Stop();
	}
}

void SoftwareResetTest()
{
	Hardware::Instance()->SoftwareReset();
}

void DwtTest()
{
	for (uint8_t i = 0; i < 5; i++)
	{
		printf("\n%d Sec Delay...\n", i + 1);
		Hardware::Instance()->GetLeds().Toggle(Hal::Leds::LedIndex::RedLed);
		Dwt::DelayMilliseconds(1000);
	}
}

void ReadButton()
{
	if (Hardware::Instance()->GetDeviceInput().GetInput(DeviceInput::InputIndex::UserButton))
		printf("\nButton Not Pressed\n");
	else
		printf("\nButton Pressed\n");
}

void TestDeviceOutput()
{
	for (uint8_t i = 0; i < 5; i++)
	{
		printf("\n%d Sec Delay...\n", i + 1);
		Hardware::Instance()->GetDeviceOutput().Toggle(Hal::DeviceOutput::OutputIndex::Output1);
		Dwt::DelayMilliseconds(1000);
	}
}
void StartWdt()
{
	printf("\nStarting Watch Dog Timer with 3 Seconds\n");
	Hardware::Instance()->GetWdt().Start(3, true);
}

void FeedWdt()
{
	printf("\nFeeding Watch Dog Timer with 3 Seconds\n");
	Hardware::Instance()->GetWdt().Feed();
}

void TestSpiffs()
{
	if (Hardware::Instance()->GetSpiffs().IsMounted() == false)
	{
		if (Hardware::Instance()->GetSpiffs().Mount() == false)
		{
			printf("\n\nSPIFFS failed!\n\n");
			return;
		}
	}

	printf("\n\nOpening file\n");
	FILE *f = fopen("/spiffs/hello.txt", "w");
	if (f == NULL)
	{
		printf("Failed to open file for writing");
		return;
	}
	fprintf(f, "SPIFFS is Working!!! Hooray!!! :D\n");
	fclose(f);
	printf("File written\n");

	// Check if destination file exists before renaming
	struct stat st;
	if (stat("/spiffs/foo.txt", &st) == 0)
	{
		// Delete it if it exists
		unlink("/spiffs/foo.txt");
	}

	// Rename original file
	printf("Renaming file\n");
	if (rename("/spiffs/hello.txt", "/spiffs/foo.txt") != 0)
	{
		printf("Rename failed\n");
		return;
	}

	printf("Reading Test file\n");
	f = fopen("/spiffs/lala.txt", "r");
	if (f == NULL)
	{
		printf("Failed to open file for reading\n");
		return;
	}

	char line[64];
	fgets(line, sizeof(line), f);
	fclose(f);

	// Open renamed file for reading
	printf("Reading Stored Test file\n");
	f = fopen("/spiffs/lala.txt", "r");
	if (f == NULL)
	{
		printf("Failed to open file for reading\n");
		return;
	}

	fgets(line, sizeof(line), f);
	fclose(f);
	// strip newline
	char *pos = strchr(line, '\n');
	if (pos)
	{
		*pos = '\0';
	}

	printf("Read from file: '%s'\n\n", line);
}
static char musicBuffer[1024 * 16];

void TestPlaySound()
{
	Hardware::Instance()->GetI2s().Start();
	Hardware::Instance()->GetI2s().UpdateChannelClock(Hal::I2sBitSample::Sample16Bits, Hal::I2sChannelMode::ChannelStereo, 22000);

	FILE *f = fopen("/spiffs/sample.wav", "r");

	if (f == NULL)
	{
		printf("Failed to open file for reading\n");
		return;
	}

	uint32_t length = 0;
	do
	{
		length = fread(musicBuffer, 1, sizeof(musicBuffer), f);
		Hardware::Instance()->GetI2s().Play((uint8_t *)musicBuffer, length);
	} while (length != 0);

	fclose(f);
	Hardware::Instance()->GetI2s().Stop();
}

void TestSerial()
{
	Hardware::Instance()->GetUart().Write("Hello Yuri's World\n", sizeof("Hello Yuri's World\n"));
}

void ExternalInterruptTest(bool enable)
{

	static ExternalInterruptTestClass *ExtIntTest;
	if (ExtIntTest == nullptr)
		ExtIntTest = new ExternalInterruptTestClass(Hal::Gpio::GpioIndex::Gpio4, Hal::ExternalInterrupt::InterruptType::EdgePositive);

	if (enable)
		ExtIntTest->Start();
	else
		ExtIntTest->Stop();
}

void TestPwm()
{
	Hardware *system = Hal::Hardware::Instance();
	Hal::Pwm &pwm = system->GetPwm();

	pwm.SetPin(Hal::Pwm::PwmIndex::PWM0, Hal::Gpio::GpioIndex::Gpio2);
	pwm.SetPwmFrequence(1000);
	pwm.Start(Hal::Pwm::PwmIndex::PWM0);
	pwm.StartPwm();

	TimeLimit time;
	Dwt::DelayMilliseconds(100);
	printf("\nTesting Software PWM...\n");
	for (uint8_t i = 0; i < 50;)
	{
		if (time.IsTimeUp(100))
		{
			time.Reset();
			pwm.SetDutyCycle(Hal::Pwm::PwmIndex::PWM0, 2 * i);
			i++;
		}
		vTaskDelay(10);
	}
	time.Reset();
	for (uint8_t i = 50; i > 1;)
	{
		if (time.IsTimeUp(100))
		{
			time.Reset();
			pwm.SetDutyCycle(Hal::Pwm::PwmIndex::PWM0, 2 * i);
			i--;
		}
		vTaskDelay(10);
	}

	pwm.Stop(Hal::Pwm::PwmIndex::PWM0);
	pwm.StopPwm();
}

void TestRtcMemory()
{
	uint8_t mem[512];

	bool rtcTested = true;
	for (int i = 0; i <= 511; ++i)
	{
		mem[i] = i;
	}

	Hardware::Instance()->GetRtc().Write(0, mem, 512);

	Hardware::Instance()->GetRtc().Read(0, mem, 512);

	for (int i = 0; i <= 511; ++i)
	{
		if (mem[i] != static_cast<uint8_t>(i))
			rtcTested = false;
	}

	if (rtcTested)
	{
		printf("\n\nMemory of RTC is working\n\n");
	}
	else
	{
		printf("\n\nMemory of RTC is NOT working or hasn't the default valued saved.\n\n");
	}
}

void PutCpuToSleep()
{
	printf("\n\nI'm going to bed and I will be back in 5 seconds. BYE :)\n\n");

	Hardware::Instance()->GetRtc().Write(0, (uint8_t *)testPhrase, (uint32_t)strlen((const char *)testPhrase));

	Hardware::Instance()->DeepSleep(5 * 1000 * 1000);
}

void TimeLimitTest()
{
	TimeLimit time;
	for (uint8_t i = 0; i < 5;)
	{
		if (time.IsTimeUp(1000))
		{
			printf("\n%d Sec Delay...\n", i + 1);
			time.Reset();
			i++;
		}
		//vTaskDelay(10);
		Hardware::Instance()->GetLeds().Toggle(Hal::Leds::LedIndex::BlueLed);
	}
}

void ScanI2c()
{
	for (int i = 1; i < 128; i++)
	{
		if (Hardware::Instance()->GetI2c().IsDeviceConnected(i))
			printf("\nFound device at address: 0x%x\n", i);
		else
			printf(".");
		Dwt::DelayMilliseconds(10);
	}
}
