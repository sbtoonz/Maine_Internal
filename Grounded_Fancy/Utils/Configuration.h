#pragma once

class Configuration
{
public:
    Configuration() = default;
    ~Configuration() = default;
    static Configuration* GetConfig();
private:
    static Configuration* configuration_;
};
