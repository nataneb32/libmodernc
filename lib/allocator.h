#ifndef LIBMC_ALLOCATOR_H
#define LIBMC_ALLOCATOR_H

#include <stdlib.h>

typedef struct allocator {
  void *(*alloc)(struct allocator *self, size_t size);
  void (*free)(struct allocator *self, void *ptr);
} allocator_t;

void *allocator_alloc(allocator_t *self, size_t size) {
	return self->alloc(self, size);
}

void allocator_free(allocator_t *self, void *ptr) {
	self->free(self, ptr);
}

#endif
