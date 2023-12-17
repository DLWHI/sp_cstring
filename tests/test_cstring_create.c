#include "sp/cstring.h"
#include "tests.h"

START_TEST(test_string_init_default) {
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

START_TEST(test_string_init_chars_neg) {
  sp_string* str = sp_string_create_chars('a', -23);

  ck_assert_ptr_null(str);

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

START_TEST(test_string_init_chars_eof) {
  sp_size_t len = 2147;
  sp_string* str = sp_string_create_chars(-1, len);

  ck_assert_ptr_nonnull(str);
  ck_assert_ptr_nonnull(sp_string_begin(str));
  ck_assert_ptr_nonnull(sp_string_end(str));
  ck_assert_int_eq(sp_string_end(str) - sp_string_begin(str),
                   sp_string_size(str));
  ck_assert_int_eq(sp_string_size(str), len);
  ck_assert_int_eq(sp_string_capacity(str), len + 1);

  for (sp_size_t i = 0; i < len; ++i) {
    ck_assert_int_eq(sp_string_char_at(str, i), -1);
  }

  sp_string_destroy(str);
}
END_TEST

START_TEST(test_string_init) {
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

START_TEST(test_string_init_empty) {
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

START_TEST(test_string_init_ptr_null) {
  sp_string* str = sp_string_create(NULL);

  ck_assert_ptr_null(str);

  sp_string_destroy(str);
}
END_TEST

START_TEST(test_string_initn_ptr_null) {
  sp_string* str = sp_string_createn(NULL, 726317);

  ck_assert_ptr_null(str);

  sp_string_destroy(str);
}
END_TEST

START_TEST(test_string_initn) {
  sp_string* str =
      sp_string_createn("quick brown fox jumps over the lazy dog", 5);
  const char* exp = "quick";
  int len = 5;

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

START_TEST(test_string_initn_zero) {
  sp_string* str = sp_string_createn("asdfghjkl;'", 0);

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

START_TEST(test_string_initn_neg) {
  sp_string* str = sp_string_createn("asdfghjkl;'", -100);

  ck_assert_ptr_null(str);

  sp_string_destroy(str);
}
END_TEST

START_TEST(test_string_copy) {
  sp_string* str = sp_string_create("quick brown fox jumps over the lazy dog");
  sp_string* cpy = sp_string_copy(str);

  ck_assert_ptr_nonnull(cpy);
  ck_assert_ptr_nonnull(sp_string_begin(cpy));
  ck_assert_ptr_nonnull(sp_string_end(cpy));
  ck_assert_int_eq(sp_string_end(cpy) - sp_string_begin(cpy),
                   sp_string_size(cpy));
  ck_assert_int_eq(sp_string_size(cpy), sp_string_size(str));
  ck_assert_str_eq(sp_string_c_str(cpy), sp_string_c_str(str));

  sp_string_destroy(str);
  sp_string_destroy(cpy);
}
END_TEST

START_TEST(test_string_copy_null) {
  sp_string* str = sp_string_copy(NULL);

  ck_assert_ptr_null(str);

  sp_string_destroy(str);
}
END_TEST

START_TEST(test_string_copy_empty) {
  sp_string* str = sp_string_create("");
  sp_string* cpy = sp_string_copy(str);

  ck_assert_ptr_nonnull(cpy);
  ck_assert_ptr_null(sp_string_begin(cpy));
  ck_assert_ptr_null(sp_string_end(cpy));
  ck_assert_int_eq(sp_string_end(cpy) - sp_string_begin(cpy),
                   sp_string_size(cpy));
  ck_assert_int_eq(sp_string_size(cpy), 0);
  ck_assert_int_eq(sp_string_capacity(cpy), 0);

  sp_string_destroy(cpy);
  sp_string_destroy(str);
}
END_TEST

START_TEST(test_string_move) {
  sp_string* str = sp_string_create("quick brown fox jumps over the lazy dog");
  sp_string* cpy = sp_string_copy(str);
  sp_string* mv = sp_string_move(str);

  ck_assert_ptr_nonnull(mv);
  ck_assert_ptr_nonnull(str);
  ck_assert_ptr_nonnull(sp_string_begin(mv));
  ck_assert_ptr_nonnull(sp_string_end(mv));
  ck_assert_int_eq(sp_string_end(mv) - sp_string_begin(mv), sp_string_size(mv));
  ck_assert_int_eq(sp_string_end(str) - sp_string_begin(str),
                   sp_string_size(str));
  ck_assert_int_eq(sp_string_size(mv), sp_string_size(cpy));
  ck_assert_str_eq(sp_string_c_str(mv), sp_string_c_str(cpy));

  sp_string_size(str);

  sp_string_destroy(str);
  sp_string_destroy(cpy);
  sp_string_destroy(mv);
}
END_TEST

START_TEST(test_string_move_empty) {
  sp_string* str = sp_string_create("");
  sp_string* cpy = sp_string_copy(str);
  sp_string* mv = sp_string_move(str);

  ck_assert_ptr_nonnull(mv);
  ck_assert_ptr_nonnull(str);
  ck_assert_ptr_null(sp_string_begin(mv));
  ck_assert_ptr_null(sp_string_end(mv));
  ck_assert_int_eq(sp_string_end(str) - sp_string_begin(str),
                   sp_string_size(str));
  ck_assert_int_eq(sp_string_size(mv), sp_string_size(cpy));

  sp_string_size(str);

  sp_string_destroy(str);
  sp_string_destroy(cpy);
  sp_string_destroy(mv);
}
END_TEST

START_TEST(test_string_move_null) {
  sp_string* str = sp_string_copy(NULL);

  ck_assert_ptr_null(str);

  sp_string_destroy(str);
}
END_TEST

START_TEST(test_string_swap) {
  sp_string* str1 = sp_string_create("astring");
  sp_string* str2 = sp_string_create("bstring");
  sp_string* str1_cpy = sp_string_copy(str1);
  sp_string* str2_cpy = sp_string_copy(str2);

  ck_assert_int_eq(sp_string_swap(str1, str2), 0);

  ck_assert_str_eq(sp_string_c_str(str1), sp_string_c_str(str2_cpy));
  ck_assert_str_eq(sp_string_c_str(str2), sp_string_c_str(str1_cpy));

  sp_string_destroy(str1);
  sp_string_destroy(str2);
  sp_string_destroy(str1_cpy);
  sp_string_destroy(str2_cpy);
}
END_TEST

START_TEST(test_string_swap_null) {
  sp_string* str = sp_string_create("astring");

  ck_assert_int_eq(sp_string_swap(str, NULL), SP_ERR_INVALID);
  ck_assert_int_eq(sp_string_swap(NULL, str), SP_ERR_INVALID);
  ck_assert_int_eq(sp_string_swap(NULL, NULL), SP_ERR_INVALID);

  sp_string_destroy(str);
}
END_TEST

START_TEST(test_string_swap_self) {
  sp_string* str = sp_string_create("astring");

  ck_assert_int_eq(sp_string_swap(str, str), 0);
  ck_assert_ptr_nonnull(str);
  ck_assert_ptr_nonnull(sp_string_begin(str));
  ck_assert_ptr_nonnull(sp_string_end(str));
  ck_assert_int_eq(sp_string_end(str) - sp_string_begin(str),
                   sp_string_size(str));

  sp_string_destroy(str);
}
END_TEST

START_TEST(test_string_front_back) {
  sp_string* str = sp_string_create("i wanted to tell you i like...");

  ck_assert_int_eq(sp_string_front(str), 'i');
  ck_assert_int_eq(sp_string_back(str), '.');

  sp_string_destroy(str);
}
END_TEST

// START_TEST(test_string_backspace) {
//   sp_string* str = sp_string_create("quick");

//   sp_string_backspace(str);

//   ck_assert_str_eq(sp_string_c_str(str), "quic");

//   sp_string_destroy(str);
// }
// END_TEST

// START_TEST(test_string_backspace_empty) {
//   sp_string* str = sp_string_create("");

//   ck_assert_int_eq(sp_string_backspace(str), SP_ERR_INVALID);

//   ck_assert_int_eq(sp_string_size(str), 0);

//   ck_assert_str_eq(sp_string_c_str(str), "");

//   sp_string_destroy(str);
// }
// END_TEST

// START_TEST(test_string_pop_back) {
//   sp_string* str = sp_string_create("quick");

//   sp_string_backspace(str);

//   ck_assert_str_eq(sp_string_c_str(str), "quic");

//   sp_string_destroy(str);
// }
// END_TEST

Suite* init_suite() {
  Suite* suite = suite_create("\033[34mctor/dtor functions\033[0m");
  TCase* def = tcase_create("tcase_def");
  tcase_add_test(def, test_string_init_default);
  tcase_add_test(def, test_string_front_back);

  TCase* ptr = tcase_create("tcase_ptr");
  tcase_add_test(ptr, test_string_init);
  tcase_add_test(ptr, test_string_init_empty);
  tcase_add_test(ptr, test_string_init_ptr_null);
  tcase_add_test(ptr, test_string_initn);
  tcase_add_test(ptr, test_string_initn_zero);
  tcase_add_test(ptr, test_string_initn_neg);
  tcase_add_test(ptr, test_string_initn_ptr_null);

  TCase* chars = tcase_create("tcase_chars");
  tcase_add_test(chars, test_string_init_chars);
  tcase_add_test(chars, test_string_init_chars_null_term);
  tcase_add_test(chars, test_string_init_chars_zero);
  tcase_add_test(chars, test_string_init_chars_neg);
  tcase_add_test(chars, test_string_init_chars_eof);

  TCase* copy_move_swap = tcase_create("tcase_cms");

  tcase_add_test(copy_move_swap, test_string_copy);
  tcase_add_test(copy_move_swap, test_string_move);
  tcase_add_test(copy_move_swap, test_string_copy_empty);
  tcase_add_test(copy_move_swap, test_string_move_empty);
  tcase_add_test(copy_move_swap, test_string_copy_null);
  tcase_add_test(copy_move_swap, test_string_move_null);
  tcase_add_test(copy_move_swap, test_string_swap);
  tcase_add_test(copy_move_swap, test_string_swap_null);
  tcase_add_test(copy_move_swap, test_string_swap_self);

  suite_add_tcase(suite, def);
  suite_add_tcase(suite, ptr);
  suite_add_tcase(suite, chars);
  suite_add_tcase(suite, copy_move_swap);
  return suite;
}
