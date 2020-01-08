#include "ApplicationManager.h"

namespace Applications
{

ApplicationManager *ApplicationManager::_applications;

ApplicationManager::ApplicationManager()
{
    if (_applications == nullptr)
    {
        _applications = this;
    }
    else
    {
        printf("Error!\n");
    }
}

void ApplicationManager::Initialize()
{
    _wifiService = new WifiService();
    _httpServer = new HttpServer(80);
}

} // namespace Applications
