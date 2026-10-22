#ifndef PLMM_H_INCLUDED
#define PLMM_H_INCLUDED


#include <vermilion.h>



void* pl_mm_reserve_memory(size_t size);
void* pl_mm_commit_memory(void* memory, size_t size);
void pl_mm_decommit_memory(void* memory, size_t size);
void* pl_mm_free_memory(void* memory);















#endif
