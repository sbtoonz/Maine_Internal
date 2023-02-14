#include "pch.h"
#include "PE_HK.h"

void PE_HK::process_event_hook(UObject* pCallObject, UFunction* pUFunc, void* pParms)
{
    return o_process_event(pCallObject, pUFunc, pParms);
}
