#include "allocator.h"

typedef struct error {
	void (*message)(struct error *self, allocator_t *allocator);
} error_t;
