
#ifndef TESTS_H_
#define TESTS_H_

#include <cstring>
#include <string>
#include "stdio.h"
#include <cstdint>
#include <cstdarg>
#include "stdio.h"
#include "wchar.h"
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
