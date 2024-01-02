#include "cstring.h"

#include <stdlib.h>
#include <string.h>

#define THROW_CHECK(code, rt, deleter) \
  if (code < 0) {                      \
    deleter;                           \
    return rt;                         \
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
    int code = sp_string_reserve(str, n_cap);
    THROW_CHECK(code, code, ) {}
  }
  return 0;
}

//==============================================================================

sp_string* sp_string_create(const char* value) {
  return sp_string_createn(value, (sp_size_t)strlen(value));
}

sp_string* sp_string_createn(const char* value, sp_size_t count) {
  if (count < 0) {
    return NULL;
  } else if (!count) {
    return sp_string_create_empty();
  }
  sp_string* str = malloc(sizeof(*str));
  ALLOC_CHECK(str, NULL, ) {
    str->ptr = malloc(count + 1);
    ALLOC_CHECK(str->ptr, NULL, free(str)) {
      str->len = 0;
      str->cap = count + 1;
      for (; count; ++str->len, ++value, --count) {
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
  if (!other->len) {
    return sp_string_create_empty();
  }
  return sp_string_create(other->ptr);
}

sp_string* sp_string_move(sp_string* other) {
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

int sp_string_swap(sp_string* lhs, sp_string* rhs) {
  if (lhs == rhs) {
    return 0;
  }
  sp_string temp = *lhs;
  *lhs = *rhs;
  *rhs = temp;
  return 0;
}

sp_string* sp_string_destroy(sp_string* str) {
  if (str) {
    free(str->ptr);
  }
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

char sp_string_front(const sp_string* str) { return *str->ptr; }

char sp_string_back(const sp_string* str) { return *(str->ptr + str->len - 1); }

const char* sp_string_c_str(const sp_string* str) { return str->ptr; }

sp_size_t sp_string_length(const sp_string* str) { return str->len; }

sp_size_t sp_string_size(const sp_string* str) { return str->len; }

sp_size_t sp_string_capacity(const sp_string* str) { return str->cap; }

//==============================================================================

int sp_string_assign(sp_string* str, const char* value) {
  if (!value) {
    return SP_ERR_INVALID;
  }
  return sp_string_assignn(str, value, (sp_size_t)strlen(value));
}

int sp_string_assignn(sp_string* str, const char* value, sp_size_t count) {
  if (count < 0) {
    return SP_ERR_INVALID;
  } else if (str->ptr == value && str->len == count) {
    return 0;
  }
  if (str->cap < count + 1) {
    sp_size_t n_cap = (str->cap * 2 > count + 1) ? str->cap * 2 : count + 1;
    char* buf = malloc(n_cap);
    ALLOC_CHECK(buf, SP_ERR_BAD_ALLOC, ) {
      memcpy(buf, value, count);
      str->cap = count + 1;
      free(str->ptr);
      str->ptr = buf;
    }
  } else {
    memcpy(str->ptr, value, count);
  }
  str->len = count;
  str->ptr[str->len] = '\0';
  return 0;
}

int sp_string_assigns(sp_string* str, sp_string* value) {
  if (!value) {
    return SP_ERR_INVALID;
  } else if (!value->len) {
    return sp_string_assignn(str, "", 0);
  }
  return sp_string_assignn(str, value->ptr, value->len);
}

int sp_string_assign_range(sp_string* str, const char* first,
                           const char* last) {
  if (!last) {
    return SP_ERR_INVALID;
  }
  return sp_string_assignn(str, first, (sp_size_t)(last - first));
}

int sp_string_assign_chars(sp_string* str, char val, sp_size_t count) {
  if (count < 0) {
    return SP_ERR_INVALID;
  } else if (!val || !count) {
    if (str->cap) {
      str->ptr[0] = '\0';
      str->len = 0;
    }
    return 0;
  }
  int code = sp_conditional_resize(str, count + 1);
  THROW_CHECK(code, code, ){};
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
        *str->ptr = '\0';
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
  }
  return sp_string_concatn(str, source, (sp_size_t)strlen(source));
}

int sp_string_concatn(sp_string* str, const char* source, sp_size_t count) {
  if (count < 0) {
    return SP_ERR_INVALID;
  } else if (!count) {
    return 0;
  }
  if (str->cap < str->len + count + 1) {
    sp_size_t n_cap = (str->cap * 2 > str->len + count + 1)
                          ? str->cap * 2
                          : str->len + count + 1;
    char* buf = malloc(n_cap);
    ALLOC_CHECK(buf, SP_ERR_BAD_ALLOC, ) {
      memcpy(buf, str->ptr, str->len);
      memcpy(buf + str->len, source, count);
      str->cap = count + 1;
      free(str->ptr);
      str->ptr = buf;
    }
  } else {
    memcpy(str->ptr + str->len, source, count);
  }
  str->len += count;
  str->ptr[str->len] = '\0';
  return 0;
}

int sp_string_concats(sp_string* str, const sp_string* other) {
  if (!other->len) {
    return 0;
  }
  return sp_string_concatn(str, other->ptr, other->len);
}

int sp_string_concat_range(sp_string* str, const char* first,
                           const char* last) {
  if (!last) {
    return SP_ERR_INVALID;
  }
  return sp_string_concatn(str, first, (sp_size_t)(last - first));
}

int sp_string_append(sp_string* str, char val, sp_size_t count) {
  if (count < 0) {
    return SP_ERR_INVALID;
  } else if (!val || !count) {
    return 0;
  }
  int code = sp_conditional_resize(str, str->len + count + 1);
  THROW_CHECK(code, code, ){};
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
  if (!source) {
    return SP_ERR_INVALID;
  }
  return sp_string_insertn(str, pos, source, (sp_size_t)strlen(source));
}

int sp_string_insertn(sp_string* str, sp_size_t pos, const char* source,
                      sp_size_t count) {
  if (count < 0 || pos < 0 || pos > str->len) {
    return SP_ERR_INVALID;
  } else if (!count) {
    return pos;
  }
  if (str->cap < str->len + count + 1) {
    sp_size_t n_cap = (str->cap * 2 > str->len + count + 1)
                          ? str->cap * 2
                          : str->len + count + 1;
    char* buf = malloc(n_cap);
    ALLOC_CHECK(buf, SP_ERR_BAD_ALLOC, ) {
      memcpy(buf, str->ptr, pos);
      memcpy(buf + pos + count, str->ptr + pos, str->len - pos);
      memcpy(buf + pos, source, count);
      str->cap = count + 1;
      free(str->ptr);
      str->ptr = buf;
    }
  } else {
    memmove(str->ptr + pos + count, str->ptr + pos, str->len - pos);
    memcpy(str->ptr + pos, source, count);
  }
  str->len += count;
  str->ptr[str->len] = '\0';
  return pos;
}

int sp_string_inserts(sp_string* str, sp_size_t pos, const sp_string* other) {
  if (!other->len) {
    return pos;
  }
  return sp_string_insertn(str, pos, other->ptr, other->len);
}

int sp_string_insert_chars(sp_string* str, sp_size_t pos, char val,
                           sp_size_t count) {
  if (count < 0 || pos < 0 || pos > str->len) {
    return SP_ERR_INVALID;
  } else if (!count) {
    return pos;
  } else if (!val) {
    str->ptr[pos] = val;
    return pos;
  }
  int code = sp_conditional_resize(str, str->len + count + 1);
  THROW_CHECK(code, code, ){};
  memmove(str->ptr + pos + count, str->ptr + pos, str->len - pos);
  memset(str->ptr + pos, val, count);
  str->len += count;
  str->ptr[str->len] = '\0';
  return pos;
}

char* sp_string_inserti(sp_string* str, const char* it, const char* source) {
  if (!source) {
    return NULL;
  }
  return sp_string_insertni(str, it, source, (sp_size_t)strlen(source));
}

char* sp_string_insertni(sp_string* str, const char* it, const char* source,
                         sp_size_t count) {
  sp_size_t ind =
      sp_string_insertn(str, (sp_size_t)(it - str->ptr), source, count);
  THROW_CHECK(ind, NULL, ) { return str->ptr + ind; }
}

char* sp_string_insertsi(sp_string* str, const char* it,
                         const sp_string* other) {
  sp_size_t ind = sp_string_inserts(str, (sp_size_t)(it - str->ptr), other);
  THROW_CHECK(ind, NULL, ) { return str->ptr + ind; }
}

char* sp_string_inserti_chars(sp_string* str, const char* it, char val,
                              sp_size_t count) {
  sp_size_t ind =
      sp_string_insert_chars(str, (sp_size_t)(it - str->ptr), val, count);
  THROW_CHECK(ind, NULL, ) { return str->ptr + ind; }
}

int sp_string_insert_range(sp_string* str, sp_size_t pos, const char* first,
                           const char* last) {
  return sp_string_insertn(str, pos, first, (sp_size_t)(last - first));
}

char* sp_string_inserti_range(sp_string* str, const char* it, const char* first,
                              const char* last) {
  sp_size_t ind = sp_string_insertn(str, (sp_size_t)(it - str->ptr), first,
                                    (sp_size_t)(last - first));
  THROW_CHECK(ind, NULL, ) { return str->ptr + ind; }
}

int sp_string_erase(sp_string* str, sp_size_t pos, sp_size_t count) {
  if (count < 0 || pos < 0 || pos + count > str->len) {
    return SP_ERR_INVALID;
  } else if (!count) {
    return 0;
  }
  memmove(str->ptr + pos, str->ptr + pos + count, str->len - pos - count);
  str->len -= count;
  str->ptr[str->len] = '\0';
  return 0;
}

char* sp_string_erasei(sp_string* str, char* it, sp_size_t count) {
  sp_size_t ind = sp_string_erase(str, (sp_size_t)(it - str->ptr), count);
  THROW_CHECK(ind, NULL, ) { return str->ptr + ind; }
}

char* sp_string_erase_range(sp_string* str, char* first, char* last) {
  return sp_string_erasei(str, first, (sp_size_t)(last - first));
}

void sp_string_to_lower(sp_string* str) {
  for (sp_size_t i = 0; i < str->len; ++i) {
    if ('A' <= str->ptr[i] && str->ptr[i] < 'Z') {
      str->ptr[i] += 32;
    }
  }
}

void sp_string_to_upper(sp_string* str) {
  for (sp_size_t i = 0; i < str->len; ++i) {
    if ('a' <= str->ptr[i] && str->ptr[i] < 'z') {
      str->ptr[i] -= 32;
    }
  }
}

void sp_string_trim(sp_string* str, const char* charset) {
  sp_string_trim_left(str, charset);
  sp_string_trim_right(str, charset);
}

void sp_string_trim_left(sp_string* str, const char* charset) {
  sp_size_t i = 0;
  for (; i < str->len && !strchr(charset, str->ptr[i]); ++i) {
  }
  memmove(str->ptr, str->ptr + i, i);
}

void sp_string_trim_right(sp_string* str, const char* charset) {
  sp_size_t i = str->len;
  for (; i && !strchr(charset, str->ptr[i - 1]); --i) {
  }
  memmove(str->ptr, str->ptr + i - 1, i - 1);
}
