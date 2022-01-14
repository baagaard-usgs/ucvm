# GNU Automake config

bin_PROGRAMS = ucvm_query

AM_CPPFLAGS = $(ETREE_INCLUDES) $(PROJ_INCLUDES)

lib_LTLIBRARIES = libucvm.la

pkginclude_HEADERS = \
	ucvm.h \
	ucvm_dtypes.h \
	ucvm_config.h \
	ucvm_grid.h \
	ucvm_proj_bilinear.h \
	ucvm_proj_ucvm.h \
	ucvm_meta_etree.h \
	ucvm_meta_patch.h \
	ucvm_utils.h

libucvm_la_SOURCES = \
	ucvm.c \
	ucvm_config.c \
	ucvm_grid.c \
	ucvm_proj_bilinear.c \
	ucvm_proj_ucvm.c \
	ucvm_interp.c \
	ucvm_map.c \
	ucvm_utils.c \
	ucvm_meta_etree.c \
	ucvm_meta_patch.c

# Default set of cvms to include
libucvm_la_SOURCES += \
	ucvm_model_1d.c \
	ucvm_model_1dgtl.c \
	ucvm_model_bbp1d.c \
	ucvm_model_plugin.c \
	ucvm_model_elygtl.c \
	ucvm_model_cmuetree.c

#	ucvm_model_etree.c
#	ucvm_model_patch.c

AM_CFLAGS = 

if BUILD_SHARED_LIBRARY
AM_CFLAGS += -DBUILD_SHARED_LIBRARY -DSHARED_LIBRARY_EXT=\"$(SHARED_LIBRARY_EXT)\"
endif

# CENCALVM includes
#if ENABLE_CENCAL
#AM_CFLAGS += -D_UCVM_ENABLE_CENCAL
#libucvm_la_SOURCES += ucvm_model_cencal.c
#endif

# CVM-H includes
if ENABLE_MODEL_CVMH
AM_CFLAGS += -D_UCVM_ENABLE_CVMH
libucvm_la_SOURCES += ucvm_model_cvmh.c
libucvm_la_LIBADD = -lvxapi
endif

# CVM-S4 includes
#if UCVM_AM_ENABLE_CVMS
#AM_CFLAGS += -D_UCVM_ENABLE_CVMS
#libucvm_la_SOURCES += ucvm_model_cvms.c
#endif

# IVLSU includes
#if UCVM_AM_ENABLE_IVLSU
#AM_CFLAGS += -D_UCVM_ENABLE_IVLSU
#endif

# CVLSU includes
#if UCVM_AM_ENABLE_CVLSU
#AM_CFLAGS += -D_UCVM_ENABLE_CVLSU
#endif

# ALBACORE includes
#if UCVM_AM_ENABLE_ALBACORE
#AM_CFLAGS += -D_UCVM_ENABLE_ALBACORE
#endif

# CVM-S5 includes
#if UCVM_AM_ENABLE_CVMS5
#AM_CFLAGS += -D_UCVM_ENABLE_CVMS5
#endif

# CCA includes
if ENABLE_MODEL_CCA
AM_CFLAGS += -D_UCVM_ENABLE_CCA
endif

# CS173 includes
#if UCVM_AM_ENABLE_CS173
#AM_CFLAGS += -D_UCVM_ENABLE_CS173
#endif

# CS173H includes
#if UCVM_AM_ENABLE_CS173H
#AM_CFLAGS += -D_UCVM_ENABLE_CS173H
#endif

# CVM-SI includes
#if UCVM_AM_ENABLE_CVMSI
#AM_CFLAGS += -D_UCVM_ENABLE_CVMSI
#libucvm_la_SOURCES += ucvm_model_cvmsi.c
#endif

# CVM-NCI includes
#if UCVM_AM_ENABLE_CVMNCI
#AM_CFLAGS += -D_UCVM_ENABLE_CVMNCI
#libucvm_la_SOURCES += ucvm_model_cvmnci.c
#endif

# WFCVM includes
#if UCVM_AM_ENABLE_WFCVM
#AM_CFLAGS += -D_UCVM_ENABLE_WFCVM
#libucvm_la_SOURCES += ucvm_model_wfcvm.c
#endif

# CVMLT includes
#if UCVM_AM_ENABLE_CVMLT
#AM_CFLAGS += -D_UCVM_ENABLE_CVMLT
#libucvm_la_SOURCES += ucvm_model_cvmlt.c
#endif

# CMRG includes
#if UCVM_AM_ENABLE_CMRG
#AM_CFLAGS += -D_UCVM_ENABLE_CMRG
#libucvm_la_SOURCES += ucvm_model_cmrg.c
#endif

# TAPE includes
#if UCVM_AM_ENABLE_TAPE
#AM_CFLAGS += -D_UCVM_ENABLE_TAPE
#libucvm_la_SOURCES += ucvm_model_tape.c
#endif

libucvm_la_LDFLAGS = $(AM_LDFLAGS) $(ETREE_LDFLAGS) $(PROJ_LDFLAGS)

ucvm_query_SOURCES = ucvm_query.c
ucvm_query_LDADD = libucvm.la



# End of file
