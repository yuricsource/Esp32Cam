#pragma once

#include "Crc32xZlib.h"
#include "lwip/ip_addr.h"
#include "ConfigurationCommon.h"
#include "HalCommon.h"
#include "BaseConfiguration.h"

namespace Middleware
{
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
                uint8_t _NotUsed : 7;
            } Flags;
            uint8_t AllFlags;
        } Settings;
    };

    GeneralConfiguration GeneralConfig = {};
    CameraPixelFormat PixelFormat = CameraPixelFormat::CameraPixelFormatJPEG;
    CameraFrameSize FrameSize = CameraFrameSize::CameraFrameSizeVGA;
    CameraModelType ModelType = CameraModelType::CameraNone;

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

    CameraConfigurationData *GetConfiguration() {return &_configuration;}
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
} // namespace Middleware