#include "mem_manager.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define GUARD_SIZE 16
#define GUARD_PATTERN 0xAB

typedef struct MemNode{
	void* real_ptr;	// Actual allocated memory ptr(include guards)
	void* user_ptr;	// Pointer returned to user(inside guards)
	size_t size;	// Size requested by user
	const char* file;	// File where allocation happened
	int line;	// line number where allocation happened
	int freed;	// whether this memory was free
	struct MemNode* next;
} MemNode;

static MemNode* head = NULL;

// helper to create guard bytes
/*
 *	Set guard bytes:
 *	Fill a memory with guard bytes to detect overrun/underrun
 *
 *	Example:
 *		unsigned char buffer[16];
 *		set_guard_bytes(buffer, 16);
*/
static void set_guard_bytes(unsigned char* ptr, size_t size) {
	memset(ptr, GUARD_PATTERN, size);
}

/*	Check_guard_bytes:
 *	Verify if the memory region still holds the guard pattern.
 *
 *	Returns 1 if intact else return 0 if overwritten
 *
 *	Example:
 *		unsigned char buffer[16];
 *		set_guard_bytes(buffer, 16);
 *		int intact = check_guard_bytes(buffer,16);
 *
*/

static int check_guard_bytes(unsigned char* ptr, size_t size) {
	for(size_t i = 0; i < size; i++) {
		if(ptr[i] != GUARD_PATTERN) {
			return 0;
		}
	}
	return 1;
}
