#include "vectory.h"
#include "memory.h"
#include "stdio.h"
#include <stddef.h>
#include <stdlib.h>
#include <string.h>

#define CAP_MUL 2
const Vec VEC_VOID = {.len = 0, .capacity = 0, .elt_size = 0, .data = NULL};

// Mutating operations
int push_end(Vec *vec, void *val) {
  // Checks for capacity validity and realloc in consequence
  if (!_valid_capacity(vec)) {
    __realloc(vec);
  }

  __vec_assign(vec, vec->len, val);
  vec->len++;

  return VEC_SUCCESS;
}

void push_front(Vec *vec, void *val);
void pop_end(Vec *vec, void *buffer, size_t n) {

}
void *pop_front(Vec *vec);
void assign(Vec *vec);
void insert(Vec *vec, void *val, size_t idx);

// Infos
size_t len(Vec *vec) { return vec->len; }
size_t capacity(Vec *vec) { return vec->capacity; }
char is_initialised(Vec *vec) { return (vec->data == NULL) ? 0 : 1; }
void format(Vec *vec) {
  printf("Element byte offset: %ld\nBase pointer: %p\nLength: %ld\nCapacity: "
         "%ld\n\n",
         vec->elt_size, vec->data, vec->len, vec->capacity);
}

inline char _valid_capacity(Vec *vec) {
  return (vec->len == vec->capacity) ? 0 : 1;
}

// Building
char init(Vec *vec, size_t capacity, size_t elt_size) {
  vec->capacity = capacity;
  vec->len = 0;
  vec->elt_size = elt_size;
  vec->data = malloc(capacity * elt_size);

  return (vec->data == NULL) ? VEC_FAILURE : VEC_SUCCESS;
}

// Side-building
void from_array(Vec *vec, void *arr);
void from_bytes(Vec *vec, char arr[]);
void deep_copy(Vec *vec, Vec *other);

void *__vec_offset(Vec *vec, size_t idx) {
  return vec->data + (idx * vec->elt_size);
}

void __vec_assign(Vec *vec, size_t idx, void *element) {
  void *offset = __vec_offset(vec, idx);
  memcpy(offset, element, vec->elt_size);
}

void __realloc(Vec *vec) {
  vec->capacity *= CAP_MUL; // Common factor with good (allocating cost/freq. of
                            // reallocation) balance
  void *_grbg = realloc(vec->data, vec->elt_size * vec->capacity);
}