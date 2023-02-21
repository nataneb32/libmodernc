#include "../lib/allocator.h"
#include "../lib/arena.h"
#include "../lib/string.h"
#include <stdio.h>

int main() {
  arena_allocator_t *arena = arena_allocator_new();
  ctx_t ctx = (ctx_t){.allocator = &arena->allocator};

  string_t *a = string_new(&ctx, "fuzz");
  printf("%s\n", string_to_str(a));

  string_destroy(a, &ctx);

  arena_destroy(arena);
  return 0;
}


