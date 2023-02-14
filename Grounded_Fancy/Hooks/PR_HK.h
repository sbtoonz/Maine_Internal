#pragma once
#include "PE_HK.h"

class PR_HK
{
public:
    static void WINAPI WINAPI h_post_render(UGameViewportClient* viewport_client, UCanvas* canvas);
    typedef void (* PostRenderFn)(UGameViewportClient*, UCanvas*);
    inline static PostRenderFn oPostRender = nullptr;
private:
    inline static bool SetHook = false;
};
