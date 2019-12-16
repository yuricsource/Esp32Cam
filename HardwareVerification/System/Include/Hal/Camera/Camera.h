/*
 * Camera.h
 *
 *  Created on: 5 Dec 2019
 *      Author: yuri
 */

#ifndef MAIN_INCLUDE_HAL_CAMERA_CAMERA_H_
#define MAIN_INCLUDE_HAL_CAMERA_CAMERA_H_

#include "../../components/http_server/my_http_server.h"
#include "../../components/camera/include/bitmap.h"
#include "HalCommon.h"
#include "Gpio.h"
#include "esp_err.h"
#include "driver/ledc.h"
#include "Camera/camera.h"
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
	struct CameraConfiguration
	{
		int PinReset; /*!< GPIO pin for camera reset line */
		int PinXclk;  /*!< GPIO pin for camera XCLK line */
		int PinSda;   /*!< GPIO pin for camera SDA line */
		int PinScl;   /*!< GPIO pin for camera SCL line */
		int PinD7;	/*!< GPIO pin for camera D7 line */
		int PinD6;	/*!< GPIO pin for camera D6 line */
		int PinD5;	/*!< GPIO pin for camera D5 line */
		int PinD4;	/*!< GPIO pin for camera D4 line */
		int PinD3;	/*!< GPIO pin for camera D3 line */
		int PinD2;	/*!< GPIO pin for camera D2 line */
		int PinD1;	/*!< GPIO pin for camera D1 line */
		int PinD0;	/*!< GPIO pin for camera D0 line */
		int PinVsync; /*!< GPIO pin for camera VSYNC line */
		int PinHref;  /*!< GPIO pin for camera HREF line */
		int PinPclk;  /*!< GPIO pin for camera PCLK line */

		int XclkFreqHz; /*!< Frequency of XCLK signal, in Hz */

		ledc_timer_t Timer;			 /*!< LEDC timer to be used for generating XCLK  */
		ledc_channel_t TimerChannel; /*!< LEDC channel to be used for generating XCLK  */

		CameraPixelFormat PixelFormat;
		CameraFrameSize FrameSize;

		int JPEGQuality;
	};

	Camera(Gpio *IoPins);
	~Camera();

private:


};
} // namespace Hal

#endif /* MAIN_INCLUDE_HAL_CAMERA_CAMERA_H_ */
