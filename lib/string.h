#include "allocator.h"
#include "ctx.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct string {
  char *buf;
  int len;
  int cap;
} string_t;

string_t *string_new(ctx_t *ctx, const char *value) {
  string_t *self = (string_t *)ctx_alloc(ctx, sizeof(string_t));
  self->cap = strlen(value) + 1;
  self->len = strlen(value);
  self->buf = (char *)ctx_alloc(ctx, self->cap);
  memset(self->buf, 0, self->cap);
  strcpy(self->buf, value);

  return self;
}

char *string_to_str(string_t *self) { return self->buf; }

void string_destroy(string_t *self, ctx_t *ctx) {
	allocator_free(ctx->allocator, self->buf);
	allocator_free(ctx->allocator, self);
}
