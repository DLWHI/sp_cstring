#include "sp/cstring.h"
#include "tests.h"

START_TEST(test_string_erase) {
  sp_string* str = sp_string_create("quicktrashsand");

  ck_assert_int_eq(sp_string_erase(str, 5, 5), 0);

  ck_assert_int_eq(sp_string_size(str), 9);

  ck_assert_str_eq(sp_string_c_str(str), "quicksand");

  sp_string_destroy(str);
}
END_TEST

START_TEST(test_string_erase_end) {
  sp_string* str = sp_string_create("quicksandtrash");

  ck_assert_int_eq(sp_string_erase(str, 9, 5), 0);

  ck_assert_int_eq(sp_string_size(str), 9);

  ck_assert_str_eq(sp_string_c_str(str), "quicksand");

  sp_string_destroy(str);
}
END_TEST

START_TEST(test_string_erase_begin) {
  sp_string* str = sp_string_create("trashquicksand");

  ck_assert_int_eq(sp_string_erase(str, 0, 5), 0);

  ck_assert_int_eq(sp_string_size(str), 9);

  ck_assert_str_eq(sp_string_c_str(str), "quicksand");

  sp_string_destroy(str);
}
END_TEST

START_TEST(test_string_erase_all) {
  sp_string* str = sp_string_create("quicksandtrash");

  ck_assert_int_eq(sp_string_erase(str, 0, 14), 0);

  ck_assert_int_eq(sp_string_size(str), 0);

  ck_assert_str_eq(sp_string_c_str(str), "");

  sp_string_destroy(str);
}
END_TEST

START_TEST(test_string_erase_out_of_bonds) {
  sp_string* str = sp_string_create("quicksandtrash");

  ck_assert_int_eq(sp_string_erase(str, 0, 15), SP_ERR_INVALID);
  ck_assert_int_eq(sp_string_erase(str, 16, 1), SP_ERR_INVALID);
  ck_assert_int_eq(sp_string_erase(str, -213, 11), SP_ERR_INVALID);
  ck_assert_int_eq(sp_string_erase(str, 0, -23), SP_ERR_INVALID);
  ck_assert_int_eq(sp_string_erase(str, 32432432, 155325), SP_ERR_INVALID);

  sp_string_destroy(str);
}
END_TEST

Suite* erasure_suite() {
  Suite* suite = suite_create("\033[34merasure operations\033[0m");
  TCase* erasure = tcase_create("tcase_erasure");

  tcase_add_test(erasure, test_string_erase);
  tcase_add_test(erasure, test_string_erase_begin);
  tcase_add_test(erasure, test_string_erase_end);
  tcase_add_test(erasure, test_string_erase_all);
  tcase_add_test(erasure, test_string_erase_out_of_bonds);

  suite_add_tcase(suite, erasure);
  return suite;
}
