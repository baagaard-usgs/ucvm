# GNU Automake config

SUBDIRS = \
	inputs

TESTS = unittest accepttest

bin_PROGRAMS = unittest accepttest

unittest_SOURCES = \
	unittest.c \
	unittest_suite_lib.c \
	test_defs.c
unittest_LDADD = $(top_builddir)/src/ucvm/libucvm.la

accepttest_SOURCES = \
	accepttest.c \
	accepttest_suite_grid.c \
	test_defs.c
accepttest_LDADD = $(top_builddir)/src/ucvm/libucvm.la

noinst_HEADERS = \
	test_defs.h \
	unittest_suite_lib.h \
	accepttest_suite_grid.h

AM_CPPFLAGS = -I$(top_srcdir)/src/ucvm
AM_CFLAGS = -DBIN_DIR=\"$(prefix)/bin\"


if ENABLE_MODEL_CENCALVM
AM_CFLAGS += -D_UCVM_ENABLE_CENCALVM
endif

if ENABLE_MODEL_CVMH
AM_CFLAGS += -D_UCVM_ENABLE_CVMH
endif

#if ENABLE_MODEL_CVMS
#AM_CFLAGS += -D_UCVM_ENABLE_CVMS
#endif

#if ENABLE_MODEL_CVMSI
#AM_CFLAGS += -D_UCVM_ENABLE_CVMSI
#endif

#if ENABLE_MODEL_IVLSU
#AM_CFLAGS += -D_UCVM_ENABLE_IVLSU
#endif

# CVLSU/COACHELLA includes
#if ENABLE_MODEL_CVLSU
#AM_CFLAGS += -D_UCVM_ENABLE_CVLSU
#endif

#if ENABLE_MODEL_ALBACORE
#AM_CFLAGS += -D_UCVM_ENABLE_ALBACORE
#endif

#if ENABLE_MODEL_CVMNCI
#AM_CFLAGS += -D_UCVM_ENABLE_CVMNCI
#endif

#if ENABLE_MODEL_WFCVM
#AM_CFLAGS += -D_UCVM_ENABLE_WFCVM
#endif

#if ENABLE_MODEL_CVMLT
#AM_CFLAGS += -D_UCVM_ENABLE_CVMLT
#endif

#if ENABLE_MODEL_CMRG
#AM_CFLAGS += -D_UCVM_ENABLE_CMRG
#endif

#if ENABLE_MODEL_TAPE
#AM_CFLAGS += -D_UCVM_ENABLE_TAPE
#endif

#if ENABLE_MODEL_CVMS5
#AM_CFLAGS += -D_UCVM_ENABLE_CVMS5
#endif

if ENABLE_MODEL_CCA
AM_CFLAGS += -D_UCVM_ENABLE_CCA
endif

#if ENABLE_MODEL_CS173
#AM_CFLAGS += -D_UCVM_ENABLE_CS173
#endif

#if ENABLE_MODEL_CS173H
#AM_CFLAGS += -D_UCVM_ENABLE_CS173H
#endif



#check: unittest accepttest
#	@( cd ${prefix}/tests; source ../conf/ucvm_env.sh; \
#		./unittest;\
#		./accepttest;\
#		./accept_test.py ${prefix}/tests;\
#	)


# End of file
