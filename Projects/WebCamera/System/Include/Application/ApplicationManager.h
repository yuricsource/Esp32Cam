#pragma once

#include "Hardware.h"
#include "WifiService.h"
#include "HttpServer.h"

namespace Applications
{

class ApplicationManager
{
public:
    ApplicationManager();

    void Initialize();

    static inline ApplicationManager *Instance()
    {
        if (_applications == nullptr)
        {
            _applications = new ApplicationManager();
        }
        return _applications;
    }

    WifiService& GetWifi() {return *_wifiService;};
    HttpServer& GetHttpServer(){return *_httpServer;};
private:
    static ApplicationManager *_applications;
    WifiService *_wifiService;
    HttpServer *_httpServer;

private:
    /// @brief	Hide Copy constructor.
    ApplicationManager(const ApplicationManager &) = delete;

    /// @brief	Hide Assignment operator.
    ApplicationManager &operator=(const ApplicationManager &) = delete;

    /// @brief	Hide Move constructor.
    ApplicationManager(ApplicationManager &&) = delete;

    /// @brief	Hide Move assignment operator.
    ApplicationManager &operator=(ApplicationManager &&) = delete;
};

} // namespace Applications