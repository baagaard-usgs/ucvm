# GNU Automake config

AM_CPPFLAGS = -I$(top_srcdir)/src/ucvm

if BUILD_SHARED_LIBRARY
AM_CFLAGS = -DBUILD_SHARED_LIBRARY -DSHARED_LIBRARY_EXT=\"$(SHARED_LIBRARY_EXT)\"
endif

lib_LTLIBRARIES =


if ENABLE_MODEL_CVMH
lib_LTLIBRARIES += libcvmh.la
libcvmh_la_SOURCES = ucvm_adapter_cvmh.c
libcvmh_la_LIBADD = -lvxapi
libcvmh_la_LIBADD += $(PROJ_LDFLAGS)
libcvmh_la_CPPFLAGS = $(AM_CPPFLAGS) $(PROJ_INCLUDES)
endif

if ENABLE_MODEL_CENCALVM
lib_LTLIBRARIES += libusgs_cencalvm.la
libusgs_cencalvm_la_SOURCES = ucvm_adapter_cencalvm.c
libusgs_cencalvm_la_LIBADD = -lcencalvm
libusgs_cencalvm_la_LIBADD = $(ETREE_LDFLAGS) $(PROJ_LDFLAGS)
libusgs_cencalvm_la_CPPFLAGS = $(AM_CPPFLAGS) $(ETREE_INCLUDES) $(PROJ_INCLUDES)
endif


# End of file
