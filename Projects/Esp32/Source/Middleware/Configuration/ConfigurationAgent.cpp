#include "ConfigurationAgent.h"

namespace Middleware
{
namespace Configuration
{

ConfigurationAgent::ConfigurationAgent()
{
}

ConfigurationAgent::~ConfigurationAgent()
{
}

void ConfigurationAgent::UseDefaultConfiguration()
{
    _boardConfiguration.DefaultConfiguration();
    _cameraConfiguration.DefaultConfiguration();
}

void ConfigurationAgent::DefaulAllConfigurations()
{
    _boardConfiguration.DefaultConfiguration();
    _cameraConfiguration.DefaultConfiguration();
    
    // Save afterwards
}

} // namespace Configuration
} // namespace Middleware