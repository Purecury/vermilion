
#include <vermilion.h>
#include <mm/arena.h>
#include <windows.h>

extern vnstatus_t vn_entry(startinfo_t* info);

int main(int argc, const char** argv){
    SYSTEM_INFO info = {0};
    GetSystemInfo(&info);
    DEBUG_INFO("starting vermilion on %d cpus\n", (int)info.dwNumberOfProcessors);
    vnarena_t* globalArena = mm_create_arena((size_t)GB(256), 0, 0);

    // TODO: make these two be in a global arena instead
    HANDLE* hThreads = mm_arena_push(globalArena, info.dwNumberOfProcessors * sizeof(HANDLE));
    startinfo_t* startInfo = mm_arena_push(globalArena, info.dwNumberOfProcessors * sizeof(startinfo_t));

    for(DWORD i = 0; i < info.dwNumberOfProcessors; i++){
        startInfo[i].arg = argv;
        startInfo[i].argCount = argc;
        startInfo[i].tId = i;
        hThreads[i] = CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)vn_entry, (LPVOID)&startInfo[i], 0, NULL);
        if(hThreads[i] == NULL){
            DEBUG_FAIL("couldn't create thread %d, winerror %d\n", (int)i, (int)GetLastError());
            goto FAIL;
        }
    }

    WaitForMultipleObjects(info.dwNumberOfProcessors, hThreads, TRUE, INFINITE);

    FAIL:
    mm_destroy_arena(globalArena);
    return 0;
}
