#include "pch.h"
#include "PR_HK.h"


void PR_HK::h_post_render(CG::UGameViewportClient* viewport_client, CG::UCanvas* canvas)
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
    }
    oPostRender(viewport_client, canvas);
}
