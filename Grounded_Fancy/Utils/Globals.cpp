#include "pch.h"
#include "Globals.h"

Globals* Globals::globals_ = nullptr;
Globals* Globals::GetGlobals()
{
    if(globals_ == nullptr)
    {
        globals_ = new Globals();
    }
    return globals_;
}
