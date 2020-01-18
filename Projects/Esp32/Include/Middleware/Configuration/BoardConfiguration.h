#pragma once

#include "Crc32xZlib.h"
#include "lwip/ip_addr.h"
#include "BaseConfiguration.h"
#include "ConfigurationCommon.h"
#include "HalCommon.h"

namespace Middleware
{
namespace Configuration
{

using Utilities::Crc32xZlib;
using Hal::WifiModeConfiguration;
using Hal::WifiAuthenticationMode;
using Hal::MacAddress;
using Hal::WifiPassword;
using Hal::WifiSsid;

struct BoardConfigurationData
{
    /// @brief	General Board configuration.
    struct GeneralConfiguration
    {
        /// @brief	Configuration flags
        union _Settings {
            struct
            {
                bool WifiEnabled : 1;
                uint8_t _NotUsed : 7;
            } Flags;
            uint8_t AllFlags;
        } Settings;
    };
    /// @brief	Wifi configuration.
    struct WifiConfiguration
    {
        ip_addr_t IPAddress = {};
        ip_addr_t Mask = {};
        ip_addr_t GatewayAddress = {};
        ip_addr_t DnsServer = {};
        WifiModeConfiguration WifiMode = WifiModeConfiguration::Client;
        WifiAuthenticationMode AuthenticationMode = WifiAuthenticationMode::Open;
        uint8_t Channel = 0;
        WifiSsid Ssid = {};
        WifiPassword Password = {};
        MacAddress Mac = {};

        union _Settings {
            struct
            {
                bool DhcpEnabled : 1;
                uint8_t _NotUsed : 7;
            } Flags;
            uint8_t AllFlags;
        } Settings;

        uint32_t GetCRC() const
        {
            return Crc32xZlib::GetCrc((unsigned char *)this, sizeof(WifiConfiguration), Crc32xZlib::Polynomial);
        }
    };

    GeneralConfiguration GeneralFlags;
    WifiConfiguration WifiConfig;

    BoardConfigurationData() :
    GeneralFlags(),
    WifiConfig()
    {
    }

    uint32_t GetCRC() const
    {
        return Crc32xZlib::GetCrc((unsigned char *)this, sizeof(BoardConfigurationData), Crc32xZlib::Polynomial);
    }
};

class BoardConfiguration : public BaseConfiguration
{
public:
    BoardConfiguration();
    ~BoardConfiguration();

    BoardConfigurationData *GetConfiguration() {return &_configuration;}
    void DefaultConfiguration();
private:

    BoardConfigurationData _configuration = {};

private:

    /// @brief	Hide Copy constructor.
    BoardConfiguration(const BoardConfiguration &) = delete;

    /// @brief	Hide Assignment operator.
    BoardConfiguration &operator=(const BoardConfiguration &) = delete;

    /// @brief	Hide Move constructor.
    BoardConfiguration(BoardConfiguration &&) = delete;

    /// @brief	Hide Move assignment operator.
    BoardConfiguration &operator=(BoardConfiguration &&) = delete;
};

} // namespace Configuration
} // namespace Middleware