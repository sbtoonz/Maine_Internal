#include "pch.h"
#include "PR_HK.h"

#include "../Features/FeatureCore.h"


void PR_HK::h_post_render(UGameViewportClient* viewport_client, UCanvas* canvas)
{
    if (canvas)
    {
       if(!SetHook)
       {
           if (HookManager::Detour(reinterpret_cast<void**>(&PE_HK::o_process_event),
                                    reinterpret_cast<void*>(&PE_HK::process_event_hook)))
           {
               LOG("Set PE Hook");
               SetHook = true;
           }
       }
        Globals::GetGlobals()->Tick(canvas);
        FeatureCore::GetFeatureCore()->Tick();
    }
    oPostRender(viewport_client, canvas);
}
