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
ASurvivalPlayerController* Globals::GetLocalPlayerController() const
{
    if (gWorld)
    {
        return reinterpret_cast<ASurvivalPlayerController*>(gWorld->OwningGameInstance->LocalPlayers[0]->
            PlayerController);
    }
    return nullptr;
}

ULocalPlayer* Globals::GetLocalPlayer()
{
    TArray<ULocalPlayer*>& lPlayers = (*UWorld::GWorld)->OwningGameInstance->LocalPlayers;
    return lPlayers[0];
}

void Globals::Tick(UCanvas* canvas)
{
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    currentCanvas = canvas;
    ScreenCenterPos.X = canvas->SizeX / 2;
    ScreenCenterPos.Y = canvas->SizeY / 2;

    gWorld = *UWorld::GWorld;
    if (!gWorld)
        return;

    if (!RobotoFont)
    {
        RobotoFont = UObject::FindObject<UFont>("Font Roboto.Roboto");

        SetConsoleTextAttribute(hConsole, 4);
        LOG("Roboto font: %p", RobotoFont); // NOLINT(clang-diagnostic-format-pedantic)
        SetConsoleTextAttribute(hConsole, 1);
    }
    if (!kismet_material_library)
    {
        kismet_material_library = reinterpret_cast<UKismetMaterialLibrary*>(
            UKismetMaterialLibrary::StaticClass());
    }
    if (!kismet_math_library)
    {
        kismet_math_library = reinterpret_cast<UKismetMathLibrary*>(UKismetMathLibrary::StaticClass());
    }
    if (!gameplay_statics)
    {
        gameplay_statics = reinterpret_cast<UGameplayStatics*>(UGameplayStatics::StaticClass());
    }

    if (!kismet_text_library)
    {
        kismet_text_library = reinterpret_cast<UKismetTextLibrary*>(UKismetTextLibrary::StaticClass());
    }
    if (!kismet_system_library)
    {
        kismet_system_library = reinterpret_cast<UKismetSystemLibrary*>(UKismetSystemLibrary::StaticClass());
    }
    ULocalPlayer* localPlayer = GetLocalPlayer();
    if (!localPlayer)
        return;
    gController = reinterpret_cast<ASurvivalPlayerController*>(localPlayer->PlayerController);
    if (!gController)
        return;

    gCharacter = reinterpret_cast<ASurvivalCharacter*>(gController->AcknowledgedPawn);
    if (gCharacter)
        return;
    if (!gCharacter->RootComponent)
        return;
}