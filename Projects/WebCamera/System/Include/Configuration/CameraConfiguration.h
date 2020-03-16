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

struct CameraConfigurationData
{
    /// @brief	General Camera configuration.
    struct GeneralConfiguration
    {
        /// @brief	Configuration flags
        union _Settings {
            struct
            {
                bool CameraEnabled : 1;
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