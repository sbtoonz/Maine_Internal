#include "pch.h"
#include "GUI.h"
GUI* GUI::gui_ = nullptr;

GUI* GUI::GetGUI()
{
    if(gui_ == nullptr)
    {
        gui_ = new GUI();
    }
    return gui_;
}
