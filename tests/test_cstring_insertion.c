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

START_TEST(test_string_insertn) {
  sp_string* str = sp_string_create("i need to exam");
  sp_size_t pos = 10;

  ck_assert_int_eq(sp_string_insertn(str, pos, "pass asd", 5), pos);

  ck_assert_str_eq(sp_string_c_str(str), "i need to pass exam");

  sp_string_destroy(str);
}
END_TEST

START_TEST(test_string_insertn_self) {
  sp_string* str = sp_string_create("i need to exam");
  sp_size_t pos = 7;
  const char* it = SP_CSTR(str) + 10;

  ck_assert_int_eq(sp_string_insertn(str, pos, it, 4), pos);

  ck_assert_str_eq(sp_string_c_str(str), "i need examto exam");

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

START_TEST(test_string_insertn_zero) {
  sp_string* str = sp_string_create("i need to exam");

  ck_assert_int_eq(sp_string_insertn(str, 7, "not zero", 0), 7);

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

START_TEST(test_string_insertn_neg) {
  sp_string* str = sp_string_create("i need to exam");

  ck_assert_int_eq(sp_string_insertn(str, 4, "what the", -16), SP_ERR_INVALID);

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

START_TEST(test_string_inserts_self) {
  sp_string* str = sp_string_create("i need to exam");

  ck_assert_int_eq(sp_string_inserts(str, 1, str), 1);

  ck_assert_str_eq(sp_string_c_str(str), "ii need to exam need to exam");

  sp_string_destroy(str);
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

START_TEST(test_string_insert_chars) {
  sp_string* str = sp_string_create("i need to exam");
  sp_size_t pos = 10;

  ck_assert_int_eq(sp_string_insert_chars(str, pos, 'a', 5), pos);

  ck_assert_str_eq(sp_string_c_str(str), "i need to aaaaaexam");

  sp_string_destroy(str);
}
END_TEST

START_TEST(test_string_insert_chars_reserved) {
  sp_string* str = sp_string_create("i need to exam");
  sp_size_t pos = 10;

  sp_string_reserve(str, 100);

  ck_assert_int_eq(sp_string_insert_chars(str, pos, 'a', 5), pos);

  ck_assert_str_eq(sp_string_c_str(str), "i need to aaaaaexam");

  sp_string_destroy(str);
}
END_TEST

START_TEST(test_string_insert_chars_begin) {
  sp_string* str = sp_string_create("i need to exam");

  ck_assert_int_eq(sp_string_insert_chars(str, 0, 'a', 7), 0);

  ck_assert_str_eq(sp_string_c_str(str), "aaaaaaai need to exam");

  sp_string_destroy(str);
}
END_TEST

START_TEST(test_string_insert_chars_end) {
  sp_string* str = sp_string_create("i need to exam");

  ck_assert_int_eq(sp_string_insert_chars(str, 14, 'o', 3), 14);

  ck_assert_str_eq(sp_string_c_str(str), "i need to examooo");

  sp_string_destroy(str);
}
END_TEST

START_TEST(test_string_insert_chars_zero) {
  sp_string* str = sp_string_create("i need to exam");

  ck_assert_int_eq(sp_string_insert_chars(str, 7, 'e', 0), 7);

  ck_assert_str_eq(sp_string_c_str(str), "i need to exam");

  sp_string_destroy(str);
}
END_TEST

START_TEST(test_string_insert_chars_out_of_bonds) {
  sp_string* str = sp_string_create("i need to exam");

  ck_assert_int_eq(sp_string_insert_chars(str, -30, 'u', 5), SP_ERR_INVALID);
  ck_assert_int_eq(sp_string_insert_chars(str, 30, 'a', 7), SP_ERR_INVALID);

  sp_string_destroy(str);
}
END_TEST

START_TEST(test_string_insert_chars_neg) {
  sp_string* str = sp_string_create("i need to exam");

  ck_assert_int_eq(sp_string_insert_chars(str, 4, 'r', -10), SP_ERR_INVALID);

  sp_string_destroy(str);
}
END_TEST

START_TEST(test_string_insert_chars_null_term) {
  sp_string* str = sp_string_create("i need to exam");

  ck_assert_int_eq(sp_string_insert_chars(str, 7, '\0', 2140000), 7);

  ck_assert_str_eq(sp_string_c_str(str), "i need ");

  sp_string_destroy(str);
}
END_TEST

START_TEST(test_string_insert_chars_eof) {
  sp_string* str = sp_string_create("i need to exam");

  ck_assert_int_eq(sp_string_insert_chars(str, 7, -1, 3), 7);

  ck_assert_int_eq(strncmp(SP_CSTR(str), "i need t", 7), 0);
  ck_assert_int_eq(strncmp(SP_CSTR(str) + 11, "o exam", 6), 0);

  for (sp_size_t i = 7; i < 10; ++i) {
    ck_assert_int_eq(sp_string_char_at(str, i), -1);
  }

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
  tcase_add_test(insert, test_string_insertn);
  tcase_add_test(insert, test_string_insertn_self);
  tcase_add_test(insert, test_string_insertn_reserved);
  tcase_add_test(insert, test_string_insertn_begin);
  tcase_add_test(insert, test_string_insertn_end);
  tcase_add_test(insert, test_string_insertn_to_empty);
  tcase_add_test(insert, test_string_insertn_out_of_bonds);
  tcase_add_test(insert, test_string_insertn_zero);
  tcase_add_test(insert, test_string_insertn_neg);
  tcase_add_test(insert, test_string_inserts);
  tcase_add_test(insert, test_string_inserts_self);
  tcase_add_test(insert, test_string_inserts_reserved);
  tcase_add_test(insert, test_string_inserts_begin);
  tcase_add_test(insert, test_string_inserts_end);
  tcase_add_test(insert, test_string_inserts_empty);
  tcase_add_test(insert, test_string_inserts_to_empty);
  tcase_add_test(insert, test_string_inserts_out_of_bonds);

  TCase* insert_chars = tcase_create("tcase_insertc");
  tcase_add_test(insert, test_string_insert_chars);
  tcase_add_test(insert, test_string_insert_chars_reserved);
  tcase_add_test(insert, test_string_insert_chars_begin);
  tcase_add_test(insert, test_string_insert_chars_end);
  tcase_add_test(insert, test_string_insert_chars_zero);
  tcase_add_test(insert, test_string_insert_chars_out_of_bonds);
  tcase_add_test(insert, test_string_insert_chars_null_term);
  tcase_add_test(insert, test_string_insert_chars_eof);
  tcase_add_test(insert, test_string_insert_chars_neg);

  TCase* inserti = tcase_create("tcase_inserti");

  tcase_add_test(insert, test_string_inserti);
  tcase_add_test(insert, test_string_inserti_reserved);
  tcase_add_test(insert, test_string_inserti_begin);
  tcase_add_test(insert, test_string_inserti_end);
  tcase_add_test(insert, test_string_inserti_empty);
  tcase_add_test(insert, test_string_inserti_to_empty);
  tcase_add_test(insert, test_string_inserti_out_of_bonds);

  suite_add_tcase(suite, insert);
  suite_add_tcase(suite, insert_chars);
  suite_add_tcase(suite, inserti);
  return suite;
}
