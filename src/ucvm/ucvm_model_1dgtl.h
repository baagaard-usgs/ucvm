#ifndef UCVM_MODEL_1DGTL_H
#define UCVM_MODEL_1DGTL_H

#include <stdarg.h>
#include "ucvm_dtypes.h"

/* Create 1DGTL */
int ucvm_1dgtl_model_create(int id,
                            const char *lib_dir,
                            const char *models_path,
                            ucvm_modelconf_t *conf);

/* Initialize 1DGTL */
int ucvm_1dgtl_model_initialize();

/* Finalize 1DGTL */
int ucvm_1dgtl_model_finalize();

/* Version 1DGTL */
int ucvm_1dgtl_model_version(int id,
                             char *ver,
                             int len);

/* Version 1DGTL */
int ucvm_1dgtl_model_label(int id,
                           char *lab,
                           int len);

/* Setparam 1DGTL */
int ucvm_1dgtl_model_setparam(int id,
                              int param,
                              ...);

/* Query 1DGTL */
int ucvm_1dgtl_model_query(int id,
                           ucvm_ctype_t cmode,
                           int n,
                           ucvm_point_t *pnt,
                           ucvm_data_t *data);

/* Fill model structure with 1DGTL */
int ucvm_1dgtl_get_model(ucvm_model_t *m);

#endif
