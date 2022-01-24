#if !defined(UCVM_MODEL_ELYGTL_H)
#define UCVM_MODEL_ELYGTL_H

#include <stdarg.h>
#include "ucvm_dtypes.h"

/* Create ELY */
int ucvm_elygtl_model_create(int id,
                             const char *lib_dir,
                             const char *models_dir,
                             ucvm_modelconf_t *conf);

/* Initialize ELY */
int ucvm_elygtl_model_initialize();

/* Finalize ELY */
int ucvm_elygtl_model_finalize();

/* Version ELY */
int ucvm_elygtl_model_version(int id,
                              char *ver,
                              int len);

/* Label ELY */
int ucvm_elygtl_model_version(int id,
                              char *lab,
                              int len);

/* Setparam ELY */
int ucvm_elygtl_model_set_parameter(int id,
                                    const char* name,
                                    const char *value);

/* Query ELY */
int ucvm_elygtl_model_query(int id,
                            ucvm_ctype_t cmode,
                            int n,
                            ucvm_point_t *pnt,
                            ucvm_data_t *data,
                            ucvm_query_flags_t *qflags);

/* Fill model structure with ELY */
int ucvm_elygtl_get_model(ucvm_model_t *m);

#endif
