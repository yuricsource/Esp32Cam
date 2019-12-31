
#ifndef TESTS_H_
#define TESTS_H_

#include "Hardware.h"

void SoftwareResetTest();
void PutCpuToSleep();
void TestSpiffs();
void TestSdCard();
void ToggleFlashLed();
void WifiMenu();
char ReadKey();
void ReadString(char * string, uint8_t size);

const char *GetTestPhrase();
#endif /* TESTS_H_ */
