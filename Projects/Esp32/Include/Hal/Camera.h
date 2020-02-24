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

	bool initialized = false;

	~Camera();
	
private:

camera_config_t _cameraConfig = {};
camera_fb_t *_frameBuffer = nullptr;

};
} // namespace Hal

#endif /* MAIN_INCLUDE_HAL_CAMERA_CAMERA_H_ */
