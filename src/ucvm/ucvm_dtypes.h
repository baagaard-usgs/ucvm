#if !defined(UCVM_DTYPES_H)
#define UCVM_DTYPES_H

#include "ucvm_plugin_dtypes.h"

/* Maximum number of supported models */
#define UCVM_MAX_MODELS 20

/* Maximum number of supported maps (topo + vs30) */
#define UCVM_MAX_MAPS 2

/* Maximum number of model flags */
#define UCVM_MAX_FLAGS 10

/* Maximum model label length */
#define UCVM_MAX_LABEL_LEN 64

/* Maximum model version length */
#define UCVM_MAX_VERSION_LEN 64

/* Maximum path length */
#define UCVM_MAX_PATH_LEN 256

/* Maximum projection description length */
#define UCVM_MAX_PROJ_LEN 256

/* Maximum model flag key length */
#define UCVM_MAX_FLAG_LEN 64

/* Maximum model list length */
#define UCVM_MAX_MODELLIST_LEN 1024

/* Special source model/ifunc flags */
#define UCVM_SOURCE_NONE -1
#define UCVM_SOURCE_CRUST -2
#define UCVM_SOURCE_GTL -3

/* Predefined crustal model interfaces */
#define UCVM_MODEL_NONE "none"
#define UCVM_MODEL_CVMS "cvms"
#define UCVM_MODEL_1D "1d"
#define UCVM_MODEL_BBP1D "bbp1d"
#define UCVM_MODEL_CMRG "cmrg"
#define UCVM_MODEL_CMUETREE "cmuetree"
#define UCVM_MODEL_CVMSI "cvmsi"
#define UCVM_MODEL_CVMNCI "cvmnci"
#define UCVM_MODEL_WFCVM "wfcvm"
#define UCVM_MODEL_CVMLT "cvmlt"
#define UCVM_MODEL_TAPE "tape"
#define UCVM_MODEL_JAPAN "japan"
/* plugin models */
#define UCVM_MODEL_CVMH "cvmh"
#define UCVM_MODEL_CENCALVM "usgs_cencalvm"
#define UCVM_MODEL_CVMS5 "cvms5"
#define UCVM_MODEL_IVLSU "ivlsu"
#define UCVM_MODEL_CVLSU "cvlsu"
#define UCVM_MODEL_ALBACORE "albacore"
#define UCVM_MODEL_CCA "cca"
#define UCVM_MODEL_CS173 "cs173"
#define UCVM_MODEL_CS173H "cs173h"

/* Predefined GTL model interfaces */
#define UCVM_MODEL_1DGTL "1dgtl"
#define UCVM_MODEL_ELYGTL "elygtl"

/* These model interfaces allow user defined
 * models to be declared in conf at runtime */
#define UCVM_MODEL_PATCH "model_patch"
#define UCVM_MODEL_ETREE "model_etree"

/* Predefined map interfaces */
#define UCVM_MAP_UCVM "ucvm"
#define UCVM_MAP_YONG "yong"

/* These map interfaces allow user defined
 * maps to be declared in conf at runtime */
#define UCVM_MAP_ETREE "map_etree"

/* Predefined interpolation functions */
#define UCVM_IFUNC_NONE "none"
#define UCVM_IFUNC_CRUST "crust"
#define UCVM_IFUNC_GTL "gtl"
#define UCVM_IFUNC_LINEAR "linear"
#define UCVM_IFUNC_ELY "ely"

/* Predefined projection strings */
#define UCVM_PROJ_GEO "+proj=lonlat +datum=WGS84"

/* Byte order */
typedef enum { UCVM_BYTEORDER_LSB=0,
               UCVM_BYTEORDER_MSB } ucvm_byteorder_t;

/* Supported error codes */
typedef enum { UCVM_CODE_SUCCESS=0,
               UCVM_CODE_ERROR,
               UCVM_CODE_DATAGAP,
               UCVM_CODE_NODATA } ucvm_code_t;

/* Supported coordinate modes */
typedef enum { UCVM_COORD_GEO_DEPTH=0,
               UCVM_COORD_GEO_ELEV } ucvm_ctype_t;

/* Supported model types */
typedef enum { UCVM_MODEL_CRUSTAL=0,
               UCVM_MODEL_GTL } ucvm_mtype_t;

/* Supported resource types */
typedef enum { UCVM_RESOURCE_MODEL=0,
               UCVM_RESOURCE_IFUNC,
               UCVM_RESOURCE_MAP,
               UCVM_RESOURCE_MODEL_IF,
               UCVM_RESOURCE_MAP_IF} ucvm_rtype_t;

/* Supported coordinate query modes. Used internally by UCVM */
typedef enum { UCVM_OPMODE_CRUSTAL=0,
               UCVM_OPMODE_GTL } ucvm_opmode_t;

/* Supported domains for query points. Used internally by UCVM */
typedef enum { UCVM_DOMAIN_NONE=0,
               UCVM_DOMAIN_GTL,
               UCVM_DOMAIN_INTERP,
               UCVM_DOMAIN_CRUST} ucvm_domain_t;

/* For swapping endian */
typedef union  {
    float f;
    unsigned char b[4];
} ucvm_fdata_t;

/* 3D point */
typedef struct  {
    double coord[3];
} ucvm_point_t;

/* 3D dims */
typedef struct  {
    unsigned int dim[3];
} ucvm_dim_t;

/* Material properties */
typedef struct {
    int source;
    double vp;
    double vs;
    double rho;
} ucvm_prop_t;

/* Model data */
typedef struct {
    double surf;
    double vs30;
    double depth;
    ucvm_domain_t domain;
    double shift_cr;
    double shift_gtl;
    ucvm_prop_t crust;
    ucvm_prop_t gtl;
    ucvm_prop_t cmb;
} ucvm_data_t;

/* Region box */
typedef struct  {
    ucvm_ctype_t cmode;
    double p1[3];
    double p2[3];
} ucvm_region_t;

/* Model config */
typedef struct  {
    char label[UCVM_MAX_LABEL_LEN];
    ucvm_region_t region;
} ucvm_modelconf_t;

/* Model interface specification */
typedef struct  {
    ucvm_mtype_t mtype;
    int (*create)(int id,
                  const char* lib_dir,
                  const char *models_path,
                  ucvm_modelconf_t *conf);
    int (*initialize)();
    int (*finalize)();
    int (*get_version)(int id,
                       char *ver,
                       int len);
    int (*get_label)(int id,
                     char *lab,
                     int len);
    int (*set_parameter)(int id,
                         const char* name,
                         const char* value);
    int (*query)(int id,
                 ucvm_ctype_t cmode,
                 int n,
                 ucvm_point_t *pnt,
                 ucvm_data_t *data,
                 ucvm_query_flags_t *qflags);
} ucvm_model_t;

/* Interp function */
typedef struct  {
    char label[UCVM_MAX_LABEL_LEN];
    int (*interp)(double zmin,
                  double zmax,
                  ucvm_ctype_t cmode,
                  ucvm_point_t *pnt,
                  ucvm_data_t *data);
} ucvm_ifunc_t;

/* Resource flag description */
typedef struct  {
    char key[UCVM_MAX_FLAG_LEN];
    char value[UCVM_MAX_FLAG_LEN];
} ucvm_flag_t;

/* Resource description */
typedef struct  {
    ucvm_rtype_t rtype;
    ucvm_mtype_t mtype; /* Applicable to models only */
    int active; /* Applicable to models/maps only */
    char label[UCVM_MAX_LABEL_LEN];
    char version[UCVM_MAX_VERSION_LEN];
    int numflags;
    ucvm_flag_t flags[UCVM_MAX_FLAGS]; /* Applicable to models only */
} ucvm_resource_t;

#endif
