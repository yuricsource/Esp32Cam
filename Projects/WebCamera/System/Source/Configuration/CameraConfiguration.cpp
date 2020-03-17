#include "CameraConfiguration.h"
#include "Hardware.h"
#include "ArduinoJson.h"
#include <array>


using Hal::Camera;
using Hal::Hardware;

namespace Configuration
{

CameraConfiguration::CameraConfiguration() : BaseConfiguration("Camera Config")
{
}

CameraConfiguration::~CameraConfiguration()
{
}

void CameraConfiguration::ApplyConfiguration()
{
    Camera &camera = Hardware::Instance()->GetCamera();
    if (_configuration.GeneralConfig.Changes.Flags.FrameSize)
        camera.SetResolution(_configuration.FrameSize);

    if (_configuration.GeneralConfig.Changes.Flags.PixelFormat)
        camera.SetImageFormat(_configuration.PixelFormat);

    // if (_configuration.GeneralConfig.Changes.Flags.FrameBufferCount)
    //     camera.SetFrameBufferCount(_configuration.FrameBufferCount);

    if (_configuration.GeneralConfig.Changes.Flags.Quality)
        camera.SetQuality(_configuration.Quality);

    if (_configuration.GeneralConfig.Changes.Flags.Contrast)
        camera.SetContrast(_configuration.Contrast);

    if (_configuration.GeneralConfig.Changes.Flags.Brightness)
        camera.SetBrightness(_configuration.Brightness);

    if (_configuration.GeneralConfig.Changes.Flags.Saturation)
        camera.SetSaturation(_configuration.Saturation);

    if (_configuration.GeneralConfig.Changes.Flags.GainCeiling)
        camera.SetGainCeiling(_configuration.GainCeiling);

    if (_configuration.GeneralConfig.Changes.Flags.ColourBar)
        camera.SetColourBar(_configuration.ColourBar);

    if (_configuration.GeneralConfig.Changes.Flags.AutoWhiteBalance)
        camera.SetAutoWhiteBalance(_configuration.AutoWhiteBalance);

    if (_configuration.GeneralConfig.Changes.Flags.AutoGainControl)
        camera.SetAutoGainControl(_configuration.AutoGainControl);

    if (_configuration.GeneralConfig.Changes.Flags.AutoExposure)
        camera.SetAutoExposureControl(_configuration.AutoExposure);

    if (_configuration.GeneralConfig.Changes.Flags.HorizontalMirror)
        camera.SetHorizontalMirror(_configuration.HorizontalMirror);

    if (_configuration.GeneralConfig.Changes.Flags.VerticalMirror)
        camera.SetVerticalMirror(_configuration.VerticalMirror);

    if (_configuration.GeneralConfig.Changes.Flags.AutoBalanceGain)
        camera.SetAutoWhiteBalanceGain(_configuration.AutoBalanceGain);

    if (_configuration.GeneralConfig.Changes.Flags.ManualGainCeiling)
        camera.SetManualGainCeiling(_configuration.ManualGainCeiling);

    if (_configuration.GeneralConfig.Changes.Flags.ExposureTime)
        camera.SetExposureTime(_configuration.ExposureTime);

    if (_configuration.GeneralConfig.Changes.Flags.ExposureDsp)
        camera.SetAutoExposureDsp(_configuration.ExposureDsp);

    if (_configuration.GeneralConfig.Changes.Flags.DownsizeEN)
        camera.SetDownsizeEn(_configuration.DownsizeEN);

    if (_configuration.GeneralConfig.Changes.Flags.Bpc)
        camera.SetBPC(_configuration.Bpc);

    if (_configuration.GeneralConfig.Changes.Flags.Wpc)
        camera.SetWPC(_configuration.Wpc);

    if (_configuration.GeneralConfig.Changes.Flags.RawGma)
        camera.SetRawGma(_configuration.RawGma);

    if (_configuration.GeneralConfig.Changes.Flags.LensCorrection)
        camera.SetLensCorrection(_configuration.LensCorrection);

    if (_configuration.GeneralConfig.Changes.Flags.SpecialEffect)
        camera.SetSpecialEffect(_configuration.SpecialEffect);

    if (_configuration.GeneralConfig.Changes.Flags.WhiteBalanceMode)
        camera.SetWhiteBalanceMode(_configuration.WhiteBalanceMode);

    if (_configuration.GeneralConfig.Changes.Flags.AutoExposureLevel)
        camera.SetAutoExposureLevel(_configuration.AutoExposureLevel);

    _configuration.GeneralConfig.Changes.AllChanges = 0;
}

void CameraConfiguration::DefaultConfiguration()
{
    // Camera Driver Settings
    _configuration.GeneralConfig.Changes.Flags.FrameSize = UpdateConfig(_configuration.FrameSize, CameraFrameSize::CameraFrameSizeXGA);
    _configuration.GeneralConfig.Changes.Flags.ModelType = UpdateConfig(_configuration.ModelType, CameraModelType::CameraOV2640);
    _configuration.GeneralConfig.Changes.Flags.PixelFormat = UpdateConfig(_configuration.PixelFormat, CameraPixelFormat::CameraPixelFormatJPEG);

    // Sensor Settings
    _configuration.GeneralConfig.Changes.Flags.FrameBufferCount = UpdateConfig(_configuration.FrameBufferCount, static_cast<uint8_t>(1));
    _configuration.GeneralConfig.Changes.Flags.Quality = UpdateConfig(_configuration.Quality, static_cast<uint8_t>(10));
    _configuration.GeneralConfig.Changes.Flags.Contrast = UpdateConfig(_configuration.Contrast, 0);
    _configuration.GeneralConfig.Changes.Flags.Brightness = UpdateConfig(_configuration.Brightness, 0);
    _configuration.GeneralConfig.Changes.Flags.Saturation = UpdateConfig(_configuration.Saturation, 0);
    _configuration.GeneralConfig.Changes.Flags.GainCeiling = UpdateConfig(_configuration.GainCeiling, CameraGainCeiling::Gain2);
    _configuration.GeneralConfig.Changes.Flags.ColourBar = UpdateConfig(_configuration.ColourBar, false);
    _configuration.GeneralConfig.Changes.Flags.AutoWhiteBalance = UpdateConfig(_configuration.AutoWhiteBalance, false);
    _configuration.GeneralConfig.Changes.Flags.AutoGainControl = UpdateConfig(_configuration.AutoGainControl, true);
    _configuration.GeneralConfig.Changes.Flags.AutoExposure = UpdateConfig(_configuration.AutoExposure, true);
    _configuration.GeneralConfig.Changes.Flags.HorizontalMirror = UpdateConfig(_configuration.HorizontalMirror, true);
    _configuration.GeneralConfig.Changes.Flags.VerticalMirror = UpdateConfig(_configuration.VerticalMirror, true);
    _configuration.GeneralConfig.Changes.Flags.AutoBalanceGain = UpdateConfig(_configuration.AutoBalanceGain, true);
    _configuration.GeneralConfig.Changes.Flags.ManualGainCeiling = UpdateConfig(_configuration.ManualGainCeiling, static_cast<uint8_t>(5));
    _configuration.GeneralConfig.Changes.Flags.ExposureTime = UpdateConfig(_configuration.ExposureTime, static_cast<uint16_t>(204));
    _configuration.GeneralConfig.Changes.Flags.ExposureDsp = UpdateConfig(_configuration.ExposureDsp, true);
    _configuration.GeneralConfig.Changes.Flags.DownsizeEN = UpdateConfig(_configuration.DownsizeEN, true);
    _configuration.GeneralConfig.Changes.Flags.Bpc = UpdateConfig(_configuration.Bpc, false);
    _configuration.GeneralConfig.Changes.Flags.Wpc = UpdateConfig(_configuration.Wpc, false);
    _configuration.GeneralConfig.Changes.Flags.RawGma = UpdateConfig(_configuration.RawGma, false);
    _configuration.GeneralConfig.Changes.Flags.LensCorrection = UpdateConfig(_configuration.LensCorrection, true);
    _configuration.GeneralConfig.Changes.Flags.SpecialEffect = UpdateConfig(_configuration.SpecialEffect, CameraSpecialEffect::None);
    _configuration.GeneralConfig.Changes.Flags.WhiteBalanceMode = UpdateConfig(_configuration.WhiteBalanceMode, CameraWhiteBalanceMode::Auto);
    _configuration.GeneralConfig.Changes.Flags.AutoExposureLevel = UpdateConfig(_configuration.AutoExposureLevel, 0);
}

} // namespace Configuration