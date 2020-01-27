#pragma once

#include "Hardware.h"
#include "WifiService.h"
#include "HttpServer.h"
#include "DnsClient.h"
#include "GatewayService.h"
#include "IPParser.h"

namespace Applications
{

class ApplicationAgent
{
public:
    ApplicationAgent();

    void Initialize();

    static inline ApplicationAgent *Instance()
    {
        if (_applications == nullptr)
        {
            _applications = new ApplicationAgent();
        }
        return _applications;
    }

    WifiService& GetWifi() {return *_wifiService;};
    HttpServer& GetHttpServer(){return *_httpServer;};
    GatewayService& GetGatewayService(){ return *_gatewayService;};

private:
    static ApplicationAgent *_applications;
    WifiService *_wifiService;
    HttpServer *_httpServer;
    GatewayService *_gatewayService;

private:
    /// @brief	Hide Copy constructor.
    ApplicationAgent(const ApplicationAgent &) = delete;

    /// @brief	Hide Assignment operator.
    ApplicationAgent &operator=(const ApplicationAgent &) = delete;

    /// @brief	Hide Move constructor.
    ApplicationAgent(ApplicationAgent &&) = delete;

    /// @brief	Hide Move assignment operator.
    ApplicationAgent &operator=(ApplicationAgent &&) = delete;
};

} // namespace Applications