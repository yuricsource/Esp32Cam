
#ifndef TESTS_H_
#define TESTS_H_

#include "Hardware.h"

void SoftwareResetTest();
void PutCpuToSleep();
void TestSpiffs();
void TestSdCard();
void ToggleFlashLed();

const char *GetTestPhrase();
#endif /* TESTS_H_ */
