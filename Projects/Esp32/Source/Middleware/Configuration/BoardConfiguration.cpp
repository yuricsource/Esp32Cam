#include "BoardConfiguration.h"

namespace Middleware
{
namespace Configuration
{

void BoardConfiguration::DefaultConfiguration()
{
    _configuration.GeneralFlags.Settings.Flags.WifiEnabled = true;
    _configuration.WifiConfig.Settings.Flags.DhcpEnabled = true;
    _configuration.WifiConfig.Channel = 8;
    _configuration.WifiConfig.WifiMode = WifiModeConfiguration::HotSpot;
    sprintf(_configuration.WifiConfig.Ssid.data(),"%s","WebCamera hotspot");
    sprintf(_configuration.WifiConfig.Password.data(),"%s","12345678");
    
}

BoardConfiguration::BoardConfiguration()
{
    
}

BoardConfiguration::~BoardConfiguration()
{
    
}

} // namespace Configuration
} // namespace Middleware