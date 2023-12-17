#ifndef SP_CSTRING_CSTRING_H_
#define SP_CSTRING_CSTRING_H_

typedef long sp_size_t;

typedef struct sp_string sp_string;

#define SP_LENGTH(x) sp_string_length(x)

#define SP_ERR_INVALID -1
#define SP_ERR_BAD_ALLOC -2

sp_string* sp_string_create_empty();
sp_string* sp_string_create(const char* value);
sp_string* sp_string_createn(const char* value, sp_size_t count);
sp_string* sp_string_create_chars(char val, sp_size_t count);
sp_string* sp_string_copy(const sp_string* other);
sp_string* sp_string_move(sp_string* other);
int sp_string_swap(sp_string* lhs, sp_string* rhs);
sp_string* sp_string_destroy(sp_string* str);

//==============================================================================

char* sp_string_begin(sp_string* str);
const char* sp_string_cbegin(const sp_string* str);

char* sp_string_end(sp_string* str);
const char* sp_string_cend(const sp_string* str);

char sp_string_char_at(const sp_string* str, sp_size_t pos);

char sp_string_front(const sp_string* str);
char sp_string_back(const sp_string* str);

sp_size_t sp_string_length(const sp_string* str);

sp_size_t sp_string_size(const sp_string* str);

sp_size_t sp_string_capacity(const sp_string* str);

const char* sp_string_c_str(const sp_string* str);

//==============================================================================

int sp_string_assign(sp_string* str, const char* value);
int sp_string_assignn(sp_string* str, const char* value, sp_size_t count);
int sp_string_assign_range(sp_string* str, const char* first, const char* last);
int sp_string_assign_chars(sp_string* str, char val, sp_size_t count);
int sp_string_reserve(sp_string* str, sp_size_t newsize);
int sp_string_shrink_to_fit(sp_string* str);

//==============================================================================

int sp_string_concat(sp_string* str, const char* source);
int sp_string_concatn(sp_string* str, const char* source, sp_size_t count);
int sp_string_concats(sp_string* str, const sp_string* other);
int sp_string_append(sp_string* str, char val, sp_size_t count);

int sp_string_insert(sp_string* str, sp_size_t pos, const char* source);
int sp_string_insertn(sp_string* str, sp_size_t pos, const char* source, sp_size_t count);
int sp_string_inserts(sp_string* str, sp_size_t pos, const sp_string* other);
int sp_string_insertc(sp_string* str, sp_size_t pos, char val, sp_size_t count);

char* sp_string_inserti(sp_string* str, const char* it, const char* source);
char* sp_string_insertni(sp_string* str, const char* it, const char* source, sp_size_t count);
char* sp_string_insertsi(sp_string* str, const char* it, const sp_string* other);
char* sp_string_insertci(sp_string* str, const char* it, char val, sp_size_t count);

int sp_string_insert_range(sp_string* str, sp_size_t pos, const char* first, const char* last);
char* sp_string_inserti_range(sp_string* str, const char* it, const char* first, const char* last);

int sp_string_erase(sp_string* str, sp_size_t pos, sp_size_t count);
char* sp_string_erasei(sp_string* str, char* it, sp_size_t count);
char* sp_string_erase_range(sp_string* str, char* first, char* last);

//==============================================================================

int sp_string_backspace(sp_string* str);

void sp_string_push_back(sp_string* str, char val);

void sp_string_pop_back(sp_string* str);

#endif  // SP_CSTRING_STRING_H_
