#pragma once

class GUI
{
public:
    GUI() = default;
    ~GUI() = default;
    static GUI* GetGUI();
private:
    static GUI* gui_;
};
