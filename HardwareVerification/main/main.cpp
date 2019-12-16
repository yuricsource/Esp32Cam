/* pthread/std::thread example

   This example code is in the Public Domain (or CC0 licensed, at your option.)

   Unless required by applicable law or agreed to in writing, this
   software is distributed on an "AS IS" BASIS, WITHOUT WARRANTIES OR
   CONDITIONS OF ANY KIND, either express or implied.
*/

#include <iostream>
#include <thread>
#include <chrono>
#include <memory>
#include <string>
#include <sstream>
#include <esp_attr.h>
#include <freertos/FreeRTOS.h>
#include <freertos/task.h>
#include <chrono>
#include <memory>
#include <string>
#include <sstream>
#include <freertos/FreeRTOS.h>
#include <freertos/task.h>
#include <esp_log.h>
#include "Hardware.h"
#include "Tests.h"
#include <cstring>

void executetMenu(char Test)
{
	switch (Test)
	{
	case 'l':
	case 'L':
		BlinkStatusLed();
		break;
	case 't':
	case 'T':
		TestTimer0(true);
		break;
	case 'g':
	case 'G':
		TestTimer0(false);
		break;
	case 'a':
	case 'A':
		ReadAdcValue();
		break;
	case 'i':
	case 'I':
		ScanI2c();
		break;
	case 'd':
	case 'D':
		DwtTest();
		break;
	case 'e':
	case 'E':
		TimeLimitTest();
		break;
	case 'r':
	case 'R':
		SoftwareResetTest();
		break;
	case 'b':
	case 'B':
		ReadButton();
		break;
	case 'o':
	case 'O':
		ExternalInterruptTest(true);
		break;
	case 'p':
	case 'P':
		ExternalInterruptTest(false);
		break;
	case 's':
	case 'S':
		TestPwm();
		break;
	case 'x':
	case 'X':
		TestSerial();
		break;
	case 'f':
	case 'F':
		PutCpuToSleep();
		break;
	case 'n':
	case 'N':
		TestRtcMemory();
		break;
	case 'j':
	case 'J':
		//TestExternalRtc();
		break;
	case 'm':
	case 'M':
		TestDeviceOutput();
		break;
	case 'h':
	case 'H':
		StartWdt();
		break;
	case 'q':
	case 'Q':
		FeedWdt();
		break;
	case 'c':
	case 'C':
		TestSpiffs();
		break;
		break;
	case 'k':
	case 'K':
		TestPlaySound();
		break;
		break;
	case 'z':
	case 'Z':
		TestSdCard();
		break;
	default:
		break;
	}

	printf("\n");
	printf("Main menu:\n");
	printf("----------\n");
	printf("[L] - Test Leds\n");
	printf("[T] - Enable Timer 1\n");
	printf("[G] - Disable Timer 1\n");
	printf("[A] - Print ADC Value\n");
	printf("[I] - Scan I2c Devices\n");
	printf("[D] - Dwt timer test\n");
	printf("[E] - Time Limit test\n");
	printf("[R] - Software Reset Test\n");
	printf("[B] - Print User Button State\n");
	printf("[O] - Enable External Interruption by User pin\n");
	printf("[P] - Disable External Interruption by User pin\n");
	printf("[S] - Start PWM\n");
	printf("[X] - Print \"Hello Yuri's World!\" in Uart1\n");
	printf("[F] - Deep Sleep for 5 Seconds.\n");
	printf("[N] - Test RTC memory\n");
	printf("[M] - Test Device Output\n");
	printf("[J] - Test External RTC\n");
	printf("[H] - Initialise Watch Dog Timer [Not finished]\n");
	printf("[Q] - Test External RTC\n");
	printf("[C] - Test SPIFFS\n");
	printf("[K] - Test Sound [speaker(R)<->GPIO25 and speaker(L)<->GPIO26]\n");
	printf("[Z] - Test SdCard\n");
}
extern "C" void app_main(void)
{
	Hal::Hardware::Instance();
	printf("\n");
	printf("Hardware Verification for ESP8266\n");
	printf("\n");
	Hal::Hardware::Instance()->GetAdc().InitAdc(Hal::Adc::AdcIndex::Adc1Channel6);
	char test = 0;

	if (Hal::Hardware::Instance()->GetResetReason() == Hal::ResetReason::DeepSleep)
	{
		int len = strlen(GetTestPhrase());
		uint8_t test[len];

		Hal::Hardware::Instance()->GetRtc().Read(0, test, len);
		//const char * phrase =
		if (strncmp((const char *)test, GetTestPhrase(), len) == 0)
		{
			printf("\nTest Passed\n%s\n\n", test);
		}
		else
			printf("\nTest Failed\n");
	}

	while (1)
	{
		executetMenu(test);
		test = 0;
		while (test == 0)
		{
			scanf("%c", &test);
			vTaskDelay(10);
		}
	}
}
