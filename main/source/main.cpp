#include <common.hpp>
#include "../utility/logger/logger.hpp"
#include "../utility/memory/signatures/signatures.hpp"
#include "../utility/invoker/invoker.hpp"

static HANDLE coreThread;
static DWORD lpThreadId = 0;

DWORD WINAPI Core(LPVOID lpParam) {
    Logger::Instance()->Initialize();
    Logger::Instance()->Log("Dumping Entrypoints... \n");

    Signatures::Instance()->Initialize();
    Invoker::Instance()->Dump();

    Logger::Instance()->Log("Goodbye! \n");

    Signatures::Instance()->Uninitialize();
    Invoker::Instance()->Uninitialize();
    Logger::Instance()->Uninitialize();

    CloseHandle(coreThread);
    FreeLibraryAndExitThread((HMODULE)lpParam, 0);
}

BOOL WINAPI DllMain(HINSTANCE hinstDLL, DWORD fdwReason, LPVOID lpvReserved) {
    UNREFERENCED_PARAMETER(lpvReserved);

    if (fdwReason == DLL_PROCESS_ATTACH) {
        DisableThreadLibraryCalls(hinstDLL);

        coreThread = CreateThread(
            nullptr, 
            0, 
            Core, 
            hinstDLL, 
            0, 
            &lpThreadId
        );
    }

    return TRUE;
}