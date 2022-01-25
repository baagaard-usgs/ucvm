#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <getopt.h>
#include "test_defs.h"
#include "unittest_suite_lib.h"

int
main (int argc,
      char *argv[]) {
    char *xmldir = NULL;
    int err = UCVM_CODE_SUCCESS;

    if (argc == 2) {
        xmldir = argv[1];
    }

    /* Run test suites */
    err |= suite_lib(xmldir);

    return err;
}
