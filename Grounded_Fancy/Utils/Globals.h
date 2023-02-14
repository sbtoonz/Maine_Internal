#pragma once

class Globals
{
public:
    Globals() = default;
    ~Globals() = default;
    static Globals* GetGlobals();
    static Globals* globals_;
    ASurvivalPlayerController* GetLocalPlayerController() const;
    static ULocalPlayer* GetLocalPlayer();
    void Tick(UCanvas* canvas);
    UCanvas* currentCanvas = nullptr;
    UGameplayStatics* gameplay_statics = nullptr;
    UKismetTextLibrary* kismet_text_library = nullptr;
    UKismetMaterialLibrary* kismet_material_library = nullptr;
    UKismetMathLibrary* kismet_math_library = nullptr;
    UKismetSystemLibrary* kismet_system_library = nullptr;
    UWorld* gWorld = nullptr;
    ASurvivalCharacter* gCharacter = nullptr;
    ASurvivalPlayerController* gController = nullptr;
    UFont* RobotoFont = nullptr;
    FVector2D ScreenCenterPos{};
    FName paramName;
};
