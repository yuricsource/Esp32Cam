/*
 * Camera.h
 *
 *  Created on: 5 Dec 2019
 *      Author: yuri
 */

#ifndef MAIN_INCLUDE_HAL_CAMERA_CAMERA_H_
#define MAIN_INCLUDE_HAL_CAMERA_CAMERA_H_

#include "../../components/http_server/my_http_server.h"
// #include "bitmap.h"
#include "HalCommon.h"
#include "Gpio.h"
#include "esp_err.h"
#include "driver/ledc.h"
#include "Camera/Driver/esp_camera.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "freertos/semphr.h"
#include "freertos/event_groups.h"
#include "esp_event_legacy.h"

static void handle_grayscale_pgm(http_context_t http_ctx, void* ctx);
static void handle_rgb_bmp(http_context_t http_ctx, void* ctx);
static void handle_rgb_bmp_stream(http_context_t http_ctx, void* ctx);
static void handle_jpg(http_context_t http_ctx, void* ctx);
static void handle_jpg_stream(http_context_t http_ctx, void* ctx);
static esp_err_t event_handler(void *ctx, system_event_t *event);
static esp_err_t write_frame(http_context_t http_ctx);

namespace Hal
{

class Camera
{

public:

	Camera(Gpio *IoPins);
    
	void Init();
	
	void DeInit();
	
	const camera_fb_t * GetFrameBuffer();
	
	bool Capture();

	void SetResolution(CameraFrameSize frameSize);

	void SetImageFormat(CameraPixelFormat format);

	~Camera();
	
private:

camera_config_t _cameraConfig = {};
camera_fb_t *_frameBuffer = nullptr;

};
} // namespace Hal

#endif /* MAIN_INCLUDE_HAL_CAMERA_CAMERA_H_ */
