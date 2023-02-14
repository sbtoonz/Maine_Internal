#pragma once
#include "PE_HK.h"

class PR_HK
{
public:
    static void WINAPI WINAPI h_post_render(CG::UGameViewportClient* viewport_client, CG::UCanvas* canvas);
    typedef void (* PostRenderFn)(CG::UGameViewportClient*, CG::UCanvas*);
    inline static PostRenderFn oPostRender = nullptr;
private:
    inline static bool SetHook = false;
};
