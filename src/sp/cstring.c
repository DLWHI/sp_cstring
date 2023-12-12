#include "cstring.h"

#include <stdlib.h>
#include <string.h>

#define THROW_CHECK(code, deleter) \
  if (code) {                      \
    deleter;                       \
    return code;                   \
  } else

#define ALLOC_CHECK(ptr, rt, deleter) \
  if (!ptr) {                         \
    deleter;                          \
    return rt;                        \
  } else

typedef struct sp_string {
  char* ptr;
  sp_size_t len;
  sp_size_t cap;
} sp_string;

//==============================================================================

static int sp_conditional_resize(sp_string* str, sp_size_t req) {
  if (str->cap < req) {
    sp_size_t n_cap = (str->cap * 2 > req) ? str->cap * 2 : req;
    THROW_CHECK(sp_string_reserve(str, n_cap), ) {}
  }
  return 0;
}

//==============================================================================

sp_string* sp_string_create(const char* value) {
  if (!value) {
    return NULL;
  } else if (!*value) {
    return sp_string_create_empty();
  }
  sp_size_t count = (sp_size_t)strlen(value) + 1;
  sp_string* str = malloc(sizeof(*str));
  ALLOC_CHECK(str, NULL, ) {
    str->ptr = malloc(count);
    ALLOC_CHECK(str->ptr, NULL, free(str)) {
      str->len = 0;
      str->cap = count;
      for (; *value; ++str->len, ++value) {
        str->ptr[str->len] = *value;
      }
      str->ptr[str->len] = '\0';
    }
  }
  return str;
}

sp_string* sp_string_create_empty() {
  sp_string* str = malloc(sizeof(*str));
  if (str) {
    str->ptr = NULL;
    str->len = 0;
    str->cap = 0;
  }
  return str;
}

sp_string* sp_string_create_chars(char val, sp_size_t count) {
  if (count < 0) {
    return NULL;
  } else if (!count || !val) {
    return sp_string_create_empty();
  }
  sp_string* str = malloc(sizeof(*str));
  ALLOC_CHECK(str, NULL, ) {
    str->ptr = malloc(count + 1);
    ALLOC_CHECK(str->ptr, NULL, free(str)) {
      str->cap = count + 1;
      for (str->len = 0; str->len < count; ++str->len) {
        str->ptr[str->len] = val;
      }
      str->ptr[str->len] = '\0';
    }
  }
  return str;
}

sp_string* sp_string_copy(const sp_string* other) {
  return sp_string_create(other->ptr);
}

sp_string* sp_string_move(sp_string* other) {
  if (!other) {
    return NULL;
  }
  sp_string* str = malloc(sizeof(*str));
  ALLOC_CHECK(str, NULL, ) {
    str->ptr = other->ptr;
    str->cap = other->cap;
    str->len = other->len;
    other->ptr = NULL;
    other->cap = 0;
    other->len = 0;
  }
  return str;
}

sp_string* sp_string_destroy(sp_string* str) {
  free(str->ptr);
  free(str);
  return NULL;
}

//==============================================================================

char* sp_string_begin(sp_string* str) { return str->ptr; }
const char* sp_string_cbegin(const sp_string* str) { return str->ptr; }

char* sp_string_end(sp_string* str) { return str->ptr + str->len; }
const char* sp_string_cend(const sp_string* str) { return str->ptr + str->len; }

char sp_string_char_at(const sp_string* str, sp_size_t pos) {
  return (0 <= pos && pos < str->len) ? str->ptr[pos] : '\0';
}

const char* sp_string_c_str(const sp_string* str) { return str->ptr; }

sp_size_t sp_string_length(const sp_string* str) { return str->len; }

sp_size_t sp_string_size(const sp_string* str) { return str->len; }

sp_size_t sp_string_capacity(const sp_string* str) { return str->cap; }

//==============================================================================

int sp_string_assign(sp_string* str, const char* value) {
  if (!value) {
    return SP_ERR_INVALID;
  }
  sp_size_t count =(sp_size_t)strlen(value);
  int code = sp_conditional_resize(str, count + 1);
  THROW_CHECK(code, ){};
  str->len = 0;
  memcpy(str->ptr, value, count);
  str->len = count;
  str->ptr[str->len] = '\0';
  return 0;
}

int sp_string_assign_chars(sp_string* str, char val, sp_size_t count) {
  if (val < 0 || count < 0) {
    return SP_ERR_INVALID;
  } else if (!val || !count) {
    if (str->cap) {
      str->ptr[0] = '\0';
      str->len = 0;
    }
    return 0;
  }
  int code = sp_conditional_resize(str, count + 1);
  THROW_CHECK(code, ){};
  memset(str->ptr, val, count);
  str->len = count;
  str->ptr[count] = '\0';
  return 0;
}

int sp_string_reserve(sp_string* str, sp_size_t newsize) {
  if (str->cap < newsize) {
    char* ptr = realloc(str->ptr, newsize);
    ALLOC_CHECK(ptr, SP_ERR_BAD_ALLOC, ) {
      if (!str->len) {
        str->ptr = '\0';
      }
      str->ptr = ptr;
      str->cap = newsize;
    }
  }
  return 0;
}

int sp_string_shrink_to_fit(sp_string* str) {
  if (str->cap > str->len + 1) {
    char* ptr = realloc(str->ptr, str->len + 1);
    ALLOC_CHECK(ptr, SP_ERR_BAD_ALLOC, ) {
      str->ptr = ptr;
      str->cap = str->len + 1;
    }
  }
  return 0;
}

//==============================================================================

int sp_string_concat(sp_string* str, const char* source) {
  if (!source) {
    return SP_ERR_INVALID;
  } else if (!*source) {
    return 0;
  }
  sp_size_t count = (sp_size_t)strlen(source);
  int code =
      sp_conditional_resize(str, str->len + count + 1);
  THROW_CHECK(code, ){};
  memcpy(str->ptr + str->len, source, count);
  str->len += count;
  str->ptr[str->len] = '\0';
  return 0;
}

int sp_string_concat_string(sp_string* str, const sp_string* other) {
  if (!other) {
    return SP_ERR_INVALID;
  } else if (!other->len) {
    return 0;
  }
  int code = sp_conditional_resize(str, str->len + other->len + 1);
  THROW_CHECK(code, ){};
  memcpy(str->ptr + str->len, other->ptr, other->len);
  str->len += other->len;
  str->ptr[str->len] = '\0';
  return 0;
}

int sp_string_concat_chars(sp_string* str, char val, sp_size_t count) {
  if (count < 0) {
    return SP_ERR_INVALID;
  } else if (!val || !count) {
    return 0;
  }
  int code = sp_conditional_resize(str, str->len + count + 1);
  THROW_CHECK(code, ){};
  memset(str->ptr + str->len, val, count);
  str->len += count;
  str->ptr[str->len] = '\0';
  return 0;
}

int sp_string_backspace(sp_string* str) {
  if (str->len) {
    str->ptr[str->len] = '\0';
    --str->len;
    return 0;
  }
  return SP_ERR_INVALID;
}

void sp_string_push_back(sp_string* str, char val) {
  sp_conditional_resize(str, str->cap + 1);
  str->ptr[str->len++] = val;
  str->ptr[str->len] = '\0';
}

void sp_string_pop_back(sp_string* str) {
  str->ptr[str->len] = '\0';
  --str->len;
}

int sp_string_insert(sp_string* str, sp_size_t pos, const char* source) {
  if (!source || pos < 0 || pos >= str->len) {
    return SP_ERR_INVALID;
  } else if (!*source) {
    return 0;
  }
  sp_size_t count = (sp_size_t)strlen(source);
  int code = sp_conditional_resize(str, str->len + count + 1);
  THROW_CHECK(code, ){};
  memmove(str->ptr + pos + count, str->ptr + pos, count);
  memcpy(str->ptr + pos, source, count);
  str->ptr[str->len] = '\0';
  return 0;
}

int sp_string_insert_string(sp_string* str, sp_size_t pos,
                            const sp_string* other) {
  if (!other || pos < 0 || pos >= str->len) {
    return SP_ERR_INVALID;
  } else if (!other->len) {
    return 0;
  }
  int code = sp_conditional_resize(str, str->len + other->len + 1);
  THROW_CHECK(code, ){};
  memmove(str->ptr + pos + other->len, str->ptr + pos, other->len);
  memcpy(str->ptr + pos, other->ptr, other->len);
  str->ptr[str->len] = '\0';
  return 0;
}

int sp_string_insert_chars(sp_string* str, sp_size_t pos, char val,
                           sp_size_t count) {
  if (count < 0 || pos < 0 || pos >= str->len) {
    return SP_ERR_INVALID;
  } else if (!count || !val) {
    return 0;
  }
  int code = sp_conditional_resize(str, str->len + count + 1);
  THROW_CHECK(code, ){};
  memmove(str->ptr + pos + count, str->ptr + pos, count);
  memset(str->ptr + pos, val, count);
  str->ptr[str->len] = '\0';
  return 0;
}

int sp_string_erase(sp_string* str, sp_size_t pos, sp_size_t count) {
  if (pos < 0 || pos >= str->len || count < 0) {
    return SP_ERR_INVALID;
  } else if (!count) {
    return 0;
  }
  memmove(str->ptr + pos, str->ptr + pos + count, count);
  str->len -= count;
  str->ptr[str->len] = '\0';
  return 0;
}

int sp_string_erase_range(sp_string* str, char* first, char* last) {
  if (first > last || str->ptr > first || (str->ptr + str->len) < last) {
    return SP_ERR_INVALID;
  } else if (first == last) {
    return 0;
  }
  memmove(first, last, last - first);
  str->len -= (sp_size_t)(last - first);
  str->ptr[str->len] = '\0';
  return 0;
}

//==============================================================================