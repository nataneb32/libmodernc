#include "allocator.h"
#include <stdlib.h>

typedef struct ctx {
	allocator_t* allocator;
} ctx_t;

void* ctx_alloc(ctx_t* self, size_t size) {
	return allocator_alloc(self->allocator, size);
}
