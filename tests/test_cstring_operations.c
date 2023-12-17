#include "sp/cstring.h"
#include "tests.h"

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

START_TEST(test_string_concat_null) {
  sp_string* str = sp_string_create("quick");

  ck_assert_int_eq(sp_string_concat(str, NULL), SP_ERR_INVALID);

  sp_string_destroy(str);
}
END_TEST

START_TEST(test_string_concatn) {
  sp_string* str = sp_string_create("quick");

  ck_assert_int_eq(sp_string_concatn(str, "sand fasm", 4), 0);

  ck_assert_int_eq(sp_string_size(str), 9);

  ck_assert_str_eq(sp_string_c_str(str), "quicksand");

  sp_string_destroy(str);
}
END_TEST

START_TEST(test_string_concatn_zero) {
  sp_string* str = sp_string_create("quick");

  ck_assert_int_eq(sp_string_concatn(str, "sand", 0), 0);

  ck_assert_int_eq(sp_string_size(str), 5);

  ck_assert_str_eq(sp_string_c_str(str), "quick");

  sp_string_destroy(str);
}
END_TEST

START_TEST(test_string_concatn_to_empty) {
  sp_string* str = sp_string_create("");

  ck_assert_int_eq(sp_string_concatn(str, "quicksand", 5), 0);

  ck_assert_int_eq(sp_string_size(str), 5);

  ck_assert_str_eq(sp_string_c_str(str), "quick");

  sp_string_destroy(str);
}
END_TEST

START_TEST(test_string_concatn_null) {
  sp_string* str = sp_string_create("quick");

  ck_assert_int_eq(sp_string_concatn(str, NULL, 13), SP_ERR_INVALID);

  sp_string_destroy(str);
}
END_TEST

START_TEST(test_string_concatn_neg) {
  sp_string* str = sp_string_create("quick");

  ck_assert_int_eq(sp_string_concatn(str, "null", -13), SP_ERR_INVALID);

  sp_string_destroy(str);
}
END_TEST

START_TEST(test_string_concats) {
  sp_string* con = sp_string_create("quick");
  sp_string* cat = sp_string_create("sand");

  ck_assert_int_eq(sp_string_concats(con, cat), 0);

  ck_assert_int_eq(sp_string_size(con), 9);

  ck_assert_str_eq(sp_string_c_str(con), "quicksand");
  ck_assert_str_eq(sp_string_c_str(cat), "sand");

  sp_string_destroy(con);
  sp_string_destroy(cat);
}
END_TEST

START_TEST(test_string_concats_empty) {
  sp_string* con = sp_string_create("quick");
  sp_string* cat = sp_string_create("");

  ck_assert_int_eq(sp_string_concats(con, cat), 0);

  ck_assert_int_eq(sp_string_size(con), 5);

  ck_assert_str_eq(sp_string_c_str(con), "quick");

  sp_string_destroy(con);
  sp_string_destroy(cat);
}
END_TEST

START_TEST(test_string_concats_to_empty) {
  sp_string* con = sp_string_create("");
  sp_string* cat = sp_string_create("quick");

  ck_assert_int_eq(sp_string_concats(con, cat), 0);

  ck_assert_int_eq(sp_string_size(con), 5);

  ck_assert_str_eq(sp_string_c_str(con), "quick");

  sp_string_destroy(con);
  sp_string_destroy(cat);
}
END_TEST

START_TEST(test_string_concats_null) {
  sp_string* str = sp_string_create("quick");

  ck_assert_int_eq(sp_string_concat(str, NULL), SP_ERR_INVALID);

  sp_string_destroy(str);
}
END_TEST

START_TEST(test_string_append) {
  sp_string* str = sp_string_create("quick");

  ck_assert_int_eq(sp_string_append(str, 'e', 5), 0);

  ck_assert_str_eq(sp_string_c_str(str), "quickeeeee");

  sp_string_destroy(str);
}
END_TEST

START_TEST(test_string_append_to_empty) {
  sp_string* str = sp_string_create("");

  ck_assert_int_eq(sp_string_append(str, 'e', 5), 0);

  ck_assert_str_eq(sp_string_c_str(str), "eeeee");

  sp_string_destroy(str);
}
END_TEST

START_TEST(test_string_append_zero) {
  sp_string* str = sp_string_create("quick");

  ck_assert_int_eq(sp_string_append(str, 'e', 0), 0);

  ck_assert_str_eq(sp_string_c_str(str), "quick");

  sp_string_destroy(str);
}
END_TEST

START_TEST(test_string_append_null_term) {
  sp_string* str = sp_string_create("quick");

  ck_assert_int_eq(sp_string_append(str, '\0', 5), 0);

  ck_assert_str_eq(sp_string_c_str(str), "quick");

  sp_string_destroy(str);
}
END_TEST

START_TEST(test_string_append_neg) {
  sp_string* str = sp_string_create("quick");

  ck_assert_int_eq(sp_string_append(str, 'e', -5), SP_ERR_INVALID);

  ck_assert_str_eq(sp_string_c_str(str), "quick");

  sp_string_destroy(str);
}
END_TEST

Suite* operations_suite() {
  Suite* suite = suite_create("\033[34mstring operations\033[0m");
  TCase* concat = tcase_create("tcase_concat");

  tcase_add_test(concat, test_string_concat);
  tcase_add_test(concat, test_string_concat_empty);
  tcase_add_test(concat, test_string_concat_to_empty);
  tcase_add_test(concat, test_string_concat_null);
  tcase_add_test(concat, test_string_concatn);
  tcase_add_test(concat, test_string_concatn_to_empty);
  tcase_add_test(concat, test_string_concatn_zero);
  tcase_add_test(concat, test_string_concatn_neg);
  tcase_add_test(concat, test_string_concatn_null);
  tcase_add_test(concat, test_string_concats);
  tcase_add_test(concat, test_string_concats_empty);
  tcase_add_test(concat, test_string_concats_to_empty);
  tcase_add_test(concat, test_string_concats_null);

  TCase* append = tcase_create("tcase_append");

  tcase_add_test(concat, test_string_append);
  tcase_add_test(concat, test_string_append_to_empty);
  tcase_add_test(concat, test_string_append_zero);
  tcase_add_test(concat, test_string_append_null_term);
  tcase_add_test(concat, test_string_append_neg);

  suite_add_tcase(suite, concat);
  suite_add_tcase(suite, append);
  return suite;
}
