#include "allocator.h"
#include <assert.h>
#include <stdio.h>

typedef struct arena_allocator {
  allocator_t allocator;
  char *buffer;
  int size;
  int capacity;
  int count;
} arena_allocator_t;

void *arena_allocator_alloc(allocator_t *self, size_t size) {
  arena_allocator_t *arena = (arena_allocator_t *)self;
  if (arena->size + size >= arena->capacity) {
    arena->capacity *= 2;
    arena->buffer = (char *)realloc(arena->buffer, arena->capacity);
  }

  void *ptr = arena->buffer + arena->size;
  arena->size += size;
  ++arena->count;
  return ptr;
}

void arena_allocator_free(allocator_t *self, void *ptr) {
  arena_allocator_t *arena = (arena_allocator_t *)self;
  --arena->count;
}

void arena_destroy(arena_allocator_t *self) {
  printf("%d\n", self->count);
  assert(self->count <= 0);
  free(self->buffer);
  free(self);
}

arena_allocator_t *arena_allocator_new() {
  arena_allocator_t *self =
      (arena_allocator_t *)malloc(sizeof(arena_allocator_t));
  self->allocator.alloc = arena_allocator_alloc;
  self->allocator.free = arena_allocator_free;
  self->capacity = 64;
  self->size = 0;
  self->buffer = (char *)malloc(self->capacity);
  self->count = 0;
  return self;
}
