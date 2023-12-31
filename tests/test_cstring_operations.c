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

START_TEST(test_string_concatn) {
  sp_string* str = sp_string_create("quick");

  ck_assert_int_eq(sp_string_concatn(str, "sand fasm", 4), 0);

  ck_assert_int_eq(sp_string_size(str), 9);

  ck_assert_str_eq(sp_string_c_str(str), "quicksand");

  sp_string_destroy(str);
}
END_TEST

START_TEST(test_string_concatn_self) {
  sp_string* str = sp_string_create("quicksand");

  ck_assert_int_eq(sp_string_concatn(str, SP_CSTR(str) + 5, 4), 0);

  ck_assert_int_eq(sp_string_size(str), 13);

  ck_assert_str_eq(sp_string_c_str(str), "quicksandsand");

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

START_TEST(test_string_concats_self) {
  sp_string* con = sp_string_create("quick");

  ck_assert_int_eq(sp_string_concats(con, con), 0);

  ck_assert_int_eq(sp_string_size(con), 10);

  ck_assert_str_eq(sp_string_c_str(con), "quickquick");

  sp_string_destroy(con);
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

START_TEST(test_string_concat_range) {
  sp_string* str = sp_string_create("quick");
  const char* range = "sand fasm";
  ck_assert_int_eq(sp_string_concat_range(str, range, range + 4), 0);

  ck_assert_int_eq(sp_string_size(str), 9);

  ck_assert_str_eq(sp_string_c_str(str), "quicksand");

  sp_string_destroy(str);
}
END_TEST

START_TEST(test_string_concat_range_self) {
  sp_string* str = sp_string_create("quicksand");

  ck_assert_int_eq(sp_string_concat_range(str, SP_CSTR(str), SP_CSTR(str) + 6), 0);

  ck_assert_int_eq(sp_string_size(str), 15);

  ck_assert_str_eq(sp_string_c_str(str), "quicksandquicks");

  sp_string_destroy(str);
}
END_TEST

START_TEST(test_string_concat_range_empty) {
  sp_string* str = sp_string_create("quick");
  const char* range = "range";

  ck_assert_int_eq(sp_string_concat_range(str, range, range), 0);

  ck_assert_int_eq(sp_string_size(str), 5);

  ck_assert_str_eq(sp_string_c_str(str), "quick");

  sp_string_destroy(str);
}
END_TEST

START_TEST(test_string_concat_range_to_empty) {
  sp_string* str = sp_string_create("");
  const char* range = "quicksand";

  ck_assert_int_eq(sp_string_concat_range(str, range, range + 5), 0);

  ck_assert_int_eq(sp_string_size(str), 5);

  ck_assert_str_eq(sp_string_c_str(str), "quick");

  sp_string_destroy(str);
}
END_TEST

START_TEST(test_string_concat_range_invalid) {
  sp_string* str = sp_string_create("quick");
  const char* range = "quicksand";

  ck_assert_int_eq(sp_string_concat_range(str, range + 4, range + 1), SP_ERR_INVALID);

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

START_TEST(test_string_letter_case) {
  sp_string* str = sp_string_create("qUiCk bRoWN foXXxxxxXX");

  sp_string_to_lower(str);

  ck_assert_str_eq(sp_string_c_str(str), "quick brown foxxxxxxxx");

  sp_string_to_upper(str);

  ck_assert_str_eq(sp_string_c_str(str), "QUICK BROWN FOXXXXXXXX");

  sp_string_destroy(str);
}
END_TEST

START_TEST(test_string_letter_case_w_symbols) {
  sp_string* str = sp_string_create("qUiCk. 1337 bR%oWN 32_foX_");

  sp_string_to_lower(str);

  ck_assert_str_eq(sp_string_c_str(str), "quick. 1337 br%own 32_fox_");

  sp_string_to_upper(str);

  ck_assert_str_eq(sp_string_c_str(str), "QUICK. 1337 BR%OWN 32_FOX_");

  sp_string_destroy(str);
}
END_TEST

START_TEST(test_string_trim) {
  sp_string* str = sp_string_create("  __ _ \t \t ---current joys---   \r\n\n\n- ");

  sp_string_trim(str, "_- \t\r\n");

  ck_assert_str_eq(sp_string_c_str(str), "current joys");

  sp_string_destroy(str);
}
END_TEST

START_TEST(test_string_trim_one_symbol) {
  sp_string* str = sp_string_create("  __ _ \t \t ---current joys---   \r\n\n\n- ");

  sp_string_trim(str, " ");

  ck_assert_str_eq(sp_string_c_str(str), "__ _ \t \t ---current joys---   \r\n\n\n-");

  sp_string_destroy(str);
}
END_TEST

Suite* operations_suite() {
  Suite* suite = suite_create("\033[34mstring operations\033[0m");
  TCase* concat = tcase_create("tcase_concat");

  tcase_add_test(concat, test_string_concat);
  tcase_add_test(concat, test_string_concat_empty);
  tcase_add_test(concat, test_string_concat_to_empty);
  tcase_add_test(concat, test_string_concatn);
  tcase_add_test(concat, test_string_concatn_self);
  tcase_add_test(concat, test_string_concatn_to_empty);
  tcase_add_test(concat, test_string_concatn_zero);
  tcase_add_test(concat, test_string_concatn_neg);
  tcase_add_test(concat, test_string_concats);
  tcase_add_test(concat, test_string_concats_self);
  tcase_add_test(concat, test_string_concats_empty);
  tcase_add_test(concat, test_string_concats_to_empty);

  TCase* concat_range = tcase_create("tcase_concat_range");
  tcase_add_test(concat_range, test_string_concat_range);
  tcase_add_test(concat_range, test_string_concat_range_empty);
  tcase_add_test(concat_range, test_string_concat_range_self);
  tcase_add_test(concat_range, test_string_concat_range_to_empty);
  tcase_add_test(concat_range, test_string_concat_range_invalid);

  TCase* append = tcase_create("tcase_append");

  tcase_add_test(append, test_string_append);
  tcase_add_test(append, test_string_append_to_empty);
  tcase_add_test(append, test_string_append_zero);
  tcase_add_test(append, test_string_append_null_term);
  tcase_add_test(append, test_string_append_neg);

  TCase* letter_case = tcase_create("tcase_letter_case");

  tcase_add_test(letter_case, test_string_letter_case);
  tcase_add_test(letter_case, test_string_letter_case_w_symbols);

  TCase* trim = tcase_create("tcase_trim");

  tcase_add_test(trim, test_string_trim);
  tcase_add_test(trim, test_string_trim_one_symbol);

  suite_add_tcase(suite, concat);
  suite_add_tcase(suite, concat_range);
  suite_add_tcase(suite, append);
  suite_add_tcase(suite, letter_case);
  suite_add_tcase(suite, trim);
  return suite;
}
