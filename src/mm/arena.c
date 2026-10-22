#include <pl/mm.h>
#include <mm/arena.h>
#include <rtl/mem.h>
// very simple arena so far
// TODO: make it uh.. saner and easier to debug
//
//
//
#define GET_CURRENT_BASE(arena)((void*)((uintptr_t)(arena) + (uintptr_t)arena->used))

vnarena_t* mm_create_arena(size_t reserved, size_t committed, vnarenaflags_t flags){
    (void)flags;
    vnarena_t* arena = (vnarena_t*)pl_mm_reserve_memory(reserved);
    arena = (vnarena_t*)pl_mm_commit_memory((void*)arena, committed + sizeof(vnarena_t));
    rtl_zero_mem((void*)arena, ALIGN_PAGE(committed + sizeof(vnarena_t)));
    arena->committed = ALIGN_PAGE(committed + sizeof(vnarena_t));
    arena->used = sizeof(vnarena_t);
    arena->reserved = reserved;
    return arena;
}

void mm_destroy_arena(vnarena_t* arena){
    pl_mm_decommit_memory(arena, arena->committed);
    pl_mm_free_memory(arena);
}


void* mm_arena_push(vnarena_t* arena, size_t size){
    if(arena->reserved <= arena->used + size){
        DEBUG_FAIL("arena has ran out of memory\n");
        return NULL;
    }
    if(arena->committed <= arena->used + size){
        arena->committed = (arena->committed * 2) + size;
        pl_mm_commit_memory((void*)arena, arena->committed);
        arena->committed = ALIGN_PAGE(arena->committed); // TODO: test if this is correct
    }
    void* base = GET_CURRENT_BASE(arena);
    arena->used += size;
    return base;
}


bool mm_arena_pop(vnarena_t* arena, size_t size){
    if(arena->used - size <= sizeof(vnarena_t)){
        DEBUG_WARNING("(arena->used - size) would've brought arena below header size");
        return FALSE;
    }
    arena->used -= size;
    return TRUE;
}
