#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <unistd.h>
#include "test_defs.h"
#include "accepttest_suite_grid.h"

int
test_grid_tool_1d() {
    char infile[MAX_STRING_LEN];
    char outfile[MAX_STRING_LEN];
    char reffile[MAX_STRING_LEN];
    char currentdir[MAX_STRING_LEN];

    printf("Test: ucvm_query 1d model w/ large grid\n");

    /* Save current directory */
    getcwd(currentdir, MAX_STRING_LEN);

    snprintf(infile, MAX_STRING_LEN-1, "%s/inputs/%s", currentdir, "test-grid.in");
    snprintf(outfile, MAX_STRING_LEN-1, "%s/%s", currentdir, "test-grid-ucvm_query-1d.out");
    snprintf(reffile, MAX_STRING_LEN-1, "%s/ref/%s", currentdir, "test-grid-lib-1d.ref");

    if (test_assert_int(run_ucvm_query(BIN_DIR,
                                       "../conf/ucvm.conf",
                                       UCVM_MODEL_1D, "ucvm",
                                       infile, outfile),
                        0) != 0) {
        fprintf(stderr, "FAIL: ucvm_query failure\n");
        return UCVM_CODE_ERROR;
    }

    /* Perform diff btw outfile and ref */
    if (test_assert_file(outfile, reffile) != 0) {
        return UCVM_CODE_ERROR;
    }

    unlink(outfile);

    printf("PASS\n");
    return UCVM_CODE_SUCCESS;
}


int
test_grid_lib_1d() {
    ucvm_point_t *pnts;
    ucvm_data_t *data, *refdata;
    int i, num_pnts, num_data;
    char infile[MAX_STRING_LEN];
    char outfile[MAX_STRING_LEN];
    char reffile[MAX_STRING_LEN];
    char currentdir[MAX_STRING_LEN];

    printf("Test: ucvm library 1d model w/ large grid\n");

    /* Allocate buffers */
    pnts = malloc(MAX_POINTS * sizeof(ucvm_point_t));
    if (pnts == NULL) {
        fprintf(stderr, "FAIL: Failed to allocate point memory\n");
        return UCVM_CODE_ERROR;
    }
    data = malloc(MAX_POINTS * sizeof(ucvm_data_t));
    if (data == NULL) {
        fprintf(stderr, "FAIL: Failed to allocate data memory\n");
        return UCVM_CODE_ERROR;
    }
    refdata = malloc(MAX_POINTS * sizeof(ucvm_data_t));
    if (refdata == NULL) {
        fprintf(stderr, "FAIL: Failed to allocate refdata memory\n");
        return UCVM_CODE_ERROR;
    }

    snprintf(infile, MAX_STRING_LEN-1, "inputs/%s", "test-grid.in");
    snprintf(outfile, MAX_STRING_LEN-1, "%s", "test-grid-lib-1d.out");
    snprintf(reffile, MAX_STRING_LEN-1, "ref/%s", "test-grid-lib-1d.ref");

    /* Read in grid points */
    if (read_points(infile, MAX_POINTS, pnts, &num_pnts) != 0) {
        fprintf(stderr, "FAIL: Failed to read points from input grid file\n");
        free(pnts);
        free(data);
        return UCVM_CODE_ERROR;
    }

    /* Read in reference data */
    if (read_data(reffile, MAX_POINTS, refdata, &num_data) != 0) {
        fprintf(stderr, "FAIL: Failed to read points from refernce grid file\n");
        free(pnts);
        free(data);
        return UCVM_CODE_ERROR;
    }

    if (test_assert_int(num_pnts, num_data) != 0) {
        fprintf(stderr, "FAIL: Num points and num data are unequal\n");
        free(pnts);
        free(data);
        return UCVM_CODE_ERROR;
    }

    /* Setup UCVM */
    if (ucvm_init("../conf/ucvm.conf") != UCVM_CODE_SUCCESS) {
        fprintf(stderr, "FAIL: Failed to initialize UCVM API\n");
        free(pnts);
        free(data);
        return UCVM_CODE_ERROR;
    }
    if (ucvm_add_model_bylist(UCVM_MODEL_1D) != UCVM_CODE_SUCCESS) {
        fprintf(stderr, "FAIL: Failed to enable model\n");
        free(pnts);
        free(data);
        return UCVM_CODE_ERROR;
    }

    /* Query UCVM */
    if (ucvm_query(num_pnts, pnts, data) != UCVM_CODE_SUCCESS) {
        fprintf(stderr, "FAIL: Query CVM failed\n");
        free(pnts);
        free(data);
        return UCVM_CODE_ERROR;
    }

    /* Write out new data -- optional
     * if (write_data(outfile, num_pnts, data, pnts, "1d","none","crust") != 0) {
     * fprintf(stderr, "FAIL: Failed to write points to grid file\n");
     * free(pnts);
     * free(data);
     * return(1);
     * }
     */

    /* Compare query and reference data */
    for (i = 0; i < num_pnts; i++) {
        if ((test_assert_double(data[i].surf, refdata[i].surf) != 0) ||
            (test_assert_double(data[i].vs30, refdata[i].vs30) != 0) ||
            (test_assert_double(data[i].cmb.vp, refdata[i].cmb.vp) != 0) ||
            (test_assert_double(data[i].cmb.vs, refdata[i].cmb.vs) != 0) ||
            (test_assert_double(data[i].cmb.rho, refdata[i].cmb.rho) != 0)) {
            fprintf(stderr, "FAIL: Mismatch on line %d\n", i);
            free(pnts);
            free(data);
            return UCVM_CODE_ERROR;
        }
    }

    free(pnts);
    free(data);
    free(refdata);

    /* Finalize UCVM */
    ucvm_finalize();

    printf("PASS\n");
    return UCVM_CODE_SUCCESS;
}


int
suite_grid(const char *xmldir) {
    test_suite_t suite;
    char logfile[256];
    int err = UCVM_CODE_SUCCESS;
    FILE *lf = NULL;

    /* Setup test suite */
    strcpy(suite.suite_name, "suite_grid");
    suite.num_tests = 1;
    suite.tests = malloc(suite.num_tests * sizeof(test_info_t));
    if (suite.tests == NULL) {
        fprintf(stderr, "Failed to alloc test structure\n");
        return UCVM_CODE_ERROR;
    }
    test_get_time(&suite.exec_time);

    /* Setup test cases */
    strcpy(suite.tests[0].test_name, "test_grid_lib_1d");
    suite.tests[0].test_func = &test_grid_lib_1d;
    suite.tests[0].elapsed_time = 0.0;

    /*** this is being tested via accept_test.py
     * strcpy(suite.tests[1].test_name, "test_grid_tool_1d");
     * suite.tests[1].test_func = &test_grid_tool_1d;
     * suite.tests[1].elapsed_time = 0.0;
     ***/

    err = test_run_suite(&suite);

    if (xmldir != NULL) {
        sprintf(logfile, "%s/%s.xml", xmldir, suite.suite_name);
        lf = init_log(logfile);
        if (lf == NULL) {
            fprintf(stderr, "Failed to initialize logfile\n");
            return UCVM_CODE_ERROR;
        }

        if (write_log(lf, &suite) != 0) {
            fprintf(stderr, "Failed to write test log\n");
            return UCVM_CODE_ERROR;
        }

        close_log(lf);
    }

    free(suite.tests);

    return err;
}
