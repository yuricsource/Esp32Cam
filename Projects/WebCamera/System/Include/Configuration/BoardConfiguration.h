#pragma once

#include "Crc32xZlib.h"
#include "lwip/ip_addr.h"
#include "BaseConfiguration.h"
#include "ConfigurationCommon.h"
#include "ConnectionTypes.h"
#include "HalCommon.h"

namespace Configuration
{

using Hal::MacAddress;
using Hal::WifiAuthenticationMode;
using Hal::WifiModeConfiguration;
using Hal::WifiPassword;
using Hal::WifiSsid;
using Protocol::RemoteConnection;
using Utilities::Crc32xZlib;

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

    /// @brief	Server configuration.
    struct ServerConfiguration
    {
        RemoteConnection connection = {};

        uint32_t GetCRC() const
        {
            return Crc32xZlib::GetCrc((unsigned char *)this, sizeof(ServerConfiguration), Crc32xZlib::Polynomial);
        }
    };

    GeneralConfiguration GeneralFlags;
    WifiConfiguration WifiConfig;
    ServerConfiguration ServerConfig;

    BoardConfigurationData() : GeneralFlags(),
                               WifiConfig(),
                               ServerConfig()

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

    bool Deserialize(const char * json);
    bool Serialize(char * json, int length);
    BoardConfigurationData *GetConfiguration() { return &_configuration; }
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