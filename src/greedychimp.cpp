#include "Hooks.h"
#include "Jamflex.h"
#include "MinHook.h"
#include <Windows.h>
#include <iostream>
#include "osclient.h"

void UnhookMouseHook() {
    HHOOK jagexMouseHook =
        *(HHOOK *)((uintptr_t)GetModuleHandleA("osclient.exe") + osclient.MouseHook);

    if (UnhookWindowsHookEx(jagexMouseHook) != 0)
        std::cout << "Mouse hook boom.\n";
}

uintptr_t Entry(HMODULE hModule) {
    AllocConsole();
    FILE *f;
    freopen_s(&f, "CONOUT$", "w", stdout);

    UnhookMouseHook();

    auto PlaceHook = [](uintptr_t location, void *jmpTo, fn *original) {
        MH_CreateHook(reinterpret_cast<LPVOID>(Jamflex::clientBase + location),
                      jmpTo, reinterpret_cast<LPVOID *>(original));
    };

    // Hooks
    MH_Initialize();

    // MH_CreateHookApi(L"opengl32.dll", "wglSwapBuffers", &hwglSwapBuffers,
    //                  reinterpret_cast<void **>(&oSwapBuffers));

    PlaceHook(osclient.DoAction, &DoAction, &oDoAction);

    // PlaceHook(0xbc840, &NodeAction, &oNodeAction);
    // PlaceHook(0xbce30, &EntityAction, &oEntityAction);

    MH_EnableHook(MH_ALL_HOOKS);

    // Keepalive
    for (;;) {

        // Eject
        if (GetAsyncKeyState(VK_F1) & 1) {
            // Uncomment if you want to hook opengl. If you don't, unloading the
            // module will crash, since you haven't reverted the bytes you
            // overwrote when diverting the game's wndproc.

            // SetWindowLongPtr(Gielinor::Get().GetGameWindow(), GWLP_WNDPROC,
            //  (LONG_PTR)gameWindowProc); // Unhook
            break;
        }

        Sleep(100);
    }

    // Clean up
    {
        MH_DisableHook(MH_ALL_HOOKS);
        MH_Uninitialize();
        fclose(f);
        FreeConsole();
        FreeLibraryAndExitThread(hModule, 0);
    }
    return 0;
}

BOOL WINAPI DllMain(HMODULE hModule, DWORD fdwReason, LPVOID lpvReserved) {
    switch (fdwReason) {
    case DLL_PROCESS_ATTACH:
        CloseHandle(CreateThread(nullptr, 0, (LPTHREAD_START_ROUTINE)Entry,
                                 hModule, 0, nullptr));
    case DLL_THREAD_ATTACH:
    case DLL_THREAD_DETACH:
    case DLL_PROCESS_DETACH:
        break;
    }
    return TRUE; // Successful DLL_PROCESS_ATTACH.
}