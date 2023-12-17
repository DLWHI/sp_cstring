#include "sp/cstring.h"
#include "tests.h"

START_TEST(test_string_insert) {
  sp_string* str = sp_string_create("i need to exam");
  sp_size_t pos = 10;

  ck_assert_int_eq(sp_string_insert(str, pos, "pass "), pos);

  ck_assert_str_eq(sp_string_c_str(str), "i need to pass exam");

  sp_string_destroy(str);
}
END_TEST

START_TEST(test_string_insert_reserved) {
  sp_string* str = sp_string_create("i need to exam");
  sp_size_t pos = 10;

  sp_string_reserve(str, 100);

  ck_assert_int_eq(sp_string_insert(str, pos, "pass "), pos);

  ck_assert_str_eq(sp_string_c_str(str), "i need to pass exam");

  sp_string_destroy(str);
}
END_TEST

START_TEST(test_string_insert_begin) {
  sp_string* str = sp_string_create("i need to exam");

  ck_assert_int_eq(sp_string_insert(str, 0, "pass "), 0);

  ck_assert_str_eq(sp_string_c_str(str), "pass i need to exam");

  sp_string_destroy(str);
}
END_TEST

START_TEST(test_string_insert_end) {
  sp_string* str = sp_string_create("i need to exam");

  ck_assert_int_eq(sp_string_insert(str, 14, "pass "), 14);

  ck_assert_str_eq(sp_string_c_str(str), "i need to exampass ");

  sp_string_destroy(str);
}
END_TEST

START_TEST(test_string_insert_to_empty) {
  sp_string* str = sp_string_create_empty();
  const char* ptr = "let there be something in every soul that is lost";
  ck_assert_int_eq(sp_string_insert(str, 0, ptr), 0);

  ck_assert_str_eq(sp_string_c_str(str), ptr);

  sp_string_destroy(str);
}
END_TEST

START_TEST(test_string_insert_empty) {
  sp_string* str = sp_string_create("i need to exam");

  ck_assert_int_eq(sp_string_insert(str, 7, ""), 7);

  ck_assert_str_eq(sp_string_c_str(str), "i need to exam");

  sp_string_destroy(str);
}
END_TEST

START_TEST(test_string_insert_out_of_bonds) {
  sp_string* str = sp_string_create("i need to exam");

  ck_assert_int_eq(sp_string_insert(str, -30, "fail"), SP_ERR_INVALID);
  ck_assert_int_eq(sp_string_insert(str, 30, "fail"), SP_ERR_INVALID);

  sp_string_destroy(str);
}
END_TEST

START_TEST(test_string_insert_null) {
  sp_string* str = sp_string_create("i need to exam");

  ck_assert_int_eq(sp_string_insert(str, 4, NULL), SP_ERR_INVALID);

  sp_string_destroy(str);
}
END_TEST

START_TEST(test_string_insertn) {
  sp_string* str = sp_string_create("i need to exam");
  sp_size_t pos = 10;

  ck_assert_int_eq(sp_string_insertn(str, pos, "pass asd", 5), pos);

  ck_assert_str_eq(sp_string_c_str(str), "i need to pass exam");

  sp_string_destroy(str);
}
END_TEST

START_TEST(test_string_insertn_reserved) {
  sp_string* str = sp_string_create("i need to exam");
  sp_size_t pos = 10;

  sp_string_reserve(str, 100);

  ck_assert_int_eq(sp_string_insertn(str, pos, "pass asd", 5), pos);

  ck_assert_str_eq(sp_string_c_str(str), "i need to pass exam");

  sp_string_destroy(str);
}
END_TEST

START_TEST(test_string_insertn_begin) {
  sp_string* str = sp_string_create("i need to exam");

  ck_assert_int_eq(sp_string_insertn(str, 0, "pass asd", 5), 0);

  ck_assert_str_eq(sp_string_c_str(str), "pass i need to exam");

  sp_string_destroy(str);
}
END_TEST

START_TEST(test_string_insertn_end) {
  sp_string* str = sp_string_create("i need to exam");

  ck_assert_int_eq(sp_string_insertn(str, 14, "pass asd", 4), 14);

  ck_assert_str_eq(sp_string_c_str(str), "i need to exampass");

  sp_string_destroy(str);
}
END_TEST

START_TEST(test_string_insertn_to_empty) {
  sp_string* str = sp_string_create_empty();
  const char* ptr = "let there be something in every soul that is lost";
  ck_assert_int_eq(sp_string_insertn(str, 0, ptr, 49), 0);

  ck_assert_str_eq(sp_string_c_str(str), ptr);

  sp_string_destroy(str);
}
END_TEST

START_TEST(test_string_insertn_empty) {
  sp_string* str = sp_string_create("i need to exam");

  ck_assert_int_eq(sp_string_insertn(str, 7, "", 100), 7);

  ck_assert_str_eq(sp_string_c_str(str), "i need to exam");

  sp_string_destroy(str);
}
END_TEST

START_TEST(test_string_insertn_out_of_bonds) {
  sp_string* str = sp_string_create("i need to exam");

  ck_assert_int_eq(sp_string_insert(str, -30, "fail"), SP_ERR_INVALID);
  ck_assert_int_eq(sp_string_insert(str, 30, "fail"), SP_ERR_INVALID);

  sp_string_destroy(str);
}
END_TEST

START_TEST(test_string_insertn_null) {
  sp_string* str = sp_string_create("i need to exam");

  ck_assert_int_eq(sp_string_insert(str, 4, NULL), SP_ERR_INVALID);

  sp_string_destroy(str);
}
END_TEST

START_TEST(test_string_inserts) {
  sp_string* str = sp_string_create("i need to exam");
  sp_string* ins = sp_string_create("pass ");
  sp_size_t pos = 10;

  ck_assert_int_eq(sp_string_inserts(str, pos, ins), pos);

  ck_assert_str_eq(sp_string_c_str(str), "i need to pass exam");

  sp_string_destroy(str);
  sp_string_destroy(ins);
}
END_TEST

START_TEST(test_string_inserts_reserved) {
  sp_string* str = sp_string_create("i need to exam");
  sp_string* ins = sp_string_create("pass ");
  sp_size_t pos = 10;

  sp_string_reserve(str, 100);

  ck_assert_int_eq(sp_string_inserts(str, pos, ins), pos);

  ck_assert_str_eq(sp_string_c_str(str), "i need to pass exam");

  sp_string_destroy(str);
  sp_string_destroy(ins);
}
END_TEST

START_TEST(test_string_inserts_begin) {
  sp_string* str = sp_string_create("i need to exam");
  sp_string* ins = sp_string_create("pass ");

  ck_assert_int_eq(sp_string_inserts(str, 0, ins), 0);

  ck_assert_str_eq(sp_string_c_str(str), "pass i need to exam");

  sp_string_destroy(str);
  sp_string_destroy(ins);
}
END_TEST

START_TEST(test_string_inserts_end) {
  sp_string* str = sp_string_create("i need to exam");
  sp_string* ins = sp_string_create("pass ");

  ck_assert_int_eq(sp_string_inserts(str, 14, ins), 14);

  ck_assert_str_eq(sp_string_c_str(str), "i need to exampass ");

  sp_string_destroy(str);
  sp_string_destroy(ins);
}
END_TEST

START_TEST(test_string_inserts_to_empty) {
  sp_string* str = sp_string_create_empty();
  const char* ptr = "let there be something in every soul that is lost";
  sp_string* ins = sp_string_create(ptr);

  ck_assert_int_eq(sp_string_inserts(str, 0, ins), 0);

  ck_assert_str_eq(sp_string_c_str(str), ptr);

  sp_string_destroy(str);
  sp_string_destroy(ins);
}
END_TEST

START_TEST(test_string_inserts_empty) {
  sp_string* str = sp_string_create("i need to exam");
  sp_string* ins = sp_string_create_empty();

  ck_assert_int_eq(sp_string_inserts(str, 7, ins), 7);

  ck_assert_str_eq(sp_string_c_str(str), "i need to exam");

  sp_string_destroy(str);
  sp_string_destroy(ins);
}
END_TEST

START_TEST(test_string_inserts_out_of_bonds) {
  sp_string* str = sp_string_create("i need to exam");
  sp_string* ins = sp_string_create("fail");

  ck_assert_int_eq(sp_string_inserts(str, -30, ins), SP_ERR_INVALID);
  ck_assert_int_eq(sp_string_inserts(str, 30, ins), SP_ERR_INVALID);

  sp_string_destroy(str);
  sp_string_destroy(ins);
}
END_TEST

START_TEST(test_string_inserts_null) {
  sp_string* str = sp_string_create("i need to exam");

  ck_assert_int_eq(sp_string_inserts(str, 4, NULL), SP_ERR_INVALID);

  sp_string_destroy(str);
}
END_TEST

START_TEST(test_string_inserti) {
  sp_string* str = sp_string_create("i need to exam");
  sp_size_t ind = 10;
  char* pos = sp_string_begin(str) + ind;

  pos = sp_string_inserti(str, pos, "pass ");
  ck_assert_int_eq(pos - sp_string_begin(str), ind);
  ck_assert_int_eq(*pos, 'p');

  ck_assert_str_eq(sp_string_c_str(str), "i need to pass exam");

  sp_string_destroy(str);
}
END_TEST

START_TEST(test_string_inserti_reserved) {
  sp_string* str = sp_string_create("i need to exam");
  sp_string_reserve(str, 100);
  char* pos = sp_string_begin(str) + 10;

  ck_assert_ptr_eq(sp_string_inserti(str, pos, "pass "), pos);
  ck_assert_int_eq(*pos, 'p');

  ck_assert_str_eq(sp_string_c_str(str), "i need to pass exam");

  sp_string_destroy(str);
}
END_TEST

START_TEST(test_string_inserti_begin) {
  sp_string* str = sp_string_create("i need to exam");

  ck_assert_ptr_eq(sp_string_inserti(str, sp_string_begin(str), "pass "),
                   sp_string_begin(str));
  ck_assert_int_eq(sp_string_front(str), 'p');

  ck_assert_str_eq(sp_string_c_str(str), "pass i need to exam");

  sp_string_destroy(str);
}
END_TEST

START_TEST(test_string_inserti_end) {
  sp_string* str = sp_string_create("i need to exam");
  sp_size_t ind = sp_string_length(str);

  char* pos = sp_string_inserti(str, sp_string_end(str), "pass ");

  ck_assert_ptr_eq(pos, sp_string_begin(str) + ind);
  ck_assert_int_eq(*pos, 'p');

  ck_assert_str_eq(sp_string_c_str(str), "i need to exampass ");

  sp_string_destroy(str);
}
END_TEST

START_TEST(test_string_inserti_to_empty) {
  sp_string* str = sp_string_create_empty();

  ck_assert_ptr_eq(
      sp_string_inserti(str, sp_string_begin(str),
                        "let there be something in every soul that is lost"),
      sp_string_begin(str));

  ck_assert_str_eq(sp_string_c_str(str),
                   "let there be something in every soul that is lost");

  sp_string_destroy(str);
}
END_TEST

START_TEST(test_string_inserti_empty) {
  sp_string* str = sp_string_create("i need to exam");
  char* pos = sp_string_begin(str) + 10;

  ck_assert_ptr_eq(sp_string_inserti(str, pos, ""), pos);
  ck_assert_int_eq(*pos, 'e');

  ck_assert_str_eq(sp_string_c_str(str), "i need to exam");

  sp_string_destroy(str);
}
END_TEST

START_TEST(test_string_inserti_out_of_bonds) {
  sp_string* str = sp_string_create("i need to exam");
  char* outb = sp_string_begin(str) - 10;
  char* oute = sp_string_end(str) + 10;

  ck_assert_ptr_null(sp_string_inserti(str, outb, "fail"));
  ck_assert_ptr_null(sp_string_inserti(str, oute, "fail"));

  sp_string_destroy(str);
}
END_TEST

START_TEST(test_string_inserti_null) {
  sp_string* str = sp_string_create("i need to exam");
  char* pos = sp_string_begin(str) + 10;

  ck_assert_ptr_null(sp_string_inserti(str, pos, NULL));
  ck_assert_ptr_null(sp_string_inserti(str, pos, NULL));

  sp_string_destroy(str);
}
END_TEST

Suite* insertion_suite() {
  Suite* suite = suite_create("\033[34minsert operations\033[0m");
  TCase* insert = tcase_create("tcase_insert");

  tcase_add_test(insert, test_string_insert);
  tcase_add_test(insert, test_string_insert_reserved);
  tcase_add_test(insert, test_string_insert_begin);
  tcase_add_test(insert, test_string_insert_end);
  tcase_add_test(insert, test_string_insert_empty);
  tcase_add_test(insert, test_string_insert_to_empty);
  tcase_add_test(insert, test_string_insert_out_of_bonds);
  tcase_add_test(insert, test_string_insert_null);
  tcase_add_test(insert, test_string_insertn);
  tcase_add_test(insert, test_string_insertn_reserved);
  tcase_add_test(insert, test_string_insertn_begin);
  tcase_add_test(insert, test_string_insertn_end);
  tcase_add_test(insert, test_string_insertn_to_empty);
  tcase_add_test(insert, test_string_insertn_out_of_bonds);
  tcase_add_test(insert, test_string_insertn_null);
  tcase_add_test(insert, test_string_inserts);
  tcase_add_test(insert, test_string_inserts_reserved);
  tcase_add_test(insert, test_string_inserts_begin);
  tcase_add_test(insert, test_string_inserts_end);
  tcase_add_test(insert, test_string_inserts_to_empty);
  tcase_add_test(insert, test_string_inserts_out_of_bonds);
  tcase_add_test(insert, test_string_inserts_null);

  TCase* inserti = tcase_create("tcase_inserti");

  tcase_add_test(insert, test_string_inserti);
  tcase_add_test(insert, test_string_inserti_reserved);
  tcase_add_test(insert, test_string_inserti_begin);
  tcase_add_test(insert, test_string_inserti_end);
  tcase_add_test(insert, test_string_inserti_empty);
  tcase_add_test(insert, test_string_inserti_to_empty);
  tcase_add_test(insert, test_string_inserti_out_of_bonds);
  tcase_add_test(insert, test_string_inserti_null);

  suite_add_tcase(suite, insert);
  suite_add_tcase(suite, inserti);
  return suite;
}