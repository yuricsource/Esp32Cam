
#ifndef TESTS_H_
#define TESTS_H_

#include "Hardware.h"
#include "audio_example_file.h"

void BlinkStatusLed();
void ReadAdcValue();
void TestTimer0(bool start);
void ScanI2c();
void DwtTest();
void TimeLimitTest();
void SoftwareResetTest();
void ReadButton();
void ExternalInterruptTest(bool enable);
void TestPwm();
void TestSerial();
void PutCpuToSleep();
void TestRtcMemory();
void TestDeviceOutput();
void StartWdt();
void FeedWdt();
void TestSpiffs();
void TestPlaySound();
void TestSdCard();

class ExternalInterruptTestClass : Hal::ExternalInterrupt
{
public:
	ExternalInterruptTestClass(Hal::Gpio::GpioIndex gpio, Hal::ExternalInterrupt::InterruptType interruptType) : Hal::ExternalInterrupt(gpio, interruptType)
	{
	}

	static void InterruptCallback2(void *arg)
	{
		//printf("External interrupt activated, Gpio: \n");
		Hal::Hardware::Instance()->GetLeds().Toggle(Hal::Leds::LedIndex::GreenLed);
	}

	void Start()
	{
		this->ConfigureInterrupt((gpio_isr_t)InterruptCallback2);
		this->Enable();
	}
	void Stop()
	{
		this->Disable();
	}
};

const char *GetTestPhrase();
#endif /* TESTS_H_ */
