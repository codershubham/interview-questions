#include <stdio.h>
#include "mem_manager.h"
#include <stdlib.h>

int main() {
    // Example usage of the memory manager
    char* p1 = (char*)MEM_ALLOC(100);
    char* p2 = (char*)MEM_ALLOC(200);

    // Use the allocated memory
    for(int i = 0; i < 100; i++) {
        p1[i] = 'A';
    }
    for(int i = 0; i < 200; i++) {
        p2[i] = 'B';
    }

    // Free one block and forget to free the other to simulate a leak
    MEM_FREE(p1);

    // Report memory status
    mem_report();

    // Free the remaining block
    MEM_FREE(p2);

    // Final report
    mem_report();

    return 0;
}