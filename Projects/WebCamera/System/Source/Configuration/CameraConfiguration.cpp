#include "CameraConfiguration.h"

namespace Configuration
{

CameraConfiguration::CameraConfiguration()
{

}

CameraConfiguration::~CameraConfiguration()
{

}

void CameraConfiguration::DefaultConfiguration()
{
    _configuration.FrameSize = CameraFrameSize::CameraFrameSizeXGA;
    _configuration.ModelType = CameraModelType::CameraOV2640;
    _configuration.PixelFormat = CameraPixelFormat::CameraPixelFormatJPEG;
}


} // namespace Configuration