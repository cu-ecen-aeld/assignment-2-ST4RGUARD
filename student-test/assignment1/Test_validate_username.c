/* clang-format off */
#include "../../assignment-autotest/Unity/src/unity.h"
#include "string.h"
#include "../../assignment-autotest/test/assignment1/username-from-conf-file.h"
#include "../../examples/autotest-validate/autotest-validate.h"
/* clang-format on */
#include <stdbool.h>
#include <stdlib.h>

void test_validate_my_username() {
  /**
   * TODO: Replace the line below with your code here as described above to
   * verify your /conf/username.txt config file and my_username() functions are
   * setup properly
   *
   */
  TEST_ASSERT_EQUAL_STRING_MESSAGE(
      malloc_username_from_conf_file(), my_username(),
      "Username from my_username() should match /conf/username.txt");
}
