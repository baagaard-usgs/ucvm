#include "ucvm_dtypes.h"
#include "ucvm_plugin_dtypes.h"

#include "cvmh/vx_sub.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

#define MIN(X, Y) (((X) < (Y)) ? (X) : (Y))

/* VX no data value */
#define VX_NO_DATA -99999.0

typedef struct cvmh_params_t {
    int force_depth_above_surf;
} cvmh_params_t;

// UCVM API required Functions

#if defined(BUILD_SHARED_LIBRARY)

/** Initializes the model */
int ucvmapi_model_create(const char *dir,
                         const char *label);

/** Initialize the model. */
int ucvmapi_model_initialize();

/** Cleans up the model (frees memory, etc.) */
int ucvmapi_model_finalize();

/** Returns version information */
int ucvmapi_model_version(char *ver,
                          int len);

/* Set model user parameter */
int ucvmapi_model_set_param(const char* name,
                            const char* value);

/** Queries the model */
int ucvmapi_model_query(ucvm_plugin_point_t *points,
                        ucvm_plugin_properties_t *data,
                        int numpts);

#endif

// CVM-H functions

/** Create the model */
int cvmh_create(const char *dir,
                const char *label);

/** Create user parameters with default values */
int cvmh_create_params();

/** Initialize the model. */
int cvmh_initialize();

/** Cleans up the model (frees memory, etc.) */
int cvmh_finalize();

/** Returns version information */
int cvmh_version(char *ver,
                 int len);

/* Set model user parameter */
int cvmh_set_param(const char* name,
                   const char* value);

/** Queries the model */
int cvmh_query(ucvm_plugin_point_t *points,
               ucvm_plugin_properties_t *data,
               int numpts);

cvmh_params_t *cvmh_params = NULL;

/**
 * Create CVM-H model.
 *
 * @param[in] models_dir Directory containing UCVM models.
 * @param[in] label UCVM label for CVM-H model.
 * @returns UCVM_CODE_SUCCESS if successful, UCVM_CODE_ERROR otherwise.
 */
int
cvmh_create(const char *models_dir,
            const char* label) {
    char model_path[UCVM_MAX_PATH_LEN];

    if ((models_dir == NULL) || (strlen(models_dir) == 0)) {
        fprintf(stderr, "No config path defined for model `%s`\n", label);
        return (UCVM_CODE_ERROR);
    }
    snprintf(model_path, UCVM_MAX_PATH_LEN, "%s/%s", models_dir, label);

    /* Init vx */
    if (vx_setup(model_path) != 0) {
        return (UCVM_CODE_ERROR);
    }

    cvmh_create_params();

    return (UCVM_CODE_SUCCESS);
}


/**
 * Create CVM-H parameters and populate with default values.
 *
 * @returns UCVM_CODE_SUCCESS if successful, UCVM_CODE_ERROR otherwise.
 */
int
cvmh_create_params(void) {
    if (cvmh_params) {
        free(cvmh_params);
        cvmh_params = NULL;
    }
    cvmh_params = malloc(sizeof(cvmh_params_t));
    if (!cvmh_params) {
        fprintf(stderr, "Could not create CMV-H user parameters.");
        return (UCVM_CODE_ERROR);
    }

    cvmh_params->force_depth_above_surf = 0;

    return (UCVM_CODE_SUCCESS);
}


/**
 * Initialize CVM-H model.
 *
 * @returns UCVM_CODE_SUCCESS if successful, UCVM_CODE_ERROR otherwise.
 */
int
cvmh_initialize() {
    return (UCVM_CODE_SUCCESS);
}


/**
 * Finalize CVM-H model.
 *
 * @returns UCVM_CODE_SUCCESS if successful, UCVM_CODE_ERROR otherwise.
 */
int
cvmh_finalize() {
    if (cvmh_params) {
        free(cvmh_params);
        cvmh_params = NULL;
    }
#if defined(_UCVM_MODEL_CVMH_11_2_0)
    /* Cleanup not available */
#else
    vx_cleanup();
#endif
    return (UCVM_CODE_SUCCESS);
}


/**
 * Get version information for CVM-H model.
 *
 * @param[out] ver Version string.
 * @param[in] len Maximum length of the version string.
 * @returns UCVM_CODE_SUCCESS if successful, UCVM_CODE_ERROR otherwise.
 */
int
cvmh_version(char *ver,
             int len) {
    char vxver[512];
    int verlen = 0;

    vx_version(vxver);
    verlen = strlen(vxver);
    verlen = MIN(verlen, len-1);
    memset(ver, 0, len);
    strncpy(ver, vxver, verlen);
    return (UCVM_CODE_SUCCESS);
}


/**
 * Set model parameter.
 *
 * @param[in] name Name of parameter.
 * @param[in] value Value of parameter.
 */
int
cvmh_set_param(const char *name,
               const char *value) {
    assert(cvmh_params);

    if (strcasecmp(name, "FORCE_DEPTH_ABOVE_SURF") == 0) {
        cvmh_params->force_depth_above_surf = strcasecmp(value, "true") == 0 ? 1 : 0;
    } else if (strcasecmp(name, "USE_1D_BKG") == 0) {
        if (strcasecmp(value, "true") == 0) {
            /* Register SCEC 1D background model */
            vx_register_scec();
        } else {
            /* Disable background model */
            vx_register_bkg(NULL);
        }
    } else if (strcmp(name, "USE_GTL") == 0) {
#if defined(_UCVM_MODEL_CVMH_11_2_0)
        /* GTL Toggle not available */
        fprintf(stderr, "CVM-H flag '%s' not supported in 11.2.0\n", pstr);
        return (UCVM_CODE_ERROR);
#else
        if (strcasecmp(value, "True") == 0) {
            vx_setgtl(1);
        } else {
            vx_setgtl(0);
        }
#endif
    }

    return (UCVM_CODE_SUCCESS);
}


/* Query CVM-H */
int
cvmh_query(ucvm_plugin_point_t *points,
           ucvm_plugin_properties_t *data,
           int numpoints) {
    int i;
    vx_entry_t entry;
    float vx_surf;
    int datagap = 0;

    entry.coor_type = VX_COORD_GEO;
    vx_setzmode(VX_ZMODE_DEPTH); /* Plugin interface uses depth for vertical coordinate */

    for (i = 0; i < numpoints; i++) {
        entry.coor[0] = points[i].longitude;
        entry.coor[1] = points[i].latitude;
        entry.coor[2] = points[i].depth;

        /* Force depth mode if directed and point is above surface */
        if ((cvmh_params->force_depth_above_surf) && (points[i].depth < 0.0)) {
            entry.coor[2] = 0.0;
        } // if

        /* Query CVM-H for the point */
        vx_getcoord(&entry);

        if (entry.data_src != VX_SRC_NR) {
            if (entry.vp > 0.0) {
                data[i].vp = entry.vp;
            }
            if (entry.vs > 0.0) {
                data[i].vs = entry.vs;
            }
            if (entry.rho > 0.0) {
                data[i].rho = entry.rho;
            }
        } else {
            datagap = 1;
        }
    }

    return (UCVM_CODE_SUCCESS);
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
    return cvmh_create(dir, label);
}


/**
 * Initialize function loaded and called by the UCVM library.
 *
 * @return CCA_CODE_SUCCESS or CCA_CODE_ERROR.
 */
int
ucvmapi_model_initialize() {
    return cvmh_initialize();
}


/**
 * Finalize function loaded and called by the UCVM library.
 *
 * @return CCA_CODE_SUCCESS or CCA_CODE_ERROR.
 */
int
ucvmapi_model_finalize() {
    return cvmh_finalize();
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
    return cvmh_version(ver, len);
}


/**
 * Set model parameter.
 *
 * @param ver Version string to return.
 * @param len Maximum length of buffer.
 * @return CCA_CODE_SUCCESS or CCA_CODE_ERROR.
 */
int
ucvmapi_model_set_param(const char *name,
                        const char *value) {
    return cvmh_set_param(name, value);
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
                    int numpoints) {
    return cvmh_query(points, data, numpoints);
}


#endif
