#pragma once

class PE_HK
{
public:
    typedef void (__thiscall *tProcessEvent)(UObject*, UFunction*, void*);
    inline static  tProcessEvent o_process_event = nullptr;
    static void WINAPI WINAPI process_event_hook(UObject* pCallObject, UFunction* pUFunc, void* pParms);
};
