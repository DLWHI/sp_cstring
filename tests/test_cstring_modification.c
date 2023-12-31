#include "sp/cstring.h"
#include "tests.h"

START_TEST(test_string_reseve) {
  sp_string* str = sp_string_create_empty();
  int len = 39;

  ck_assert_int_eq(sp_string_reserve(str, len), 0);

  ck_assert_ptr_nonnull(str);
  ck_assert_ptr_nonnull(sp_string_begin(str));
  ck_assert_ptr_nonnull(sp_string_end(str));
  ck_assert_int_eq(sp_string_end(str) - sp_string_begin(str),
                   sp_string_size(str));
  ck_assert_int_eq(sp_string_size(str), 0);
  ck_assert_int_eq(sp_string_capacity(str), len);

  sp_string_destroy(str);
}
END_TEST

START_TEST(test_string_reseve_expand) {
  sp_string* str = sp_string_create("expand");
  int oldsize = sp_string_length(str);
  int len = 39;

  ck_assert_int_eq(sp_string_reserve(str, len), 0);

  ck_assert_ptr_nonnull(str);
  ck_assert_ptr_nonnull(sp_string_begin(str));
  ck_assert_ptr_nonnull(sp_string_end(str));
  ck_assert_int_eq(sp_string_end(str) - sp_string_begin(str),
                   sp_string_size(str));
  ck_assert_int_eq(sp_string_size(str), oldsize);
  ck_assert_int_eq(sp_string_capacity(str), len);

  sp_string_destroy(str);
}
END_TEST

START_TEST(test_string_reseve_shrink) {
  sp_string* str = sp_string_create("expand");
  int oldcap = sp_string_capacity(str);
  int len = 1;

  ck_assert_int_eq(sp_string_reserve(str, len), 0);

  ck_assert_ptr_nonnull(str);
  ck_assert_ptr_nonnull(sp_string_begin(str));
  ck_assert_ptr_nonnull(sp_string_end(str));
  ck_assert_int_eq(sp_string_end(str) - sp_string_begin(str),
                   sp_string_size(str));
  ck_assert_int_eq(sp_string_size(str), oldcap - 1);
  ck_assert_int_eq(sp_string_capacity(str), oldcap);

  sp_string_destroy(str);
}
END_TEST

START_TEST(test_string_reseve_zero) {
  sp_string* str = sp_string_create("expand");
  int oldcap = sp_string_capacity(str);
  int len = 0;

  ck_assert_int_eq(sp_string_reserve(str, len), 0);

  ck_assert_ptr_nonnull(str);
  ck_assert_ptr_nonnull(sp_string_begin(str));
  ck_assert_ptr_nonnull(sp_string_end(str));
  ck_assert_int_eq(sp_string_end(str) - sp_string_begin(str),
                   sp_string_size(str));
  ck_assert_int_eq(sp_string_size(str), oldcap - 1);
  ck_assert_int_eq(sp_string_capacity(str), oldcap);

  sp_string_destroy(str);
}
END_TEST

START_TEST(test_string_reseve_neg) {
  sp_string* str = sp_string_create("expand");
  int oldcap = sp_string_capacity(str);
  int len = 1;

  ck_assert_int_eq(sp_string_reserve(str, -len), 0);

  ck_assert_ptr_nonnull(str);
  ck_assert_ptr_nonnull(sp_string_begin(str));
  ck_assert_ptr_nonnull(sp_string_end(str));
  ck_assert_int_eq(sp_string_end(str) - sp_string_begin(str),
                   sp_string_size(str));
  ck_assert_int_eq(sp_string_size(str), oldcap - 1);
  ck_assert_int_eq(sp_string_capacity(str), oldcap);

  sp_string_destroy(str);
}
END_TEST

START_TEST(test_string_shrink_to_fit) {
  sp_string* str = sp_string_create("expand");
  int oldsize = sp_string_length(str);
  int len = 100;

  sp_string_reserve(str, len);
  ck_assert_int_eq(sp_string_shrink_to_fit(str), 0);

  ck_assert_ptr_nonnull(str);
  ck_assert_ptr_nonnull(sp_string_begin(str));
  ck_assert_ptr_nonnull(sp_string_end(str));
  ck_assert_int_eq(sp_string_end(str) - sp_string_begin(str),
                   sp_string_size(str));
  ck_assert_int_eq(sp_string_size(str), oldsize);
  ck_assert_int_eq(sp_string_capacity(str), oldsize + 1);

  sp_string_destroy(str);
}
END_TEST

START_TEST(test_string_assign) {
  sp_string* str = sp_string_create_empty();
  const char* exp = "quick brown fox jumps over the lazy dog";
  int len = 39;

  ck_assert_int_eq(sp_string_assign(str, exp), 0);

  ck_assert_ptr_nonnull(str);
  ck_assert_ptr_nonnull(sp_string_begin(str));
  ck_assert_ptr_nonnull(sp_string_end(str));
  ck_assert_int_eq(sp_string_size(str), len);
  ck_assert_int_eq(sp_string_capacity(str), len + 1);

  ck_assert_str_eq(SP_CSTR(str), exp);

  sp_string_destroy(str);
}
END_TEST

START_TEST(test_string_assign_existing) {
  sp_string* str = sp_string_create("hello");
  const char* exp = "quick brown fox jumps over the lazy dog";
  int len = 39;

  ck_assert_int_eq(sp_string_assign(str, exp), 0);

  ck_assert_int_eq(sp_string_size(str), len);
  ck_assert_int_eq(sp_string_capacity(str), len + 1);

  ck_assert_str_eq(SP_CSTR(str), exp);

  sp_string_destroy(str);
}
END_TEST

START_TEST(test_string_assign_shrink) {
  sp_string* str = sp_string_create("quick brown fox jumps over the lazy dog");
  sp_size_t oldcap = sp_string_capacity(str);
  const char* exp = "hello";
  int len = 5;

  ck_assert_int_eq(sp_string_assign(str, "hello"), 0);

  ck_assert_int_eq(sp_string_size(str), len);
  ck_assert_int_eq(sp_string_capacity(str), oldcap);

  ck_assert_str_eq(SP_CSTR(str), exp);

  sp_string_destroy(str);
}
END_TEST

START_TEST(test_string_assign_empty) {
  sp_string* str = sp_string_create("quick brown fox jumps over the lazy dog");
  sp_size_t oldcap = sp_string_capacity(str);

  ck_assert_int_eq(sp_string_assign(str, ""), 0);

  ck_assert_int_eq(sp_string_size(str), 0);
  ck_assert_int_eq(sp_string_capacity(str), oldcap);

  ck_assert_str_eq(SP_CSTR(str), "");

  sp_string_destroy(str);
}
END_TEST

START_TEST(test_string_assignn) {
  sp_string* str = sp_string_create_empty();
  const char* exp = "quick brown fox jumps over the lazy dog";
  int len = 14;

  ck_assert_int_eq(sp_string_assignn(str, exp, len), 0);

  ck_assert_ptr_nonnull(str);
  ck_assert_ptr_nonnull(sp_string_begin(str));
  ck_assert_ptr_nonnull(sp_string_end(str));
  ck_assert_int_eq(sp_string_size(str), len);
  ck_assert_int_eq(sp_string_capacity(str), len + 1);

  ck_assert_int_eq(strncmp(SP_CSTR(str), exp, 14), 0);

  sp_string_destroy(str);
}
END_TEST

START_TEST(test_string_assignn_existing) {
  sp_string* str = sp_string_create("hello");
  const char* exp = "quick brown fox jumps over the lazy dog";
  int len = 14;

  ck_assert_int_eq(sp_string_assignn(str, exp, len), 0);

  ck_assert_int_eq(sp_string_size(str), len);
  ck_assert_int_eq(sp_string_capacity(str), len + 1);

  ck_assert_int_eq(strncmp(SP_CSTR(str), exp, 14), 0);

  sp_string_destroy(str);
}
END_TEST

START_TEST(test_string_assignn_self_size) {
  sp_string* str = sp_string_create("quick brown fox jumps over the lazy dog");
  int len = 5;

  ck_assert_int_eq(sp_string_assignn(str, SP_CSTR(str), len), 0);

  ck_assert_int_eq(sp_string_size(str), len);
  ck_assert_int_eq(sp_string_capacity(str), 40);

  ck_assert_int_eq(strncmp(SP_CSTR(str), "quick", len), 0);

  sp_string_destroy(str);
}
END_TEST

START_TEST(test_string_assignn_shrink) {
  sp_string* str = sp_string_create("quick brown fox jumps over the lazy dog");
  sp_size_t oldcap = sp_string_capacity(str);
  const char* exp = "hello";
  int len = 5;

  ck_assert_int_eq(sp_string_assignn(str, "hello", len), 0);

  ck_assert_int_eq(sp_string_size(str), len);
  ck_assert_int_eq(sp_string_capacity(str), oldcap);

  ck_assert_str_eq(SP_CSTR(str), exp);

  sp_string_destroy(str);
}
END_TEST

START_TEST(test_string_assignn_zero) {
  sp_string* str = sp_string_create("quick brown fox jumps over the lazy dog");
  sp_size_t oldcap = sp_string_capacity(str);

  ck_assert_int_eq(sp_string_assignn(str, "data", 0), 0);

  ck_assert_int_eq(sp_string_size(str), 0);
  ck_assert_int_eq(sp_string_capacity(str), oldcap);

  ck_assert_str_eq(SP_CSTR(str), "");

  sp_string_destroy(str);
}
END_TEST

START_TEST(test_string_assignn_neg) {
  sp_string* str = sp_string_create("quick brown fox jumps over the lazy dog");
  sp_size_t oldcap = sp_string_capacity(str);

  ck_assert_int_eq(sp_string_assignn(str, "snobism", -100), SP_ERR_INVALID);

  ck_assert_int_eq(sp_string_size(str), 39);
  ck_assert_int_eq(sp_string_capacity(str), oldcap);

  ck_assert_str_eq(SP_CSTR(str),
                   "quick brown fox jumps over the lazy dog");

  sp_string_destroy(str);
}
END_TEST

START_TEST(test_string_assigns) {
  sp_string* str = sp_string_create_empty();
  sp_string* src = sp_string_create("quick brown fox jumps over the lazy dog");

  ck_assert_int_eq(sp_string_assigns(str, src), 0);

  ck_assert_ptr_nonnull(str);
  ck_assert_ptr_nonnull(sp_string_begin(str));
  ck_assert_ptr_nonnull(sp_string_end(str));
  ck_assert_int_eq(sp_string_size(str), sp_string_size(src));

  ck_assert_str_eq(SP_CSTR(str), sp_string_c_str(src));

  sp_string_destroy(str);
  sp_string_destroy(src);
}
END_TEST

START_TEST(test_string_assigns_existing) {
  sp_string* str = sp_string_create("hello");
  sp_string* src = sp_string_create("quick brown fox jumps over the lazy dog");


  ck_assert_int_eq(sp_string_assigns(str, src), 0);

  ck_assert_int_eq(sp_string_size(str), sp_string_size(src));

  ck_assert_str_eq(SP_CSTR(str), sp_string_c_str(src));

  sp_string_destroy(str);
  sp_string_destroy(src);
}
END_TEST

START_TEST(test_string_assigns_self) {
  sp_string* str = sp_string_create("hello");

  ck_assert_int_eq(sp_string_assigns(str, str), 0);

  ck_assert_int_eq(sp_string_size(str), sp_string_size(str));

  ck_assert_str_eq(SP_CSTR(str), SP_CSTR(str));

  sp_string_destroy(str);
}
END_TEST

START_TEST(test_string_assigns_shrink) {
  sp_string* str = sp_string_create("quick brown fox jumps over the lazy dog");
  sp_size_t oldcap = sp_string_capacity(str);
  sp_string* src = sp_string_create("hello");

  ck_assert_int_eq(sp_string_assigns(str, src), 0);

  ck_assert_int_eq(sp_string_capacity(str), oldcap);
  ck_assert_int_eq(sp_string_size(str), sp_string_size(src));

  ck_assert_str_eq(SP_CSTR(str), sp_string_c_str(src));

  sp_string_destroy(str);
  sp_string_destroy(src);
}
END_TEST

START_TEST(test_string_assigns_empty) {
  sp_string* str = sp_string_create("quick brown fox jumps over the lazy dog");
  sp_size_t oldcap = sp_string_capacity(str);
  sp_string* src = sp_string_create_empty();

  ck_assert_int_eq(sp_string_assigns(str, src), 0);

  ck_assert_int_eq(sp_string_size(str), 0);
  ck_assert_int_eq(sp_string_capacity(str), oldcap);

  ck_assert_str_eq(SP_CSTR(str), "");

  sp_string_destroy(str);
  sp_string_destroy(src);
}
END_TEST

START_TEST(test_string_assign_chars) {
  sp_string* str = sp_string_create_empty();
  int len = 39;

  ck_assert_int_eq(sp_string_assign_chars(str, 'a', len), 0);

  ck_assert_ptr_nonnull(str);
  ck_assert_ptr_nonnull(sp_string_begin(str));
  ck_assert_ptr_nonnull(sp_string_end(str));
  ck_assert_int_eq(sp_string_size(str), len);
  ck_assert_int_eq(sp_string_capacity(str), len + 1);

  for (sp_size_t i = 0; i < len; ++i) {
    ck_assert_int_eq(sp_string_char_at(str, i), 'a');
  }

  sp_string_destroy(str);
}
END_TEST

START_TEST(test_string_assign_chars_existing) {
  sp_string* str = sp_string_create("quick brown fox jumps over the lazy dog");
  int len = 100;

  ck_assert_int_eq(sp_string_assign_chars(str, 'a', len), 0);

  ck_assert_int_eq(sp_string_size(str), len);
  ck_assert_int_eq(sp_string_capacity(str), len + 1);

  for (sp_size_t i = 0; i < len; ++i) {
    ck_assert_int_eq(sp_string_char_at(str, i), 'a');
  }

  sp_string_destroy(str);
}
END_TEST

START_TEST(test_string_assign_chars_shrink) {
  sp_string* str = sp_string_create("quick brown fox jumps over the lazy dog");
  sp_size_t oldcap = sp_string_capacity(str);
  int len = 1;

  ck_assert_int_eq(sp_string_assign_chars(str, 'a', len), 0);

  ck_assert_int_eq(sp_string_size(str), len);
  ck_assert_int_eq(sp_string_capacity(str), oldcap);

  for (sp_size_t i = 0; i < len; ++i) {
    ck_assert_int_eq(sp_string_char_at(str, i), 'a');
  }

  sp_string_destroy(str);
}
END_TEST

START_TEST(test_string_assign_chars_neg_count) {
  sp_string* str = sp_string_create("quick brown fox jumps over the lazy dog");
  sp_size_t oldcap = sp_string_capacity(str);

  ck_assert_int_eq(sp_string_assign_chars(str, 'a', -5), SP_ERR_INVALID);

  ck_assert_int_eq(sp_string_size(str), 39);
  ck_assert_int_eq(sp_string_capacity(str), oldcap);

  ck_assert_str_eq(SP_CSTR(str),
                   "quick brown fox jumps over the lazy dog");

  sp_string_destroy(str);
}
END_TEST

START_TEST(test_string_assign_chars_zero) {
  sp_string* str = sp_string_create("quick brown fox jumps over the lazy dog");
  sp_size_t oldcap = sp_string_capacity(str);

  ck_assert_int_eq(sp_string_assign_chars(str, 'a', 0), 0);

  ck_assert_int_eq(sp_string_size(str), 0);
  ck_assert_int_eq(sp_string_capacity(str), oldcap);

  ck_assert_str_eq(SP_CSTR(str), "");

  sp_string_destroy(str);
}
END_TEST

START_TEST(test_string_assign_chars_null_term) {
  sp_string* str = sp_string_create("quick brown fox jumps over the lazy dog");
  sp_size_t oldcap = sp_string_capacity(str);
  int len = 14134;

  ck_assert_int_eq(sp_string_assign_chars(str, '\0', len), 0);

  ck_assert_int_eq(sp_string_size(str), 0);
  ck_assert_int_eq(sp_string_capacity(str), oldcap);

  ck_assert_str_eq(SP_CSTR(str), "");

  sp_string_destroy(str);
}
END_TEST

START_TEST(test_string_assign_chars_eof) {
  sp_string* str = sp_string_create("quick brown fox jumps over the lazy dog");
  int len = 141;

  ck_assert_int_eq(sp_string_assign_chars(str, -1, len), 0);

  ck_assert_int_eq(sp_string_size(str), len);
  ck_assert_int_eq(sp_string_capacity(str), len + 1);

  for (sp_size_t i = 0; i < len; ++i) {
    ck_assert_int_eq(sp_string_char_at(str, i), -1);
  }

  sp_string_destroy(str);
}
END_TEST

START_TEST(test_string_assign_range) {
  sp_string* str = sp_string_create_empty();
  const char* range = "quick brown fox jumps over the lazy dog";
  int len = 11;

  ck_assert_int_eq(sp_string_assign_range(str, range, range + len), 0);

  ck_assert_ptr_nonnull(str);
  ck_assert_ptr_nonnull(sp_string_begin(str));
  ck_assert_ptr_nonnull(sp_string_end(str));
  ck_assert_int_eq(sp_string_size(str), len);
  ck_assert_int_eq(sp_string_capacity(str), len + 1);

  ck_assert_int_eq(strncmp(SP_CSTR(str), range, len), 0);

  sp_string_destroy(str);
}
END_TEST

START_TEST(test_string_assign_range_existing) {
  sp_string* str = sp_string_create("hello");
  const char* exp = "quick brown fox jumps over the lazy dog";
  int len = 11;

  ck_assert_int_eq(sp_string_assign_range(str, exp, exp + len), 0);

  ck_assert_int_eq(sp_string_size(str), len);
  ck_assert_int_eq(sp_string_capacity(str), len + 1);

  ck_assert_int_eq(strncmp(SP_CSTR(str), exp, len), 0);

  sp_string_destroy(str);
}
END_TEST

START_TEST(test_string_assign_range_self_size) {
  sp_string* str = sp_string_create("quick brown fox jumps over the lazy dog");
  int len = 5;

  ck_assert_int_eq(sp_string_assign_range(str, SP_CSTR(str), SP_CSTR(str) + len), 0);

  ck_assert_int_eq(sp_string_size(str), len);
  ck_assert_int_eq(sp_string_capacity(str), 40);

  ck_assert_int_eq(strncmp(SP_CSTR(str), "quick", len), 0);

  sp_string_destroy(str);
}
END_TEST

START_TEST(test_string_assign_range_self) {
  sp_string* str = sp_string_create("quick brown fox jumps over the lazy dog");

  ck_assert_int_eq(sp_string_assign_range(str, SP_CSTR(str), SP_CSTR(str) + SP_STRLEN(str)), 0);

  ck_assert_int_eq(sp_string_size(str), SP_STRLEN(str));
  ck_assert_int_eq(sp_string_capacity(str), 40);

  ck_assert_int_eq(strncmp(SP_CSTR(str), SP_CSTR(str), SP_STRLEN(str)), 0);

  sp_string_destroy(str);
}
END_TEST

START_TEST(test_string_assign_range_shrink) {
  sp_string* str = sp_string_create("quick brown fox jumps over the lazy dog");
  sp_size_t oldcap = sp_string_capacity(str);
  const char* exp = "hello";
  int len = 5;

  ck_assert_int_eq(sp_string_assign_range(str, exp, exp + len), 0);

  ck_assert_int_eq(sp_string_size(str), len);
  ck_assert_int_eq(sp_string_capacity(str), oldcap);

  ck_assert_str_eq(SP_CSTR(str), exp);

  sp_string_destroy(str);
}
END_TEST

START_TEST(test_string_assign_range_empty) {
  sp_string* str = sp_string_create("quick brown fox jumps over the lazy dog");
  sp_size_t oldcap = sp_string_capacity(str);
  const char* range = "range";

  ck_assert_int_eq(sp_string_assign_range(str, range, range), 0);

  ck_assert_int_eq(sp_string_size(str), 0);
  ck_assert_int_eq(sp_string_capacity(str), oldcap);

  ck_assert_str_eq(SP_CSTR(str), "");

  sp_string_destroy(str);
}
END_TEST

START_TEST(test_string_assign_range_invalid) {
  sp_string* str = sp_string_create("quick brown fox jumps over the lazy dog");
  sp_size_t oldcap = sp_string_capacity(str);
  const char* range = "range";

  ck_assert_int_eq(sp_string_assign_range(str, range + 2, range), SP_ERR_INVALID);

  ck_assert_int_eq(sp_string_size(str), 39);
  ck_assert_int_eq(sp_string_capacity(str), oldcap);

  ck_assert_str_eq(SP_CSTR(str),
                   "quick brown fox jumps over the lazy dog");

  sp_string_destroy(str);
}
END_TEST

Suite* modification_suite() {
  Suite* suite = suite_create("\033[34mcapacity functions\033[0m");
  TCase* reserve = tcase_create("tcase_reserve");

  tcase_add_test(reserve, test_string_reseve);
  tcase_add_test(reserve, test_string_reseve_expand);
  tcase_add_test(reserve, test_string_reseve_shrink);
  tcase_add_test(reserve, test_string_reseve_neg);
  tcase_add_test(reserve, test_string_reseve_zero);

  TCase* stf = tcase_create("tcase_shrink_to_fit");

  tcase_add_test(stf, test_string_shrink_to_fit);

  TCase* assign = tcase_create("tcase_assign");

  tcase_add_test(assign, test_string_assign);
  tcase_add_test(assign, test_string_assign_shrink);
  tcase_add_test(assign, test_string_assign_existing);
  tcase_add_test(assign, test_string_assign_empty);
  tcase_add_test(assign, test_string_assignn);
  tcase_add_test(assign, test_string_assignn_existing);
  tcase_add_test(assign, test_string_assignn_shrink);
  tcase_add_test(assign, test_string_assignn_zero);
  tcase_add_test(assign, test_string_assignn_neg);
  tcase_add_test(assign, test_string_assignn_self_size);
  tcase_add_test(assign, test_string_assigns);
  tcase_add_test(assign, test_string_assigns_shrink);
  tcase_add_test(assign, test_string_assigns_existing);
  tcase_add_test(assign, test_string_assigns_empty);
  tcase_add_test(assign, test_string_assigns_self);

  TCase* assign_range = tcase_create("tcase_assign_range");
  tcase_add_test(assign_range, test_string_assign_range);
  tcase_add_test(assign_range, test_string_assign_range_existing);
  tcase_add_test(assign_range, test_string_assign_range_shrink);
  tcase_add_test(assign_range, test_string_assign_range_self);
  tcase_add_test(assign_range, test_string_assign_range_self_size);
  tcase_add_test(assign_range, test_string_assign_range_empty);
  tcase_add_test(assign_range, test_string_assign_range_invalid);


  TCase* assign_chars = tcase_create("tcase_assign_chars");
  tcase_add_test(assign_chars, test_string_assign_chars);
  tcase_add_test(assign_chars, test_string_assign_chars_existing);
  tcase_add_test(assign_chars, test_string_assign_chars_shrink);
  tcase_add_test(assign_chars, test_string_assign_chars_neg_count);
  tcase_add_test(assign_chars, test_string_assign_chars_zero);
  tcase_add_test(assign_chars, test_string_assign_chars_null_term);
  tcase_add_test(assign_chars, test_string_assign_chars_eof);

  suite_add_tcase(suite, reserve);
  suite_add_tcase(suite, stf);
  suite_add_tcase(suite, assign);
  suite_add_tcase(suite, assign_range);
  suite_add_tcase(suite, assign_chars);
  return suite;
}
