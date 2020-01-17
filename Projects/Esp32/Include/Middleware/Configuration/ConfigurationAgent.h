#pragma once

#include "Crc32xZlib.h"
#include "lwip/ip_addr.h"
#include "ConfigurationCommon.h"
#include "HalCommon.h"
#include "BoardConfiguration.h"

namespace Middleware
{
namespace Configuration
{

class ConfigurationAgent
{
public:

    ConfigurationAgent();

    ~ConfigurationAgent();

    static inline ConfigurationAgent *Instance()
    {
        if (_configurations == nullptr)
        {
            _configurations = new ConfigurationAgent();
        }
        return _configurations;
    }

    BoardConfiguration *GetBoardConfiguration() {return &boardConfiguration;}

private:

static ConfigurationAgent *_configurations;
BoardConfiguration boardConfiguration = {};


private:
    /// @brief	Hide Copy constructor.
    ConfigurationAgent(const ConfigurationAgent &) = delete;

    /// @brief	Hide Assignment operator.
    ConfigurationAgent &operator=(const ConfigurationAgent &) = delete;

    /// @brief	Hide Move constructor.
    ConfigurationAgent(ConfigurationAgent &&) = delete;

    /// @brief	Hide Move assignment operator.
    ConfigurationAgent &operator=(ConfigurationAgent &&) = delete;
};

} // namespace Configuration
} // namespace Middleware