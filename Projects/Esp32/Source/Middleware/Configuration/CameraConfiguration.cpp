#include "CameraConfiguration.h"

namespace Middleware
{
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
    _configuration.FrameSize = CameraFrameSize::CameraFrameSizeQVGA;
    _configuration.ModelType = CameraModelType::CameraOV2640;
    _configuration.PixelFormat = CameraPixelFormat::CameraPixelFormatJPEG;
}


} // namespace Configuration
} // namespace Middleware