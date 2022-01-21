/**
 * @file ucvm_model_plugin.h
 * @brief Include file for any model which supports the plugin architecture.
 * @author David Gill - SCEC <davidgil@usc.edu>
 * @version 1.0
 *
 * @section DESCRIPTION
 *
 * Header file for the new plugin architecture for all new CVMs. Reduces
 * the necessity to compile the models with UCVM. All models must take
 * input latitudes and longitudes in WGS84 format and return material
 * properties.
 *
 */

#ifndef UCVM_MODEL_PLUGIN_H
#define UCVM_MODEL_PLUGIN_H

// Includes
#include "ucvm_dtypes.h"
#include "ucvm_plugin_dtypes.h"

// Defines
#define MODEL_POINT_BUFFER  1000

typedef struct ucvm_plugin_model_t {
    int model_id;
    ucvm_modelconf_t model_conf;

    /* Functions implemented by plugin. */
    int (*model_create)(const char *dir,
                        const char *label);
    int (*model_initialize)();
    int (*model_finalize)();
    int (*model_version)(char *ver,
                         int len);
    int (*model_set_parameter)(const char* name,
                               const char* value);
    int (*model_query)(ucvm_plugin_point_t *points,
                       ucvm_plugin_properties_t *data,
                       int numpoints);
} ucvm_plugin_model_t;

ucvm_plugin_model_t *get_plugin_by_label(char *);

ucvm_plugin_model_t *get_plugin_by_id(int);

ucvm_plugin_model_t *get_plugin_by_order(int);

typedef int (*MC_FNPTR)(const char *,
                        const char *);
typedef int (*MI_FNPTR)();
typedef int (*MF_FNPTR)();
typedef int (*MV_FNPTR)(char *,
                        int);
typedef int (*MP_FNPTR)(const char *,
                        const char *);
typedef int (*MQ_FNPTR)(ucvm_plugin_point_t *,
                        ucvm_plugin_properties_t *,
                        int);

// UCVM API Required Functions

/** Creates the model. */
int ucvm_plugin_model_create(int id,
                             const char *lib_dir,
                             const char *modesl_dir,
                             ucvm_modelconf_t *conf);

/** Opens model and sets parameters. */
int ucvm_plugin_model_initialize();

/** Cleans up memory, closes model. */
int ucvm_plugin_model_finalize();

/** Retrieves the version of model that we are using. */
int ucvm_plugin_model_version(int id,
                              char *ver,
                              int len);

/** Retrieves the label for model. */
int ucvm_plugin_model_label(int id,
                            char *lab,
                            int len);

/** Sets user parameters. */
int ucvm_plugin_model_setparam(int id,
                               int param,
                               ...);

/** Queries the model. */
int ucvm_plugin_model_query(int id,
                            ucvm_ctype_t cmode,
                            int n,
                            ucvm_point_t *pnt,
                            ucvm_data_t *data);

/** Sets the model interface information. */
int ucvm_plugin_get_model(const char *lib_dir,
                          const char *models_dir,
                          const char *label,
                          ucvm_model_t *m);

#endif
