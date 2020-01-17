#pragma once

#include "Crc32xZlib.h"
#include "lwip/ip_addr.h"
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
        union __Flags {
            struct
            {
                bool WifiEnabled : 1;
                uint8_t _NotUsed : 7;
            } Flags;
            uint8_t AllFlags;
        } Flags;
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
        WifiSsid Ssid = {};
        WifiPassword Password = {};
        MacAddress Mac = {};

        union __Flags {
            struct
            {
                bool DhcpClient : 1;
                bool DhcpServer : 1;
                uint8_t _NotUsed : 6;
            } Flags;
            uint8_t AllFlags;
        } Flags;

        uint32_t GetCRC() const
        {
            return Crc32xZlib::GetCrc((unsigned char *)this, sizeof(WifiConfiguration), Crc32xZlib::Polynomial);
        }
    };

    uint32_t GetCRC() const
    {
        return Crc32xZlib::GetCrc((unsigned char *)this, sizeof(BoardConfigurationData), Crc32xZlib::Polynomial);
    }
};

class BoardConfiguration
{
public:
    BoardConfiguration();
    ~BoardConfiguration();

    BoardConfigurationData *GetConfiguration() {return &_configuration;}

private:

    BoardConfigurationData _configuration;

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