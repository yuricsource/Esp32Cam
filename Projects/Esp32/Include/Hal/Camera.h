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

	int SetResolution(CameraFrameSize frameSize);

	int SetImageFormat(CameraPixelFormat format);

	int SetImageQuality(int quality);
	
	int SetImageContrast(int contrast);

	int SetImageBrightness(int brightness);

	int SetImageSaturation(int saturation);

	int SetImageGainCeiling (CameraGainCeiling gain);

	int SetImageColourBar(bool colourBar);
	
	int SetImageAutoWhiteBalance(bool autoBalance);

	int SetImageAutoGainControl(bool autoGain);

	int SetImageAutoExposureControl(bool autoExposure);

	int SetImageHorizontalMirror(bool horizontalMirror);
	
	int SetImageVerticalMirror(bool verticalMirror);

	int SetImageAutoWhiteBalanceGain(bool autoBalanceGain);

	int SetImageAutoGainCeiling(int autoGainCeiling);

	int SetImageExposureTime(int exposureTime);

	int SetImageAutoExposureDsp(bool exposureDsp);

	int SetImageDownsizeEn(bool downsize);

	int SetImageBPC(bool bpc);

	int SetImageWPC(bool wpc);

	int SetImageRawGma(bool RawGma);

	int SetImageLensCorrection(bool lensCorrection);
	
	int SetImageSpecialEffect(CameraSpecialEffect effect);

	int SetImageWhiteBalanceMode(CameraWhiteBalanceMode mode);

	int SetImageAutoExposureLevel(int level);

	~Camera();
	
private:

	bool initialized = false;
	camera_fb_t *_frameBuffer = nullptr;
    camera_config_t _cameraConfig = {};

};
} // namespace Hal

#endif /* MAIN_INCLUDE_HAL_CAMERA_CAMERA_H_ */
