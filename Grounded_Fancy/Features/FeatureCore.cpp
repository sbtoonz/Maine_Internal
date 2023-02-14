#include "pch.h"
#include "FeatureCore.h"
FeatureCore* FeatureCore::feature_core_ = nullptr;
FeatureCore* FeatureCore::GetFeatureCore()
{
    if (!feature_core_)
    {
        feature_core_ = new FeatureCore();
        return feature_core_;
    }
    return feature_core_;
}

void FeatureCore::Tick()
{
    if (Condition())
    {
        TArray<AActor*> outactors;
        Globals::GetGlobals()->gameplay_statics->GetAllActorsOfClass(
            Globals::GetGlobals()->gWorld, AActor::StaticClass(), &outactors);

        for (int i = 0; i < outactors.Count(); i ++)
        {
            if (outactors.IsValidIndex(i))
            {
                
            }
        }
    }
}

bool FeatureCore::Condition()
{
    return Globals::GetGlobals()->gWorld;
}
