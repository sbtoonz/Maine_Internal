#pragma once
#define NOMINMAX
#define WIN32_LEAN_AND_MEAN
#include <detours.h>
#include <detver.h>
#include <syelog.h>
#include <unordered_map>
#include <Windows.h>

struct DETOUR_ALIGN
{
    BYTE    obTarget : 3;
    BYTE    obTrampoline : 5;
};

struct DETOUR_INFO
{
    // An X64 instuction can be 15 bytes long.
    // In practice 11 seems to be the limit.
    BYTE            rbCode[30];     // target code + jmp to pbRemain.
    BYTE            cbCode;         // size of moved target code.
    BYTE            cbCodeBreak;    // padding to make debugging easier.
    BYTE            rbRestore[30];  // original target code.
    BYTE            cbRestore;      // size of original target code.
    BYTE            cbRestoreBreak; // padding to make debugging easier.
    DETOUR_ALIGN    rAlign[8];      // instruction alignment array.
    PBYTE           pbRemain;       // first instruction after moved code. [free list]
    PBYTE           pbDetour;       // first instruction of detour function.
    BYTE            rbCodeIn[8];    // jmp [pbDetour]
};

using lpGetValueFnc = INT64 (*)();

class HookManager
{
private:
    static inline std::unordered_map<void**, void*> detours_;
    
public:
    static void SwapVmt(void* instance, const int32_t vmtIndex, void* hkFunc, void** outOriginalFunc)
    {
        void** index = *static_cast<void***>(instance);
        if (outOriginalFunc)
            *outOriginalFunc = index[vmtIndex];

        DWORD virtualProtect;
        VirtualProtect(&index[vmtIndex], 0x8, PAGE_EXECUTE_READWRITE, &virtualProtect);
        index[vmtIndex] = hkFunc;
        VirtualProtect(&index[vmtIndex], 0x8, virtualProtect, &virtualProtect);
    }

    static void UnSwapVmt(void* instance, const int32_t vmtIndex, void* originalFunc)
    {
        void** index = *static_cast<void***>(instance);

        DWORD virtualProtect;
        VirtualProtect(&index[vmtIndex], 0x8, PAGE_EXECUTE_READWRITE, &virtualProtect);
        index[vmtIndex] = originalFunc;
        VirtualProtect(&index[vmtIndex], 0x8, virtualProtect, &virtualProtect);
    }

    static bool Detour(void** originalFunctionPointer, void* detourPointer)
    {
        detours_.emplace(originalFunctionPointer, detourPointer);

        DetourTransactionBegin();
        DetourUpdateThread(GetCurrentThread());
        DetourAttach(originalFunctionPointer, detourPointer);

        return DetourTransactionCommit() == NO_ERROR;
    }
    static bool UnDetour(void** originalFunctionPointer, void* detourPointer)
    {
        detours_.erase(originalFunctionPointer);

        DetourTransactionBegin();
        DetourUpdateThread(GetCurrentThread());
        DetourDetach(originalFunctionPointer, detourPointer);

        return DetourTransactionCommit() == NO_ERROR;
    }
    
    static bool DetourApi(void** originalFunctionPointer, void* detourPointer)
        {
            detours_.emplace(originalFunctionPointer, detourPointer);
            PDETOUR_TRAMPOLINE lpTrampolineData = {}; 
            DetourTransactionBegin();
            DetourUpdateThread(GetCurrentThread());
            DetourAttachEx(originalFunctionPointer, detourPointer, &lpTrampolineData, nullptr, nullptr); //Use DetourAtttachEx to retrieve information about the hook
            DetourTransactionCommit();
            return DetourTransactionCommit() == NO_ERROR;
        }
        
    static void UnDetourAll()
    {
        for (std::pair<void** const, void*>& detour : detours_)
        {
            void** originalFn = detour.first;
            void* detourFn = detour.second;

            UnDetour(originalFn, detourFn);
        }
    }

    //https://www.unknowncheats.me/forum/c-and-c-/441262-hooking-x64.html
    static void* DetourFunctionASM64(void* pSource, void* pDestination, int dwLen)
    {
        const DWORD MinLen = 14;
 
        BYTE stub[] = {
            0xFF, 0x25, 0x00, 0x00, 0x00, 0x00, // jmp qword ptr [$+6]
            0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 // ptr
            };
 
        void* pTrampoline = VirtualAlloc(0, dwLen + sizeof stub, MEM_COMMIT | MEM_RESERVE, PAGE_EXECUTE_READWRITE);
 
        DWORD dwOld = 0;
        VirtualProtect(pSource, dwLen, PAGE_EXECUTE_READWRITE, &dwOld);
 
        DWORD64 retto = (DWORD64)pSource + dwLen;
 
        // trampoline
        memcpy(stub + 6, &retto, 8);
        memcpy(reinterpret_cast<void*>(reinterpret_cast<DWORD_PTR>(pTrampoline)), pSource, dwLen);
        memcpy(reinterpret_cast<void*>(reinterpret_cast<DWORD_PTR>(pTrampoline) + dwLen), stub, sizeof stub);
 
        // orig
        memcpy(stub + 6, &pDestination, 8);
        memcpy(pSource, stub, sizeof stub);
 
        for (int i = MinLen; i < dwLen; i++)
        {
            *reinterpret_cast<BYTE*>(reinterpret_cast<DWORD_PTR>(pSource) + i) = 0x90;
        }
 
        VirtualProtect(pSource, dwLen, dwOld, &dwOld);
        return reinterpret_cast<void*>(reinterpret_cast<DWORD_PTR>(pTrampoline));
    }

};
