#include <check.h>
#include "tests.h"

// TODO list:
//  - more tests

int main() {
  int failed = 0;

  Suite* suites[] = {
    init_suite(),
    modification_suite(),
    operations_suite(),
    insertion_suite(),
    erasure_suite(),
    NULL
  };

  SRunner* sr = srunner_create(suites[0]);
  srunner_set_fork_status(sr, CK_NOFORK);
  for (int i = 0; suites[++i];) {
    srunner_add_suite(sr, suites[i]);
  }
  srunner_run_all(sr, CK_NORMAL);
  failed += srunner_ntests_failed(sr);
  srunner_free(sr);

  return failed == 0 ? 0 : 1;
}
