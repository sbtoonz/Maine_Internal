#pragma once
class FeatureCore
{
public:
    static FeatureCore* GetFeatureCore();
    void Tick();
    bool Condition();
private:
    static FeatureCore* feature_core_;
};
