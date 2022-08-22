#include <iostream>

#include "merge_run.hpp"

void UNIT_TESTS() {
#if 1  // +ve case, [Valid target directory & and list of archive files]
  {
    string target = "../UNIT_TEST/output";
    FILES_LIST ar_list = {"../UNIT_TEST/input/3108-01-31.tgz",
                          "../UNIT_TEST/input/3108-01-30.tgz",
                          "../UNIT_TEST/input/3108-02-08.tgz",
                          "../UNIT_TEST/input/3108-02-02.tgz",
                          "../UNIT_TEST/input/3108-02-07.tgz",
                          "../UNIT_TEST/input/3108-02-04.tgz",
                          "../UNIT_TEST/input/3108-02-05.tgz",
                          "../UNIT_TEST/input/3108-02-06.tgz",
                          "../UNIT_TEST/input/3108-02-03.tgz",
                          "../UNIT_TEST/input/3108-02-01.tgz"};
    // Call the Merge API to merge files.
    bool ret = merge_files(ar_list, target);

    if (ret == true) {
      cout << "MERGE_TEST : success (as expected)." << endl;
    } else {
      cout << "MERGE_TEST : failed." << endl;
    }
  }
#endif

#if 0 // -ve case, wrong file name.
  {
    string target = "../UNIT_TEST/output";
    FILES_LIST ar_list = {"../UNIT_TEST/input/3108-01-30.tgz",
                          "../UNIT_TEST/input/3108-01-31.tgz",
                          "../UNIT_TEST/input/3108-02-01.tgz",
                          "../UNIT_TEST/input/3108-02-02xxx.tgz",
                          "../UNIT_TEST/input/3108-02-03.tgz",
                          "../UNIT_TEST/input/3108-02-04.tgz",
                          "../UNIT_TEST/input/3108-02-05.tgz",
                          "../UNIT_TEST/input/3108-02-06yyy.tgz",
                          "../UNIT_TEST/input/3108-02-07.tgz",
                          "../UNIT_TEST/input/3108-02-08zzz.tgz"};

    bool ret = merge_files(ar_list, target);

    if (ret == false) {
      cout << "MERGE_TEST : failed (as expected)." << endl;
    } else {
      cout << "MERGE_TEST : success (not expected)." << endl;
    }
  }
#endif

#if 0  // -ve case, wrong output directory.
  {
    string target = "../UNIT_TEST/outputxxx";
    FILES_LIST ar_list = {"../UNIT_TEST/input/3108-01-30.tgz",
                          "../UNIT_TEST/input/3108-01-31.tgz",
                          "../UNIT_TEST/input/3108-02-01.tgz",
                          "../UNIT_TEST/input/3108-02-02xxx.tgz",
                          "../UNIT_TEST/input/3108-02-03.tgz",
                          "../UNIT_TEST/input/3108-02-04.tgz",
                          "../UNIT_TEST/input/3108-02-05.tgz",
                          "../UNIT_TEST/input/3108-02-06yyy.tgz",
                          "../UNIT_TEST/input/3108-02-07.tgz",
                          "../UNIT_TEST/input/3108-02-08zzz.tgz"};

    bool ret = merge_files(ar_list, target);

    if (ret == false) {
      cout << "MERGE_TEST : failed (as expected)." << endl;
    } else {
      cout << "MERGE_TEST : success (not expected)." << endl;
    }
  }
#endif
}

int main() {
  UNIT_TESTS();

  return (0);
}
