#include "ucvm_utils.h"
#include "ucvm_dtypes.h"
#include "ucvm_plugin_dtypes.h"
#include "cencalvm/query/cvmquery.h"
#include "cencalvm/query/cvmerror.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

/* CenCal no data value */
#define CENCALVM_NO_DATA -99999.0

/* Number of values in CenCalVM query output */
#define NUM_VALUES_OUT 9

/* Constants used in surface calculations */
/* Probably version dependent */
#define CENCALVM_MODEL_BOTTOM -45000.0
#define CENCALVM_HR_OCTANT_HEIGHT 100.0
#define CENCALVM_DEM_ACCURACY 1.0

typedef struct cencalvm_params_t {
    int enable_squashing;
    double squash_min_elev;
    int cache_size;
    char model_dir[UCVM_MAX_PATH_LEN];
    char filename_detailed[UCVM_MAX_PATH_LEN];
    char filename_regional[UCVM_MAX_PATH_LEN];
    int enable_regional;
} cencalvm_params_t;

// UCVM API required Functions

#if defined(BUILD_SHARED_LIBRARY)

/** Creates the model */
int ucvmapi_model_create(const char *models_dir,
                         const char *label);

/** Initialize model */
int ucvmapi_model_initialize(void);

/** Cleans up the model (frees memory, etc.) */
int ucvmapi_model_finalize(void);

/** Returns version information */
int ucvmapi_model_version(char *ver,
                          int len);

/* Set model user parameter */
int ucvmapi_model_set_parameter(const char* name,
                                const char* value);

/** Queries the model */
int ucvmapi_model_query(ucvm_plugin_point_t *points,
                        ucvm_plugin_properties_t *data,
                        int numpts,
                        ucvm_query_flags_t *qflags);

#endif

// USGS CenCalVM functinos

/** Creates the model */
int usgs_cencalvm_create(const char *models_dir,
                         const char *label);

/** Initializes the model */
int usgs_cencalvm_initialize(void);

/** Create user parameters with default values */
int usgs_cencalvm_create_params(void);

/** Cleans up the model (frees memory, etc.) */
int usgs_cencalvm_finalize(void);

/** Returns version information */
int usgs_cencalvm_version(char *ver,
                          int len);

/* Set model user parameter */
int usgs_cencalvm_set_parameter(const char* name,
                                const char* value);

/** Queries the model */
int usgs_cencalvm_query(ucvm_plugin_point_t *points,
                        ucvm_plugin_properties_t *data,
                        int numpts,
                        ucvm_query_flags_t *qflags);

/* Local variables */

void *query = NULL;
void *error_handler = NULL;
cencalvm_params_t *cencalvm_params = NULL;

/* CenCal return value buffer */
double *output_buffer = NULL;

/**
 * Creates the CenCalVM model.
 *
 * @param[in] models_dir Directory containing UCVM models.
 * @param[in] label UCVM label for CVM-H model.
 * @returns UCVM_CODE_SUCCESS if successful, UCVM_CODE_ERROR otherwise.
 */
int
usgs_cencalvm_create(const char *models_dir,
                     const char *label) {
    if ((models_dir == NULL) || (strlen(models_dir) == 0)) {
        fprintf(stderr, "No models directory path defined for model `%s`\n", label);
        return UCVM_CODE_ERROR;
    }

    query = cencalvm_createQuery();
    if (query == NULL) {
        fprintf(stderr, "Could not create query.\n");
        return UCVM_CODE_ERROR;
    }

    error_handler = cencalvm_errorHandler(query);
    if (error_handler == NULL) {
        fprintf(stderr, "Could not get handle to error handler.\n");
        return UCVM_CODE_ERROR;
    }

    usgs_cencalvm_create_params();
    snprintf(cencalvm_params->model_dir, UCVM_MAX_PATH_LEN, "%s/%s", models_dir, label);

    return UCVM_CODE_SUCCESS;
}


/**
 * Initialize the CenCalVM model.
 *
 * @returns UCVM_CODE_SUCCESS if successful, UCVM_CODE_ERROR otherwise.
 */
int
usgs_cencalvm_initialize(void) {
    char detailed_fullpath[UCVM_MAX_PATH_LEN];
    char regional_fullpath[UCVM_MAX_PATH_LEN];

    /* Set names of model databases */
    snprintf(detailed_fullpath, UCVM_MAX_PATH_LEN, "%s/%s", cencalvm_params->model_dir,
             cencalvm_params->filename_detailed);
    if (cencalvm_filename(query, detailed_fullpath) != 0) {
        fprintf(stderr, "%s\n", cencalvm_error_message(error_handler));
        return UCVM_CODE_ERROR;
    }
    if (cencalvm_params->enable_regional) {
        snprintf(regional_fullpath, UCVM_MAX_PATH_LEN, "%s/%s", cencalvm_params->model_dir,
                 cencalvm_params->filename_regional);
        if (cencalvm_filenameExt(query, regional_fullpath) != 0) {
            fprintf(stderr, "%s\n", cencalvm_error_message(error_handler));
            return UCVM_CODE_ERROR;
        }
    }

    /* Set cache size */
    if (cencalvm_cacheSize(query, cencalvm_params->cache_size) != 0) {
        fprintf(stderr, "%s\n", cencalvm_error_message(error_handler));
        return UCVM_CODE_ERROR;
    }
    if (cencalvm_cacheSizeExt(query, cencalvm_params->cache_size) != 0) {
        fprintf(stderr, "%s\n", cencalvm_error_message(error_handler));
        return UCVM_CODE_ERROR;
    }

    /* Open database for querying */
    if (cencalvm_open(query) != 0) {
        fprintf(stderr, "%s\n", cencalvm_error_message(error_handler));
        return UCVM_CODE_ERROR;
    }

    /* Set query type to maximum resolution */
    cencalvm_queryType(query, 0);

    /* Create buffer to hold values returned in queries */
    output_buffer = (double*) malloc(sizeof(double)*NUM_VALUES_OUT);
    if (output_buffer == NULL) {
        return UCVM_CODE_ERROR;
    }

    return UCVM_CODE_SUCCESS;
}


/**
 * Create CenCalVM parameters and populate with default values.
 *
 * @returns UCVM_CODE_SUCCESS if successful, UCVM_CODE_ERROR otherwise.
 */
int
usgs_cencalvm_create_params(void) {
    if (cencalvm_params) {
        free(cencalvm_params);
        cencalvm_params = NULL;
    }
    cencalvm_params = malloc(sizeof(cencalvm_params_t));
    if (!cencalvm_params) {
        fprintf(stderr, "Could not create CenCalVM user parameters.");
        return UCVM_CODE_ERROR;
    }

    /* Set default values. */
    cencalvm_params->enable_squashing = 0;
    cencalvm_params->squash_min_elev = -200000.0;
    cencalvm_params->cache_size = 64;
    strncpy(cencalvm_params->model_dir, "cencalvm", UCVM_MAX_PATH_LEN);
    strncpy(cencalvm_params->filename_detailed, "USGSBayAreaVM-08.3.0.etree", UCVM_MAX_PATH_LEN);
    strncpy(cencalvm_params->filename_regional, "USGSBayAreaVMExt-08.3.0.etree", UCVM_MAX_PATH_LEN);
    cencalvm_params->enable_regional = 1;

    return UCVM_CODE_SUCCESS;
}


/* Finalize CenCal */
int
usgs_cencalvm_finalize(void) {
    if (cencalvm_params) {
        free(cencalvm_params);
        cencalvm_params = NULL;
    }
    if (query) {
        cencalvm_close(query);
        cencalvm_destroyQuery(query);
        query = NULL;
    }
    if (output_buffer) {
        free(output_buffer);
        output_buffer = NULL;
    }

    return UCVM_CODE_SUCCESS;
}


/* Version Cencal */
int
usgs_cencalvm_version(char *ver,
                      int len) {
    ucvm_strcpy(ver, cencalvm_params->filename_detailed, len);
    return UCVM_CODE_SUCCESS;
}


/**
 * Set model parameter.
 *
 * @param[in] name Name of parameter.
 * @param[in] value Value of parameter.
 */
int
usgs_cencalvm_set_parametereter(const char *name,
                                const char *value) {
    assert(cencalvm_params);

    if (strcasecmp(name, "CACHE_SIZE_MB") == 0) {
        cencalvm_params->cache_size = atoi(value);
    } else if (strcasecmp(name, "FILENAME_DETAILED") == 0) {
        strncpy(cencalvm_params->filename_detailed, value, UCVM_MAX_PATH_LEN);
    } else if (strcasecmp(name, "FILENAME_REGIONAL") == 0) {
        strncpy(cencalvm_params->filename_regional, value, UCVM_MAX_PATH_LEN);
    } else if (strcasecmp(name, "ENABLE_REGIONAL") == 0) {
        cencalvm_params->enable_regional = strcasecmp(value, "true") == 0 ? 1 : 0;
#if 0
    } else if (strcasecmp(name, "ENABLE_SQUASHING") == 0) {
        cencalvm_params->enable_squashing = strcasecmp(value, "true") == 0 ? 1 : 0;
    } else if (strcasecmp(name, "SQUASHING_MAX_DEPTH") == 0) {
        cencalvm_params->squash_min_elev = atof(value);
#endif
    } else {
        fprintf(stderr, "Unknown parameter %s=%s for the CenCalVM.\n", name, value);
        return UCVM_CODE_ERROR;
    }

    return UCVM_CODE_SUCCESS;
}


/* Get elevation of free surface (ground/water interface) at point */
int
usgs_cencalvm_getsurface(double lon,
                         double lat,
                         double *surf_elev,
                         double accuracy) {
    int i;
    double elev, prevelev, startelev, endelev, resid;

    *surf_elev = CENCALVM_NO_DATA;

    for (i = 0; i < NUM_VALUES_OUT; i++) {
        output_buffer[i] = 0.0;
    }

    /* Calculate starting z for surface search */
    if (cencalvm_squash(query, 0, 0.0) != 0) {
        fprintf(stderr, "%s\n", cencalvm_error_message(error_handler));
        return UCVM_CODE_ERROR;
    }

    elev = CENCALVM_MODEL_BOTTOM;

    if (cencalvm_query(query, &output_buffer, NUM_VALUES_OUT, lon, lat, elev) != 0) {
        cencalvm_error_resetStatus(error_handler);
    } else {
        /* Set up one octant higher than reported depth wrt free surface */
        elev = elev + output_buffer[5] + CENCALVM_HR_OCTANT_HEIGHT * 2;
        prevelev = elev;

        /* Find surface estimate by stepping down in octant increments */
        while (elev >= CENCALVM_MODEL_BOTTOM) {
            if (cencalvm_query(query, &output_buffer, NUM_VALUES_OUT, lon, lat, elev) != 0) {
                cencalvm_error_resetStatus(error_handler);
            } else {
                if ((output_buffer[0] > 0.0) && (output_buffer[1] > 0.0) &&
                    (output_buffer[2] > 0.0)) {
                    /* Refine surface estimate with logarithmic search */
                    startelev = elev;
                    endelev = prevelev;
                    resid = endelev - startelev;
                    while (resid > accuracy) {
                        elev = (startelev + endelev) / 2.0;
                        if (cencalvm_query(query, &output_buffer, NUM_VALUES_OUT, lon, lat, elev) != 0) {
                            cencalvm_error_resetStatus(error_handler);
                            endelev = elev;
                        } else {
                            if ((output_buffer[0] <= 0.0) || (output_buffer[1] <= 0.0) ||
                                (output_buffer[2] <= 0.0)) {
                                endelev = elev;
                            } else {
                                startelev = elev;
                            }
                        }
                        resid = endelev - startelev;
                    }
                    elev = startelev;
                    break;
                }
            }
            prevelev = elev;
            elev = elev - CENCALVM_HR_OCTANT_HEIGHT;
        }
    }

    /* Restore original squash mode */
    if (cencalvm_squash(query, cencalvm_params->enable_squashing, cencalvm_params->squash_min_elev) != 0) {
        fprintf(stderr, "%s\n", cencalvm_error_message(error_handler));
        return UCVM_CODE_ERROR;
    }

    if (elev - CENCALVM_MODEL_BOTTOM <= 0.01) {
        return UCVM_CODE_ERROR;
    }

    *surf_elev = elev;
    return UCVM_CODE_SUCCESS;
}


/* Query CenCal */
int
usgs_cencalvm_query(ucvm_plugin_point_t *points,
                    ucvm_plugin_properties_t *data,
                    int numpoints,
                    ucvm_query_flags_t *qflags) {
    int i;
    double point_lon, point_lat, point_elev, surf_elev;
    int datagap = 0;

    /* UCVM does its own squashing */
    assert(!cencalvm_params->enable_squashing);

    for (i = 0; i < numpoints; i++) {
        point_lon = points[i].longitude;
        point_lat = points[i].latitude;
        point_elev = points[i].ucvm_surf_elev - points[i].depth;

        /* Force depth mode if directed and point is above surface */
        if (qflags && qflags->force_depth_above_surf && (points[i].depth < 0.0)) {
            if (usgs_cencalvm_getsurface(point_lon, point_lat, &surf_elev, CENCALVM_DEM_ACCURACY) == UCVM_CODE_SUCCESS) {
                /* Add small buffer to overcome surface uncertainty */
                point_elev = surf_elev - CENCALVM_DEM_ACCURACY;
            } else {
                /* Fall back to using UCVM topo surface. */
                point_elev = points[i].ucvm_surf_elev - CENCALVM_DEM_ACCURACY;
            }
        } else {
            if (usgs_cencalvm_getsurface(point_lon, point_lat, &surf_elev, CENCALVM_DEM_ACCURACY) == UCVM_CODE_SUCCESS) {
                point_elev = surf_elev - points[i].depth;
            } else {
                /* Fall back to using UCVM topo surface. */
                point_elev = points[i].ucvm_surf_elev - points[i].depth;
            }
        }

        if (cencalvm_query(query, &output_buffer, NUM_VALUES_OUT, point_lon, point_lat, point_elev) != 0) {
            datagap = 1;
            cencalvm_error_resetStatus(error_handler);
        } else {
            /* Check for model error where water found below surface */
            if ((output_buffer[0] <= 0.0) ||
                (output_buffer[1] <= 0.0) ||
                (output_buffer[2] <= 0.0)) {
                datagap = 1;
            } else {
                if (output_buffer[0] > 0.0) {
                    data[i].vp = output_buffer[0];
                }
                if (output_buffer[1] > 0.0) {
                    data[i].vs = output_buffer[1];
                }
                if (output_buffer[2] > 0.0) {
                    data[i].rho = output_buffer[2];
                }
            }
        }
    }

    if (datagap) {
        return UCVM_CODE_DATAGAP;
    }

    return UCVM_CODE_SUCCESS;
}


// The following functions are for dynamic library mode. If we are compiling
// a static library, these functions must be disabled to avoid conflicts.
#if defined(BUILD_SHARED_LIBRARY)

/**
 * Create function loaded and called by the UCVM library.
 *
 * @param dir The directory in which UCVM is installed.
 * @return CCA_CODE_SUCCESS or CCA_CODE_ERROR.
 */
int
ucvmapi_model_create(const char *dir,
                     const char *label) {
    return usgs_cencalvm_create(dir, label);
}


/**
 * Initialize function loaded and called by the UCVM library.
 *
 * @return CCA_CODE_SUCCESS or CCA_CODE_ERROR.
 */
int
ucvmapi_model_initialize(void) {
    return usgs_cencalvm_initialize();
}


/**
 * Finalize function loaded and called by the UCVM library.
 *
 * @return CCA_CODE_SUCCESS or CCA_CODE_ERROR.
 */
int
ucvmapi_model_finalize(void) {
    return usgs_cencalvm_finalize();
}


/**
 * Version function loaded and called by the UCVM library.
 *
 * @param ver Version string to return.
 * @param len Maximum length of buffer.
 * @return CCA_CODE_SUCCESS or CCA_CODE_ERROR.
 */
int
ucvmapi_model_version(char *ver,
                      int len) {
    return usgs_cencalvm_version(ver, len);
}


/**
 * Set model parameter.
 *
 * @param ver Version string to return.
 * @param len Maximum length of buffer.
 * @return CCA_CODE_SUCCESS or CCA_CODE_ERROR.
 */
int
ucvmapi_model_set_parameter(const char *name,
                            const char *value) {
    return usgs_cencalvm_set_parameter(name, value);
}


/**
 * Query function loaded and called by the UCVM library.
 *
 * @param points The basic_point_t array containing the points.
 * @param data The basic_properties_t array containing the material properties returned.
 * @param numpoints The number of points in the array.
 * @return CCA_CODE_SUCCESS or CCA_CODE_ERROR.
 */
int
ucvmapi_model_query(ucvm_plugin_point_t *points,
                    ucvm_plugin_properties_t *data,
                    int numpoints,
                    ucvm_query_flags_t *qflags) {
    return usgs_cencalvm_query(points, data, numpoints, qflags);
}


#endif
