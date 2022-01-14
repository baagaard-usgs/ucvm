# GNU Automake config

SUBDIRS = \
	inputs \
	ref

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


# CENCALVM includes
if UCVM_AM_ENABLE_CENCAL
AM_CFLAGS += -D_UCVM_ENABLE_CENCAL
endif

# CVM-H includes
if UCVM_AM_ENABLE_CVMH
AM_CFLAGS += -D_UCVM_ENABLE_CVMH
endif

# CVM-S4 includes
if UCVM_AM_ENABLE_CVMS
AM_CFLAGS += -D_UCVM_ENABLE_CVMS
endif

# CVM-SI includes
if UCVM_AM_ENABLE_CVMSI
AM_CFLAGS += -D_UCVM_ENABLE_CVMSI
endif

# IVLSUIMPERIAL includes
if UCVM_AM_ENABLE_IVLSU
AM_CFLAGS += -D_UCVM_ENABLE_IVLSU
endif

# CVLSU/COACHELLA includes
if UCVM_AM_ENABLE_CVLSU
AM_CFLAGS += -D_UCVM_ENABLE_CVLSU
endif

# ALBACORE includes
if UCVM_AM_ENABLE_ALBACORE
AM_CFLAGS += -D_UCVM_ENABLE_ALBACORE
endif

# CVM-NCI includes
if UCVM_AM_ENABLE_CVMNCI
AM_CFLAGS += -D_UCVM_ENABLE_CVMNCI
endif

# WFCVM includes
if UCVM_AM_ENABLE_WFCVM
AM_CFLAGS += -D_UCVM_ENABLE_WFCVM
endif

# CVMLT includes
if UCVM_AM_ENABLE_CVMLT
AM_CFLAGS += -D_UCVM_ENABLE_CVMLT
endif

# CMRG includes
if UCVM_AM_ENABLE_CMRG
AM_CFLAGS += -D_UCVM_ENABLE_CMRG
endif

# TAPE includes
if UCVM_AM_ENABLE_TAPE
AM_CFLAGS += -D_UCVM_ENABLE_TAPE
endif

# CVMS5 includes
if UCVM_AM_ENABLE_CVMS5
AM_CFLAGS += -D_UCVM_ENABLE_CVMS5
endif

# CCA06 includes
if UCVM_AM_ENABLE_CCA
AM_CFLAGS += -D_UCVM_ENABLE_CCA
endif

# CS173 includes
if UCVM_AM_ENABLE_CS173
AM_CFLAGS += -D_UCVM_ENABLE_CS173
endif

# CS173H includes
if UCVM_AM_ENABLE_CS173H
AM_CFLAGS += -D_UCVM_ENABLE_CS173H
endif



#check: unittest accepttest
#	@( cd ${prefix}/tests; source ../conf/ucvm_env.sh; \
#		./unittest;\
#		./accepttest;\
#		./accept_test.py ${prefix}/tests;\
#	)


# End of file
