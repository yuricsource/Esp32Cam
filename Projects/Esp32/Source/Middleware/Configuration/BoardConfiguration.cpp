#include "BoardConfiguration.h"

#define TEST_CLIENT

namespace Middleware
{
namespace Configuration
{

void BoardConfiguration::DefaultConfiguration()
{
    _configuration.GeneralFlags.Settings.Flags.WifiEnabled = true;
    _configuration.WifiConfig.Settings.Flags.DhcpEnabled = true;

#ifdef TEST_CLIENT
    /*Client Configuration*/
    _configuration.WifiConfig.WifiMode = WifiModeConfiguration::Client;
    sprintf(_configuration.WifiConfig.Ssid.data(),"%s","Yuri_Duda");
    sprintf(_configuration.WifiConfig.Password.data(),"%s","Australia2us");
#else
    /*HotSpot Configuration*/
    _configuration.WifiConfig.Channel = 8;
    _configuration.WifiConfig.WifiMode = WifiModeConfiguration::HotSpot;
    sprintf(_configuration.WifiConfig.Ssid.data(),"%s","WebCamera hotspot");
    sprintf(_configuration.WifiConfig.Password.data(),"%s","12345678");
    _configuration.WifiConfig.AuthenticationMode = WifiAuthenticationMode::Wpa2Psk;
#endif
}

BoardConfiguration::BoardConfiguration()
{
    
}

BoardConfiguration::~BoardConfiguration()
{
    
}

} // namespace Configuration
} // namespace Middleware