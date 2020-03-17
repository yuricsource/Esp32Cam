#pragma once
#include <stdio.h>
#include <cstdint>
#include <cstring>
#include <cctype>
#include "ConfigurationCommon.h"

namespace Configuration
{

class BaseConfiguration
{
public:
    template <class T>
    bool UpdateConfig(T& config, T newConfig)
    {
       if (config != newConfig)
       {
           config = newConfig;
           return true;
       }
       return false;
    }

    virtual void DefaultConfiguration() = 0;
    BaseConfiguration(const char *name) : _enabled(false)
    {
        if (name == nullptr)
            return;
        size_t size = strlen(name);
        if (size < _name.size())
        {
            memcpy(_name.data(), name, size + 1);
        }
    }

    ~BaseConfiguration()
    {
    }

    void Default()
    {
        _enabled = false;
        _name = {};
    }

    bool IsEnabled()
    {
        return _enabled;
    }

    const DeviceName GetName() const
    {
        return _name;
    }

protected:
    DeviceName _name = {};
    bool _enabled = false;

private:
    /// @brief	Hide Copy constructor.
    BaseConfiguration(const BaseConfiguration &) = delete;

    /// @brief	Hide Assignment operator.
    BaseConfiguration &operator=(const BaseConfiguration &) = delete;

    /// @brief	Hide Move constructor.
    BaseConfiguration(BaseConfiguration &&) = delete;

    /// @brief	Hide Move assignment operator.
    BaseConfiguration &operator=(BaseConfiguration &&) = delete;
};
} // namespace Configuration