
#ifndef TESTS_H_
#define TESTS_H_

#include "Hardware.h"
#include "audio_example_file.h"

void SoftwareResetTest();
void PutCpuToSleep();
void TestSpiffs();
void TestSdCard();

const char *GetTestPhrase();
#endif /* TESTS_H_ */
