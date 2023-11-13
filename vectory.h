#ifndef VEC_H
#define VEC_H

#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>

#define VEC_SUCCESS 0
#define VEC_FAILURE -1

/// Should be used default capacity
#define CAP_DEF 1

typedef struct Vec {
  size_t len;
  size_t capacity;
  size_t elt_size;
  void *data; // Generic
} Vec;

extern const Vec VEC_VOID;
// Mutating operations
int push_end(Vec *vec, void *val);
void push_front(Vec *vec, void *val);
void pop_end(Vec *vec, void *buffer, size_t n);
void *pop_front(Vec *vec);
void assign(Vec *vec);
void insert(Vec *vec, void *val, size_t idx);

// Infos
size_t len(Vec *vec);
size_t capacity(Vec *vec);
char is_initialised(Vec *vec);
char _valid_capacity(Vec *vec);
void format(Vec *vec);

// Building
char init(Vec *vec, size_t capacity,
          size_t elt_size); // Overrides the initializer constant

// Side-building
void from_array(Vec *vec, void *arr);
void from_bytes(Vec *vec, char arr[]);
void deep_copy(Vec *vec, Vec *other);

void *__vec_offset(Vec *vec, size_t idx);
void __vec_assign(Vec *vec, size_t idx, void *element);
void __realloc(Vec *vec);
#endif // VEC_H