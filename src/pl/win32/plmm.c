#include <pl/mm.h>
#include <windows.h>




void* pl_mm_reserve_memory(size_t size){
    return VirtualAlloc(NULL, size, MEM_RESERVE, PAGE_EXECUTE_READWRITE);
}



void* pl_mm_commit_memory(void* memory, size_t size){
    return VirtualAlloc(memory, size, MEM_COMMIT, PAGE_EXECUTE_READWRITE);
}

void pl_mm_decommit_memory(void* memory, size_t size){
    bool result = VirtualFree(memory, size, MEM_DECOMMIT);
    if(result == FALSE){
        DEBUG_WARNING("VirtualFree returned FALSE\n");
    }
}

void* pl_mm_free_memory(void* memory){
    bool result = VirtualFree(memory, 0, MEM_RELEASE);
    if(result == FALSE){
        DEBUG_WARNING("VirtualFree returned FALSE\n");
    }
}
