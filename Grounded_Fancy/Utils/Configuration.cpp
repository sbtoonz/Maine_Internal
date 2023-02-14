#include "pch.h"
#include "Configuration.h"
Configuration* Configuration::configuration_ = nullptr;

Configuration* Configuration::GetConfig()
{
    if(configuration_ == nullptr)
    {
        configuration_ = new Configuration();
    }
    return configuration_;
}
