#include <windows.h>


BOOL APIENTRY DllMain( HMODULE hModule,
                       DWORD u1_reason_for_call,
                       LPVOID lpReserved
                    )
{
    switch(u1_reason_for_call)
    {
    case DLL_PROCESS_ATTACH:
        MessageBox(NULL, "Injected!", "Success", NULL); //lol oops retard moment
    case DLL_THREAD_ATTACH:
    case DLL_THREAD_DETACH:
    case DLL_PROCESS_DETACH:
        break;
    }
    return TRUE;
}
