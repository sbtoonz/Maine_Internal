#pragma once

class PE_HK
{
public:
    typedef void (__thiscall *tProcessEvent)(CG::UObject*, CG::UFunction*, void*);
    inline static  tProcessEvent o_process_event = nullptr;
    static void WINAPI WINAPI process_event_hook(CG::UObject* pCallObject, CG::UFunction* pUFunc, void* pParms);
};
