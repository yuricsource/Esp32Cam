#pragma once

namespace Middleware
{
namespace Configuration
{

class BaseConfiguration
{
public:

    virtual void DefaultConfiguration() = 0;
    BaseConfiguration()
    {
    }
    
    ~BaseConfiguration()
    {
    }

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
} // namespace Middleware