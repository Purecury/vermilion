#ifndef MMARENA_H_INCLUDED
#define MMARENA_H_INCLUDED


#include <vermilion.h>

typedef struct vnarena {
    size_t committed;
    size_t reserved;
    size_t used;

} vnarena_t;

typedef enum vnarenaflags {
    ARENA_NO_FLAGS = 0,
} vnarenaflags_t;


vnarena_t* mm_create_arena(size_t reserved, size_t committed, vnarenaflags_t flags);
void mm_destroy_arena(vnarena_t* arena);
void* mm_arena_push(vnarena_t* arena, size_t size);
bool mm_arena_pop(vnarena_t* arena, size_t size);


#endif
