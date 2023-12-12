#include <check.h>
#include <stdio.h>

#include "sp/cstring.h"

START_TEST(test_string_init_zero) {
  sp_string* str = sp_string_create_empty();

  ck_assert_ptr_nonnull(str);
  ck_assert_ptr_null(sp_string_begin(str));
  ck_assert_ptr_null(sp_string_end(str));
  ck_assert_ptr_eq(sp_string_begin(str), sp_string_end(str));

  sp_string_destroy(str);
}
END_TEST

START_TEST(test_string_init_chars) {
  int len = 10;
  sp_string* str = sp_string_create_chars('a', len);

  ck_assert_ptr_nonnull(str);
  ck_assert_ptr_nonnull(sp_string_cbegin(str));
  ck_assert_ptr_nonnull(sp_string_cend(str));
  ck_assert_int_eq(sp_string_size(str), len);
  ck_assert_int_eq(sp_string_capacity(str), len + 1);

  for (sp_size_t i = 0; i < len; ++i) {
    ck_assert_int_eq(sp_string_char_at(str, i), 'a');
  }

  sp_string_destroy(str);
}
END_TEST

START_TEST(test_string_init_chars_zero) {
  sp_string* str = sp_string_create_chars('a', 0);

  ck_assert_ptr_nonnull(str);
  ck_assert_ptr_null(sp_string_begin(str));
  ck_assert_ptr_null(sp_string_end(str));
  ck_assert_int_eq(sp_string_end(str) - sp_string_begin(str),
                   sp_string_size(str));
  ck_assert_int_eq(sp_string_size(str), 0);
  ck_assert_int_eq(sp_string_capacity(str), 0);

  sp_string_destroy(str);
}
END_TEST

START_TEST(test_string_init_chars_null_term) {
  sp_string* str = sp_string_create_chars('\0', 2147000);

  ck_assert_ptr_nonnull(str);
  ck_assert_ptr_null(sp_string_begin(str));
  ck_assert_ptr_null(sp_string_end(str));
  ck_assert_int_eq(sp_string_end(str) - sp_string_begin(str),
                   sp_string_size(str));
  ck_assert_int_eq(sp_string_size(str), 0);
  ck_assert_int_eq(sp_string_capacity(str), 0);

  sp_string_destroy(str);
}
END_TEST

START_TEST(test_string_init_static) {
  sp_string* str = sp_string_create("quick brown fox jumps over the lazy dog");
  const char* exp = "quick brown fox jumps over the lazy dog";
  int len = 39;

  ck_assert_ptr_nonnull(str);
  ck_assert_ptr_nonnull(sp_string_begin(str));
  ck_assert_ptr_nonnull(sp_string_end(str));
  ck_assert_int_eq(sp_string_end(str) - sp_string_begin(str),
                   sp_string_size(str));
  ck_assert_int_eq(sp_string_size(str), len);
  ck_assert_int_eq(sp_string_capacity(str), len + 1);

  ck_assert_str_eq(sp_string_c_str(str), exp);

  for (sp_size_t i = 0; i < len; ++i) {
    ck_assert_int_eq(sp_string_char_at(str, i), exp[i]);
  }

  sp_string_destroy(str);
}
END_TEST

START_TEST(test_string_init_static_empty) {
  sp_string* str = sp_string_create("");

  ck_assert_ptr_nonnull(str);
  ck_assert_ptr_null(sp_string_begin(str));
  ck_assert_ptr_null(sp_string_end(str));
  ck_assert_int_eq(sp_string_end(str) - sp_string_begin(str),
                   sp_string_size(str));
  ck_assert_int_eq(sp_string_size(str), 0);
  ck_assert_int_eq(sp_string_capacity(str), 0);

  sp_string_destroy(str);
}
END_TEST

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

  ck_assert_str_eq(sp_string_c_str(str), exp);

  sp_string_destroy(str);
}
END_TEST

START_TEST(test_string_assign_existing) {
  sp_string* str = sp_string_create_empty("hello");
  const char* exp = "quick brown fox jumps over the lazy dog";
  int len = 39;

  ck_assert_int_eq(sp_string_assign(str, exp), 0);

  ck_assert_int_eq(sp_string_size(str), len);
  ck_assert_int_eq(sp_string_capacity(str), len + 1);

  ck_assert_str_eq(sp_string_c_str(str), exp);

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

  ck_assert_str_eq(sp_string_c_str(str), exp);

  sp_string_destroy(str);
}
END_TEST

START_TEST(test_string_assign_empty) {
  sp_string* str = sp_string_create("quick brown fox jumps over the lazy dog");
  sp_size_t oldcap = sp_string_capacity(str);

  ck_assert_int_eq(sp_string_assign(str, ""), 0);

  ck_assert_int_eq(sp_string_size(str), 0);
  ck_assert_int_eq(sp_string_capacity(str), oldcap);

  ck_assert_str_eq(sp_string_c_str(str), "");

  sp_string_destroy(str);
}
END_TEST

START_TEST(test_string_assign_invalid) {
  sp_string* str = sp_string_create("quick brown fox jumps over the lazy dog");
  sp_size_t oldcap = sp_string_capacity(str);

  ck_assert_int_eq(sp_string_assign(str, NULL), SP_ERR_INVALID);

  ck_assert_int_eq(sp_string_size(str), 39);
  ck_assert_int_eq(sp_string_capacity(str), oldcap);

  ck_assert_str_eq(sp_string_c_str(str),
                   "quick brown fox jumps over the lazy dog");

  sp_string_destroy(str);
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

START_TEST(test_string_assign_chars_invalid_count) {
  sp_string* str = sp_string_create("quick brown fox jumps over the lazy dog");
  sp_size_t oldcap = sp_string_capacity(str);

  ck_assert_int_eq(sp_string_assign_chars(str, 'a', -5), SP_ERR_INVALID);

  ck_assert_int_eq(sp_string_size(str), 39);
  ck_assert_int_eq(sp_string_capacity(str), oldcap);

  ck_assert_str_eq(sp_string_c_str(str),
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

  ck_assert_str_eq(sp_string_c_str(str), "");

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

  ck_assert_str_eq(sp_string_c_str(str), "");

  sp_string_destroy(str);
}
END_TEST

START_TEST(test_string_backspace) {
  sp_string* str = sp_string_create("quick");

  sp_string_backspace(str);

  ck_assert_str_eq(sp_string_c_str(str), "quic");

  sp_string_destroy(str);
}
END_TEST

START_TEST(test_string_backspace_empty) {
  sp_string* str = sp_string_create("");

  ck_assert_int_eq(sp_string_backspace(str), SP_ERR_INVALID);

  ck_assert_int_eq(sp_string_size(str), 0);

  ck_assert_str_eq(sp_string_c_str(str), "");

  sp_string_destroy(str);
}
END_TEST

START_TEST(test_string_pop_back) {
  sp_string* str = sp_string_create("quick");

  sp_string_backspace(str);

  ck_assert_str_eq(sp_string_c_str(str), "quic");

  sp_string_destroy(str);
}
END_TEST

START_TEST(test_string_concat) {
  sp_string* str = sp_string_create("quick");

  ck_assert_int_eq(sp_string_concat(str, "sand"), 0);

  ck_assert_int_eq(sp_string_size(str), 9);

  ck_assert_str_eq(sp_string_c_str(str), "quicksand");

  sp_string_destroy(str);
}
END_TEST

START_TEST(test_string_concat_empty) {
  sp_string* str = sp_string_create("quick");

  ck_assert_int_eq(sp_string_concat(str, ""), 0);

  ck_assert_int_eq(sp_string_size(str), 5);

  ck_assert_str_eq(sp_string_c_str(str), "quick");

  sp_string_destroy(str);
}
END_TEST

START_TEST(test_string_concat_to_empty) {
  sp_string* str = sp_string_create("");

  ck_assert_int_eq(sp_string_concat(str, "quick"), 0);

  ck_assert_int_eq(sp_string_size(str), 5);

  ck_assert_str_eq(sp_string_c_str(str), "quick");

  sp_string_destroy(str);
}
END_TEST

START_TEST(test_string_concat_invalid) {
  sp_string* str = sp_string_create("quick");

  ck_assert_int_eq(sp_string_concat(str, NULL), SP_ERR_INVALID);

  sp_string_destroy(str);
}
END_TEST

START_TEST(test_string_concat_string) {
  sp_string* con = sp_string_create("quick");
  sp_string* cat = sp_string_create("sand");

  ck_assert_int_eq(sp_string_concat_string(con, cat), 0);

  ck_assert_int_eq(sp_string_size(con), 9);

  ck_assert_str_eq(sp_string_c_str(con), "quicksand");
  ck_assert_str_eq(sp_string_c_str(cat), "sand");

  sp_string_destroy(con);
  sp_string_destroy(cat);
}
END_TEST

START_TEST(test_string_concat_empty_string) {
  sp_string* con = sp_string_create("quick");
  sp_string* cat = sp_string_create("");

  ck_assert_int_eq(sp_string_concat_string(con, cat), 0);

  ck_assert_int_eq(sp_string_size(con), 5);

  ck_assert_str_eq(sp_string_c_str(con), "quick");

  sp_string_destroy(con);
  sp_string_destroy(cat);
}
END_TEST

START_TEST(test_string_concat_to_empty_string) {
  sp_string* con = sp_string_create("");
  sp_string* cat = sp_string_create("quick");

  ck_assert_int_eq(sp_string_concat_string(con, cat), 0);

  ck_assert_int_eq(sp_string_size(con), 5);

  ck_assert_str_eq(sp_string_c_str(con), "quick");

  sp_string_destroy(con);
  sp_string_destroy(cat);
}
END_TEST

START_TEST(test_string_concat_invalid_string) {
  sp_string* str = sp_string_create("quick");

  ck_assert_int_eq(sp_string_concat(str, NULL), SP_ERR_INVALID);

  sp_string_destroy(str);
}
END_TEST

START_TEST(test_string_concat_chars) {
  sp_string* str = sp_string_create("quick");

  ck_assert_int_eq(sp_string_concat_chars(str, 'e', 5), 0);

  ck_assert_str_eq(sp_string_c_str(str), "quickeeeee");

  sp_string_destroy(str);
}
END_TEST

START_TEST(test_string_concat_chars_zero) {
  sp_string* str = sp_string_create("quick");

  ck_assert_int_eq(sp_string_concat_chars(str, 'e', 0), 0);

  ck_assert_str_eq(sp_string_c_str(str), "quick");

  sp_string_destroy(str);
}
END_TEST

START_TEST(test_string_concat_chars_null_term) {
  sp_string* str = sp_string_create("quick");

  ck_assert_int_eq(sp_string_concat_chars(str, '\0', 5), 0);

  ck_assert_str_eq(sp_string_c_str(str), "quick");

  sp_string_destroy(str);
}
END_TEST

START_TEST(test_string_concat_chars_invalid) {
  sp_string* str = sp_string_create("quick");

  ck_assert_int_eq(sp_string_concat_chars(str, 'e', -5), SP_ERR_INVALID);

  ck_assert_str_eq(sp_string_c_str(str), "quick");

  sp_string_destroy(str);
}
END_TEST

Suite* string_suite() {
  Suite* s = suite_create("\033[34m-=string=-\033[0m");
  TCase* tc = tcase_create("string_rc");

  tcase_add_test(tc, test_string_init_zero);
  tcase_add_test(tc, test_string_init_chars);
  tcase_add_test(tc, test_string_init_chars_zero);
  tcase_add_test(tc, test_string_init_chars_null_term);
  tcase_add_test(tc, test_string_init_static);
  tcase_add_test(tc, test_string_init_static_empty);

  tcase_add_test(tc, test_string_reseve);
  tcase_add_test(tc, test_string_reseve_expand);
  tcase_add_test(tc, test_string_reseve_shrink);
  tcase_add_test(tc, test_string_reseve_neg);
  tcase_add_test(tc, test_string_shrink_to_fit);

  tcase_add_test(tc, test_string_assign);
  tcase_add_test(tc, test_string_assign_existing);
  tcase_add_test(tc, test_string_assign_shrink);
  tcase_add_test(tc, test_string_assign_empty);

  tcase_add_test(tc, test_string_assign_chars);
  tcase_add_test(tc, test_string_assign_chars_existing);
  tcase_add_test(tc, test_string_assign_chars_shrink);
  tcase_add_test(tc, test_string_assign_chars_zero);
  tcase_add_test(tc, test_string_assign_chars_null_term);

  tcase_add_test(tc, test_string_concat);
  tcase_add_test(tc, test_string_concat_empty);
  tcase_add_test(tc, test_string_concat_to_empty);
  tcase_add_test(tc, test_string_concat_invalid);
  tcase_add_test(tc, test_string_concat_string);
  tcase_add_test(tc, test_string_concat_empty_string);
  tcase_add_test(tc, test_string_concat_to_empty_string);
  tcase_add_test(tc, test_string_concat_chars);
  tcase_add_test(tc, test_string_concat_chars_zero);
  tcase_add_test(tc, test_string_concat_chars_null_term);
  tcase_add_test(tc, test_string_concat_chars_invalid);


  suite_add_tcase(s, tc);
  return s;
}

int main() {
  int failed = 0;

  SRunner* sr = srunner_create(string_suite());

  srunner_set_fork_status(sr, CK_NOFORK);
  srunner_run_all(sr, CK_NORMAL);

  failed += srunner_ntests_failed(sr);
  srunner_free(sr);

  return failed == 0 ? 0 : 1;
}
