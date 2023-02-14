#pragma once

class Globals
{
public:
    Globals() = default;
    ~Globals() = default;
    static Globals* GetGlobals();
private:
    static Globals* globals_;
};
