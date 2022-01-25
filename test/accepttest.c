#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <unistd.h>
#include <getopt.h>
#include "test_defs.h"
#include "accepttest_suite_grid.h"

int
main (int argc,
      char *argv[]) {
    char *xmldir = NULL;
    int err = UCVM_CODE_SUCCESS;

    if (argc == 2) {
        xmldir = argv[1];
    }

    /* Run test suites */
    err |= suite_grid(xmldir);

    return err;
}
