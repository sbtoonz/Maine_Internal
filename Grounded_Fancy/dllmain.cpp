#include "pch.h"

#include "Pattern.h"
#include "Hooks/PE_HK.h"
#include "Hooks/PR_HK.h"

DWORD WINAPI startup_thread(LPVOID lpvoid, HMODULE hmodule)
{
    if (InitSdk())
    {
        LOG("Sdk intialized"); // NOLINT(clang-diagnostic-gnu-zero-variadic-macro-arguments)
        UWorld* world = nullptr;
        while (!world)
        {
            world = *UWorld::GWorld;
            LOG("Finding UWorld");
            if (world)
            {
                LOG("World identified %p", world);
                auto ObjPESig = reinterpret_cast<DWORD64>(FindPattern(
                    "40 55 56 57 41 54 41 55 41 56 41 57 48 81 EC ? ? ? ? 48 8D 6C 24 ? 48 89 9D ? ? ? ? 48 8B 05 ? ? ? ? 48 33 C5 48 89 85 ? ? ? ? 8B 41 0C 45 33 F6 3B 05 ? ? ? ?"));
                auto* viewport = world->OwningGameInstance->LocalPlayers[0]->ViewportClient;
                if (viewport)
                {
                    auto* vftable = *reinterpret_cast<void***>(viewport);
                    for (int i = 0; i < 150; ++i)
                    {
                        if (vftable[i] == reinterpret_cast<void*>(ObjPESig))
                        {
                            LOG("Found PE %p %i", vftable[i], i);
                            PE_HK::o_process_event = reinterpret_cast<PE_HK::tProcessEvent>(vftable[i]);
                        }
                    }

                    HookManager::SwapVmt(viewport,
                                         POST_RENDER_INDEX,
                                         reinterpret_cast<void*>(&PR_HK::h_post_render),
                                         reinterpret_cast<void**>(&PR_HK::oPostRender));
                }
            }
        }
    }
    return 0;
}


BOOL APIENTRY DllMain(HMODULE hModule,
                      DWORD ul_reason_for_call,
                      LPVOID lpReserved
)
{
    HANDLE hconsole = GetStdHandle(STD_OUTPUT_HANDLE);
    FILE* consoleout;
    switch (ul_reason_for_call)
    {
    case DLL_PROCESS_ATTACH:
        DisableThreadLibraryCalls(hModule);
        AllocConsole();
        SetConsoleTextAttribute(hconsole, 1);
        freopen_s(&consoleout, "CONOUT$", "w", stdout); // NOLINT(cert-err33-c)
        SetConsoleTextAttribute(hconsole, 4);
        LOG("Starting up..."); // NOLINT(clang-diagnostic-gnu-zero-variadic-macro-arguments)
        CreateThread(nullptr, 0, reinterpret_cast<LPTHREAD_START_ROUTINE>(startup_thread), hModule, 0, nullptr);
    // NOLINT(clang-diagnostic-cast-function-type)
        break;
    case DLL_PROCESS_DETACH:
        break;
    }
    return TRUE;
}
