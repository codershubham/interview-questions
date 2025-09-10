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

/*
	mem_alloc: Allocate memory with guard bytes and track it
	Allocates memory of given size, adds guard bytes before and after,
	and tracks the allocation in a linked list.

	Example:
		char* p = mem_alloc(100, __FILE__, __LINE__);
		strcpy(p, "Hello, World!");
*/

void* mem_alloc(size_t size, const char* file, int line) {
	size_t total_size = size + 2 * GUARD_SIZE;
	unsigned char* real_ptr = (unsigned char*)malloc(total_size);
	if(!real_ptr) {
		fprintf(stderr, "Memory allocation failed at %s:%d\n", file, line);
		return NULL;
	}

	// Set guard bytes
	set_guard_bytes(real_ptr, GUARD_SIZE);
	set_guard_bytes(real_ptr + GUARD_SIZE + size, GUARD_SIZE);

	void* user_ptr = real_ptr + GUARD_SIZE;

	// Create a new MemNode
	MemNode* node = (MemNode*)malloc(sizeof(MemNode));
	if(!node) {
		fprintf(stderr, "Memory allocation for tracking failed at %s:%d\n", file, line);
		free(real_ptr);
		return NULL;
	}
	node->real_ptr = real_ptr;
	node->user_ptr = user_ptr;
	node->size = size;
	node->file = file;
	node->line = line;
	node->freed = 0;
	node->next = head;
	head = node;

	return user_ptr;
}

/*
	mem_free: Free memory and check for overruns/underruns
	Frees the memory allocated by mem_alloc, checks guard bytes,
	and removes the tracking node.

	Example:
		char* p = mem_alloc(100, __FILE__, __LINE__);
		// use p
		mem_free(p, __FILE__, __LINE__);
*/

void mem_free(void* ptr, const char* file, int line) {
	if(!ptr) {
		fprintf(stderr, "Attempt to free NULL pointer at %s:%d\n", file, line);
		return;
	}

	MemNode* prev = NULL;
	MemNode* curr = head;

	// Find the node in the linked list
	while(curr) {
		if(curr->user_ptr == ptr) {
			break;
		}
		prev = curr;
		curr = curr->next;
	}

	if(!curr) {
		fprintf(stderr, "Attempt to free untracked pointer at %s:%d\n", file, line);
		return;
	}

	if(curr->freed) {
		fprintf(stderr, "Double free detected at %s:%d (originally freed at %s:%d)\n", 
				file, line, curr->file, curr->line);
		return;
	}

	// Check guard bytes
	unsigned char* real_ptr = (unsigned char*)curr->real_ptr;
	if(!check_guard_bytes(real_ptr, GUARD_SIZE)) {
		fprintf(stderr, "Buffer underrun detected for memory allocated at %s:%d\n", curr->file, curr->line);
	}
	if(!check_guard_bytes(real_ptr + GUARD_SIZE + curr->size, GUARD_SIZE)) {
		fprintf(stderr, "Buffer overrun detected for memory allocated at %s:%d\n", curr->file, curr->line);
	}

	// Free the actual memory
	free(real_ptr);
	curr->freed = 1;

	// Remove node from linked list
	if(prev) {
		prev->next = curr->next;
	} else {
		head = curr->next;
	}
	free(curr);
}

/* mem_report: Generate a report of all allocated memory blocks
   This function traverses the linked list of memory allocations
   and prints information about each allocated block.

   Example:
       mem_report();
*/
void mem_report(void) {
	MemNode* curr = head;
	while(curr) {
		printf("Memory block at %p (size: %zu, allocated at %s:%d)\n",
				curr->user_ptr, curr->size, curr->file, curr->line);
		curr = curr->next;
	}
}