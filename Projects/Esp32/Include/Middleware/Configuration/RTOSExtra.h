#pragma once

#include "freertos/FreeRTOS.h"

#define configWIFISVC_STACK_DEPTH (1024 * 2)
#define configHTTPSVC_STACK_DEPTH (1024 * 2)

#define configTOTAL_PROJECT_HEAP_SIZE_ALLOCATED ((size_t)configWIFISVC_STACK_DEPTH + \
                                                 configHTTPSVC_STACK_DEPTH)
