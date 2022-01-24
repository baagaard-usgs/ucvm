#if !defined(UCVM_MODEL_1D_H)
#define UCVM_MODEL_1D_H

#include <stdarg.h>
#include "ucvm_dtypes.h"

/* Create 1D */
int ucvm_1d_model_create(int id,
                         const char *lib_dir,
                         const char *models_path,
                         ucvm_modelconf_t *conf);

/* Initialize 1D */
int ucvm_1d_model_initialize();

/* Finalize 1D */
int ucvm_1d_model_finalize();

/* Version 1D */
int ucvm_1d_model_version(int id,
                          char *ver,
                          int len);

/* Label 1D */
int ucvm_1d_model_label(int id,
                        char *lab,
                        int len);

/* Setparam 1D */
int ucvm_1d_model_set_parameter(int id,
                                const char *name,
                                const char *value);

/* Query 1D */
int ucvm_1d_model_query(int id,
                        ucvm_ctype_t cmode,
                        int n,
                        ucvm_point_t *pnt,
                        ucvm_data_t *data,
                        ucvm_query_flags_t *qflags);

/* Fill model structure with 1D */
int ucvm_1d_get_model(ucvm_model_t *m);

#endif
