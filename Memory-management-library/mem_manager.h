#ifndef MEM_MANAGER_H
#define MEM_MANAGER_H

#include <stddef.h>

void* mem_alloc(size_t size, const char* file, int line);
void mem_free(void* ptr, const char* file, int line);
void mem_report();

#define MEM_ALLOC(size) mem_alloc(size, __FILE__, __LINE__);
#define MEM_FREE(ptr) mem_free(ptr, __FILE__, __LINE__);

#endif // MEM_MANAGER_H
