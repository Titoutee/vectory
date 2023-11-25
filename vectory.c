#include <memory.h>
#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include <string.h>

#include "vectory.h"

const Vec VEC_VOID = {.len = 0, .capacity = 0, .elt_size = 0, .data = NULL};

// Returns a reference to the `idx` th element of the vector.
// It should be cast to the appropriate pointer type, else UB if used with
// flawed pointer type. User-friendly wrapper around `__vec_offset_c`.
void *at(Vec *vec, size_t idx) { return __vec_offset_c(vec, idx); }

void shrink_to_fit(Vec *vec) {
  vec->capacity = vec->len;
  void *crap = realloc(vec->data, (unsigned long) vec->capacity); //Nomally, is not supposed to move. Serves to free some memory.
}

// Pushes a new element to the end of the inner array.
//`sizeof(*val)` should normally be equal to the inner type size passed in the
// vector creation.
int push_end(Vec *vec, void *val) {
  // Checks for capacity validity and realloc in consequence
  if (!_valid_capacity(vec)) {
    __realloc(vec);
  }

  __vec_assign(vec, vec->len, val);
  vec->len++;

  return VEC_SUCCESS;
}

// Pushes an element to the head of the inner array.
//`sizeof(*val)` should normally be equal to the inner type size passed in the
// vector creation.
void push_front(Vec *vec, void *val);

// Pops the last element of the inner array.
// Returns a `void *` to the popped element.
void *pop_end(Vec *vec) {
  void *last = __vec_offset_c(vec, vec->len - 1);
  vec->len--;
  return last; // The caller should cast, respective to elt_size (same as
               // allocation functions such as malloc)
}

// Equivalent to `pop_end`, but permits reallocation when capacity is used at
// less than half.
void *pop_end_dyn(Vec *vec, void *buffer, size_t n) {
  void *last = __vec_offset_c(vec, vec->len);
  vec->len--;
  return last; // The caller should cast, respective to elt_size (same as
               // allocation functions such as malloc)
}

void *pop_front(Vec *vec);
void assign(Vec *vec);
void insert(Vec *vec, void *val, size_t idx);

// Infos
size_t len(Vec *vec) { return vec->len; }
size_t capacity(Vec *vec) { return vec->capacity; }
char is_initialised(Vec *vec) { return (vec->data == NULL) ? 0 : 1; }

// Prints regular infos about `vec`
void format(Vec *vec) {
  printf("Element byte offset: %ld\nBase pointer: %p\nLength: %ld\nCapacity: "
         "%ld\n\n",
         vec->elt_size, vec->data, vec->len, vec->capacity);
}

// Checks if the vector's capacity is still valid relative to the vector's
// length.
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

// Returns the subarray starting at `idx`
// It should normally not be indexed directly, as the vector length doesn't mean
// anything for it, unless the subarray is full. UNSAFE: do not use this
// function unless you know what you are doing: Unconscious out of bounds write
// and read operations may happen.
void *__vec_offset(Vec *vec, size_t idx) {
  return vec->data + (idx * vec->elt_size);
}

// Returns the subarray starting at `idx`.
// It should normally not be indexed directly, as the vector length doesn't mean
// anything for it, unless the subarray is full. Checks whether the index is in
// bounds (of the set array). If the furnished index is OOB, the base adress is
// returned.
// For vector indexing, use the `vec_at` wrapper.
void *__vec_offset_c(Vec *vec, size_t idx) {
  return (idx >= vec->len)
             ? vec->data
             : __vec_offset(vec, idx); // Safe call to `__vec_offset`
  // The actual call is never dangerous, the export of the returned address is.
}

// Assign the `idx` th element of the inner array.
// It takes the subarray starting at `idx` calling `__vec_offset`
// and extract its first element using the embedded element size.
// The operation is OOB-safe.
void __vec_assign(Vec *vec, size_t idx, void *element) {
  void *offset = __vec_offset_c(vec, idx);
  memcpy(offset, element, vec->elt_size);
}
// Reallocates the inner array with a doubled capacity.
void __realloc(Vec *vec) {
  __realloc_cust(vec, vec->capacity); // Capcity *= 2 (factor which permits a
                                      // good memory-using/alloc-freq balance)
}

// Reallocates the inner array with a custom add to capacity.
void __realloc_cust(Vec *vec, size_t cust) {
  vec->capacity += cust;
  void *grbg = realloc(vec->data, vec->capacity);
}

void __off_all(Vec *vec,
               size_t off) { // Budge to the right each element `off` steps
  if (vec->capacity < vec->len + off) {
    __realloc_cust(vec,
                   off); // Chance is that vec->data is not moved elsewhere?
  }

  // Budging
  for (int idx = vec->len - 1; idx >= 0; idx--) {
    __vec_assign(vec, idx + off, __vec_offset_c(vec, idx));
  }
}