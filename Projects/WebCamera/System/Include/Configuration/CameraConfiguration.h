#pragma once

#include "Crc32xZlib.h"
#include "lwip/ip_addr.h"
#include "ConfigurationCommon.h"
#include "HalCommon.h"
#include "BaseConfiguration.h"

namespace Configuration
{

using Utilities::Crc32xZlib;
using Hal::CameraPixelFormat;
using Hal::CameraFrameSize;
using Hal::CameraModelType;
using Hal::CameraGainCeiling;
using Hal::CameraSpecialEffect;
using Hal::CameraWhiteBalanceMode;

struct CameraConfigurationData
{
    /// @brief	General Camera configuration.
    struct GeneralConfiguration
    {
        /// @brief	Configuration flags
        union _Settings {
            struct
            {
                bool StreamEnabled : 1;
                uint32_t _NotUsed : 31;
            } Flags;
            uint32_t AllFlags;
        } Settings;
    };

    GeneralConfiguration GeneralConfig = {};
    CameraPixelFormat PixelFormat = CameraPixelFormat::CameraPixelFormatJPEG;
    CameraFrameSize FrameSize = CameraFrameSize::CameraFrameSizeSVGA;
    CameraModelType ModelType = CameraModelType::CameraNone;
    uint8_t FrameBufferCount = 1;
    uint8_t Quality = 10;
    int Contrast = 0;
    int Brightness = 0;
    int Saturation = 0;
    CameraGainCeiling GainCeiling = CameraGainCeiling::Gain2; 
    bool ColourBar = false;
    bool AutoBalance = false;
    bool AutoGain = true;
    bool AutoExposure = true;
    bool HorizontalMirror = true;
    bool VerticalMirror = true;
    bool AutoBalanceGain = true;
    int ManualGainCeiling = true;
    int ExposureTime = 204;
    bool ExposureDsp = true;
    bool DownsizeEN = true;
    bool Bpc = false;
    bool Wpc = true;
    bool RawGma = true;
    bool LensCorrection = true;
    CameraSpecialEffect SpecialEffect = CameraSpecialEffect::None;
    CameraWhiteBalanceMode WhiteBalanceMode = CameraWhiteBalanceMode::Auto;
    int AutoExposureLevel = 0;

    CameraConfigurationData() :
    GeneralConfig()
    {

    }

    uint32_t GetCRC() const
    {
        return Crc32xZlib::GetCrc((unsigned char *)this, sizeof(CameraConfigurationData), Crc32xZlib::Polynomial);
    }
};

class CameraConfiguration : public BaseConfiguration
{
public:
    CameraConfiguration();
    ~CameraConfiguration();

    const CameraConfigurationData *GetConfiguration() {return &_configuration;}
    void DefaultConfiguration();

private:
    CameraConfigurationData _configuration = {};

private:
    /// @brief	Hide Copy constructor.
    CameraConfiguration(const CameraConfiguration &) = delete;

    /// @brief	Hide Assignment operator.
    CameraConfiguration &operator=(const CameraConfiguration &) = delete;

    /// @brief	Hide Move constructor.
    CameraConfiguration(CameraConfiguration &&) = delete;

    /// @brief	Hide Move assignment operator.
    CameraConfiguration &operator=(CameraConfiguration &&) = delete;
};

} // namespace Configuration