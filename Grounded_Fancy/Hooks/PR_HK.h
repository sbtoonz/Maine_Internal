#pragma once

class PR_HK
{
public:
    static void WINAPI WINAPI h_post_render(CG::UGameViewportClient* viewport_client, CG::UCanvas* canvas);
private:
    typedef void (* PostRenderFn)(CG::UGameViewportClient*, CG::UCanvas*);
public:
    inline static PostRenderFn oPostRender = nullptr;
};
