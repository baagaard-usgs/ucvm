/**
 * Header file with data types for the plugin architecture.
 */

#if !defined(UCVM_PLUGIN_DTYPES_H)
#define UCVM_PLUGIN_DTYPES_H

typedef struct ucvm_plugin_point_t {
    double longitude;
    double latitude;
    double depth;
    double ucvm_surf_elev;
} ucvm_plugin_point_t;

typedef struct ucvm_plugin_properties_t {
    double vp;
    double vs;
    double rho;
    double qp;
    double qs;
} ucvm_plugin_properties_t;

#endif