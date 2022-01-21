dnl GNU Autoconf config

AC_PREREQ(2.59)
AC_INIT([UCVM], [22.X.0], [software@scec.org])
AC_CONFIG_AUX_DIR([./aux-config])
AC_CONFIG_MACRO_DIR([m4])
AM_INIT_AUTOMAKE([foreign no-exeext])

dnl
dnl Models
dnl

AC_ARG_ENABLE([model-cca],
	[AC_HELP_STRING([--enable-model-cca],
		[enable use of SCEC CCA model @<:@default=no@:>@])],
		[if test "$enableval" = "yes" ; then enable_model_cca=yes; else enable_model_cca=no; fi],
		[enable_model_cca=no])
AM_CONDITIONAL([ENABLE_MODEL_CCA], [test "$enable_model_cca" = yes])

AC_ARG_ENABLE([model-cvmh],
	[AC_HELP_STRING([--enable-model-cvmh],
		[enable use of SCEC CVM-H model @<:@default=no@:>@])],
		[if test "$enableval" = "yes" ; then enable_model_cvmh=yes; else enable_model_cvmh=no; fi],
		[enable_model_cvmh=no])
AM_CONDITIONAL([ENABLE_MODEL_CVMH], [test "$enable_model_cvmh" = "yes"])

dnl AC_ARG_ENABLE([model-cvms],
dnl         [AS_HELP_STRING([--enable-model-cvms],
dnl         [enable model SCEC CVM-S])],
dnl         [enable_model_cvms=yes],
dnl         [enable_model_cvms=no])
        
dnl AC_ARG_ENABLE([model-cvms5],
dnl         [AS_HELP_STRING([--enable-model-cvms5],
dnl         [enable model SCEC CVM-S5])],
dnl         [enable_model_cvms5=yes],
dnl         [enable_model_cvms5=no])

dnl AC_ARG_ENABLE([model-cs173],
dnl         [AS_HELP_STRING([--enable-model-cs173],
dnl         [enable model SCEC CS173])],
dnl         [enable_model_cs173=yes],
dnl         [enable_model_cs173=no])

dnl AC_ARG_ENABLE([model-cs173h],
dnl         [AS_HELP_STRING([--enable-model-cs173h],
dnl         [enable model SCEC CS173H])],
dnl         [enable_model_cs173h=yes],
dnl         [enable_model_cs173h=no])

AC_ARG_ENABLE([model-cencalvm],
	[AC_HELP_STRING([--enable-model-cencalvm],
		[enable use of USGS CenCalVM model @<:@default=no@:>@])],
		[if test "$enableval" = "yes" ; then enable_model_cencalvm=yes; else enable_model_cencalvm=no; fi],
		[enable_model_cencalvm=no])
AM_CONDITIONAL([ENABLE_MODEL_CENCALVM], [test "$enable_model_cencalvm" = "yes"])

dnl AC_ARG_ENABLE([model-cvmsi],
dnl         [AS_HELP_STRING([--enable-model-cvmsi],
dnl         [enable model SCEC CVM-SI])],
dnl         [enable_model_cvmsi=yes],
dnl         [enable_model_cvmsi=no])

dnl AC_ARG_ENABLE([model-cvmnci],
dnl         [AS_HELP_STRING([--enable-model-cvmnci],
dnl         [enable model SCEC CVM-NCI])],
dnl         [enable_model_cvmnci=yes],
dnl         [enable_model_cvmnci=no])

dnl AC_ARG_ENABLE([model-wfcvm],
dnl         [AS_HELP_STRING([--enable-model-wfcvm],
dnl         [enable model WFCVM])],
dnl         [enable_model_wfcvm=yes],
dnl         [enable_model_wfcvm=no])

dnl AC_ARG_ENABLE([model-cvmlt],
dnl         [AS_HELP_STRING([--enable-model-cvmlt],
dnl         [enable model Lin-Thurber])],
dnl         [enable_model_cvmlt=yes],
dnl         [enable_model_cvmlt=no])

dnl AC_ARG_ENABLE([model-cmrg],
dnl         [AS_HELP_STRING([--enable-model-cmrg],
dnl         [enable model CMRG])],
dnl         [enable_model_cmrg=yes],
dnl         [enable_model_cmrg=no])

dnl AC_ARG_ENABLE([model-tape],
dnl         [AS_HELP_STRING([--enable-model-tape],
dnl         [enable model Tape])],
dnl         [enable_model_tape=yes],
dnl         [enable_model_tape=no])

dnl
dnl Dependencies
dnl

dnl Etree (Euclid)
AC_ARG_ENABLE([etree],
    [AC_HELP_STRING([--enable-etree],
        [install Etree library @<:@default=yes@:>@])],
	[if test "$enableval" = yes ; then install_etree=yes; else install_etree=no; fi],
	[install_etree=yes])
AM_CONDITIONAL([INSTALL_ETREE], [test "$install_etree" = yes])
AC_ARG_WITH([etree-incdir],
  [AS_HELP_STRING([--with-etree-incdir], [directory containing Etree header files])],
  [with_etree_incdir=$withval"],
  [with_etree_incdir=no])
AC_SUBST(with_etree_incdir)
AC_ARG_WITH([etree-libdir],
  [AS_HELP_STRING([--with-etree-libdir], [directory containing Etree library])],
  [with_etree_libdir="$withval"],
  [with_etree_libdir=no"])

dnl SQLITE
AC_ARG_ENABLE([sqlite],
    [AC_HELP_STRING([--enable-sqlite],
        [install Sqlite @<:@default=no@:>@])],
	[if test "$enableval" = "yes" ; then install_sqlite=yes; else install_sqlite=no; fi],
	[install_sqlite=no])
AM_CONDITIONAL([INSTALL_SQLITE], [test "$install_sqlite" = yes])
AC_ARG_WITH([sqlite-incdir],
    [AC_HELP_STRING([--with-sqlite-incdir],
        [location of sqlite header files @<:@default=no@:>@])],
	[with_sqlite_incdir=$withval],
	[with_sqlite_incdir=no])
AC_SUBST(with_sqlite_incdir)
AC_ARG_WITH([sqlite-libdir],
    [AC_HELP_STRING([--with-sqlite-libdir],
        [location of sqlite library @<:@default=no@:>@])],
	[with_sqlite_libdir=$withval],
	[with_sqlite_libdir=no])
AC_SUBST(with_sqlite_libdir)

dnl TIFF
AC_ARG_ENABLE([tiff],
    [AC_HELP_STRING([--enable-tiff],
        [install Tiff @<:@default=no@:>@])],
	[if test "$enableval" = "yes" ; then install_tiff=yes; else install_tiff=no; fi],
	[install_tiff=no])
AM_CONDITIONAL([INSTALL_TIFF], [test "$install_tiff" = yes])
AC_ARG_WITH([tiff-incdir],
    [AC_HELP_STRING([--with-tiff-incdir],
        [location of tiff header files @<:@default=no@:>@])],
	[with_tiff_incdir=$withval],
	[with_tiff_incdir=no])
AC_SUBST(with_tiff_incdir)
AC_ARG_WITH([tiff-libdir],
    [AC_HELP_STRING([--with-tiff-libdir],
        [location of tiff library @<:@default=no@:>@])],
	[with_tiff_libdir=$withval],
	[with_tiff_libdir=no])
AC_SUBST(with_tiff_libdir)

dnl PROJ
AC_ARG_ENABLE([proj],
    [AC_HELP_STRING([--enable-proj],
        [install Proj @<:@default=yes@:>@])],
	[if test "$enableval" = "yes" ; then install_proj=yes; else install_proj=no; fi],
	[install_proj=yes])
AM_CONDITIONAL([INSTALL_PROJ], [test "$install_proj" = yes])
AC_ARG_WITH([proj-incdir],
    [AC_HELP_STRING([--with-proj-incdir], [directory containing Proj header files @<:@default=no@:>@])],
	[with_proj_incdir=$withval],
	[with_proj_incdir=no])
AC_SUBST(with_proj_incdir)
AC_ARG_WITH([proj-libdir],
    [AC_HELP_STRING([--with-proj-libdir], [directory containing Proj library @<:@default=no@:>@])],
	[with_proj_libdir=$withval],
	[with_proj_libdir=no])
AC_SUBST(with_proj_libdir)

# FFTW
AC_ARG_ENABLE([fftw],
    [AC_HELP_STRING([--enable-fftw],
        [install FFTW @<:@default=yes@:>@])],
	[if test "$enableval" = yes ; then install_fftw=yes; else install_fftw=no; fi],
	[install_fftw=yes])
AM_CONDITIONAL([INSTALL_FFTW], [test "$install_fftw" = yes])
AC_ARG_WITH([fftw-incdir],
    [AC_HELP_STRING([--with-fftw-incdir],
	[directory containing FFTW header files @<:@default=no@:>@])],
	[with_fftw_incdir=$withval],
	[with_fftw_incdir=no])
AC_SUBST(with_fftw_incdir)
AC_ARG_WITH([fftw-libdir],
    [AC_HELP_STRING([--with-fftw-libdir],
        [directory containing FFTW library @<:@default=no@:>@])],
	[with_fftw_libdir=$withval],
	[with_fftw_libdir=no])
AC_SUBST(with_fftw_libdir)

dnl NETCDF
dnl AC_ARG_ENABLE([netcdf],
dnl     [AC_HELP_STRING([--enable-netcdf],
dnl         [install NetCDF @<:@default=yes@:>@])],
dnl 	[if test "$enableval" = yes ; then install_netcdf=yes; else install_netcdf=no; fi],
dnl 	[install_netcdf=no])
dnl AM_CONDITIONAL([INSTALL_NETCDF], [test "$install_netcdf" = yes])
dnl AC_ARG_WITH([netcdf-incdir],
dnl     [AC_HELP_STRING([--with-netcdf-incdir],
dnl 	[directory containing NetCDF header files @<:@default=no@:>@])],
dnl 	[with_netcdf_incdir=$withval],
dnl 	[with_netcdf_incdir=no])
dnl AC_SUBST(with_netcdf_incdir)
dnl AC_ARG_WITH([netcdf-libdir],
dnl     [AC_HELP_STRING([--with-netcdf-libdir],
dnl         [directory containing NetCDF library @<:@default=no@:>@])],
dnl 	[with_netcdf_libdir=$withval],
dnl 	[with_netcdf_libdir=no])
dnl AC_SUBST(with_netcdf_libdir)

dnl AC_ARG_ENABLE([iobuf],
dnl         [AS_HELP_STRING([--enable-iobuf],
dnl         [enable IOBUF module])],
dnl         [enable_iobuf=yes],
dnl         [enable_iobuf=no])

dnl
dnl Compilers and command line tools
dnl
AC_PROG_CC
AC_PROG_LIBTOOL
AC_PROG_INSTALL
AC_PROG_MKDIR_P
AC_CANONICAL_HOST

#if test "$fortran_required" = yes; then
#   AC_PROJ_FC
#fi

AM_CONDITIONAL([BUILD_SHARED_LIBRARY], [test "$enable_shared" = yes])
if test "$enable_shared" = yes; then
  AC_MSG_NOTICE("Building shared libraries")
  case $host_os in
    darwin*)
      SHARED_LIBRARY_EXT="dylib"
    ;;
    linux*)
      SHARED_LIBRARY_EXT="so"
    ;;
    *)
      SHARED_LIBRARY_EXT="so"
    ;;
  esac
  AC_MSG_NOTICE("Assuming shared libraries have extension '$SHARED_LIBRARY_EXT'")
  AC_SUBST(SHARED_LIBRARY_EXT)
else
  AC_MSG_WARN("Building shared libraries not enabled.")
fi

dnl curl
AC_PATH_PROG(CURL, curl)
if test -z "$CURL" ; then
  AC_MSG_FAILURE([cannot find 'curl' program.])
  CURL=`echo "Error: curl is not installed." ; false`
fi

dnl TAR
AC_PATH_PROG(TAR, tar)
if test -z "$TAR" ; then
  AC_MSG_FAILURE([cannot find 'tar' program.])
  TAR=`echo "Error: tar is not installed." ; false`
fi

if test $enable_model_cencalvm = yes; then
dnl GUNZIP
AC_PATH_PROG(GUNZIP, gunzip)
if test -z "$GUNZIP" ; then
  AC_MSG_FAILURE([cannot find 'gunzip' program.])
  GUNZIP=`echo "Error: USGS CenCalVM requires gunzip to uncompress model. gunzip is not installed." ; false`
fi
fi

dnl MPI
AX_PROG_CC_MPI([true],[use_mpi=yes],[use_mpi=no])
AM_CONDITIONAL(UCVM_HAVE_MPI, [test x"$use_mpi" = xyes])

dnl
dnl Verify configuration
dnl

dnl ETREE (required)
if test "$install_etree" = yes ; then
  ETREE_INCLUDES=""
  ETREE_LDFLAGS="-letree"
else
  if test "$with_etree_incdir" != no ; then
    ETREE_INCLUDES="-I$with_etree_incdir"
  fi
  if test"$with_etree_libdir" != no ; then
    ETREE_LDFLAGS="-L$with_etree_libdir -letree"
  fi
  SCEC_ETREE_HEADER
  SCEC_ETREE_LIB
fi
AC_SUBST(ETREE_INCLUDES)
AC_SUBST(ETREE_LDFLAGS)

dnl proj (required)
if test "$install_proj" = yes ; then
  dnl sqlite (required by proj)
  if test "$install_sqlite" = yes ; then
    SQLITE3_INCLUDES="-I$prefix/include"
    SQLITE3_LDFLAGS="-L$prefix/lib -lsqlite"
  else
    if test "$with_sqlite_incdir" != no; then
      SQLITE3_INCLUDES="-I$with_sqlite_incdir"
    fi
    if test "$with_sqlite_libdir" != no; then
      SQLITE3_LDFLAGS="-L$with_sqlite_libdir"
    fi
    SCEC_SQLITE3_HEADER
    SCEC_SQLITE3_LIB
  fi
  AC_SUBST(SQLITE3_INCLUDES)
  AC_SUBST(SQLITE3_LDFLAGS)

  dnl tiff (required by proj)
  if test "$install_tiff" = yes ; then
    TIFF_INCLUDES="-I$prefix/include"
    TIFF_LDFLAGS="-L$prefix/lib -ltiff"
  else
    if test "$with_tiff_incdir" != no; then
      TIFF_INCLUDES="-I$with_tiff_incdir"
    fi
    if test "$with_tiff_libdir" != no; then
      TIFF_LDFLAGS="-L$with_tiff_libdir"
    fi
    SCEC_TIFF_HEADER
    SCEC_TIFF_LIB
  fi
  AC_SUBST(TIFF_INCLUDES)
  AC_SUBST(TIFF_LDFLAGS)

  PROJ_INCLUDES="-I$prefix/include"
  PROJ_LDFLAGS="-L$prefix/lib -lproj"
else
  if test "$with_proj_incdir" != no ; then
    PROJ_INCLUDES="-I$with_proj_incdir"
  fi
  if test"$with_proj_libdir" != no ; then
    PROJ_LDFLAGS="-L$with_proj_libdir -lproj"
  fi
  SCEC_PROJ_HEADER
  SCEC_PROJ_LIB
fi
AC_SUBST(PROJ_INCLUDES)
AC_SUBST(PROJ_LDFLAGS)

dnl Check required FFTW installation
dnl CFLAGS="$FFTW_INCL $CHECK_CFLAGS"
dnl LDFLAGS="$CHECK_LDFLAGS $FFTW_LIB"
dnl AC_CHECK_LIB(fftw3, fftw_execute, [AC_CHECK_HEADER([fftw3.h], [], [AC_MSG_ERROR(["FFTW headers not found in $FFTW_INCL; use --with-fftw-include-path"])], [AC_INCLUDES_DEFAULT])],[AC_MSG_ERROR(["FFTW library not found; use --with-fftw-lib-path"])])

dnl # Check optional NetCDF library
dnl if test "x$enable_netcdf" = xyes; then
dnl    echo "Checking for NetCDF library"
dnl    CFLAGS="$NETCDF_INCL $CHECK_CFLAGS"
dnl    LDFLAGS="$CHECK_LDFLAGS $NETCDF_LIB"
dnl    AC_CHECK_LIB(netcdf, nc_create,
dnl 	[AM_CONDITIONAL(UCVM_HAVE_NETCDF, true)], 
dnl 	[AC_MSG_ERROR([NetCDF library not found; use --with-netcdf-include-path"])],
dnl 	[-lhdf5_hl -lhdf5 -lz -lm -lcurl -ldl])
dnl    AC_CHECK_HEADER(netcdf.h,
dnl 	[],
dnl 	[AC_MSG_ERROR([NetCDF header not found; use --with-netcdf-lib-path"])],
dnl 	[AC_INCLUDES_DEFAULT])

dnl else
dnl 	AM_CONDITIONAL(UCVM_HAVE_NETCDF, false)
dnl fi

dnl
dnl Setup environment so dependencies are used in build
dnl
CFLAGS="$CFLAGS"
CPPFLAGS="-I$prefix/include $CPPFLAGS"
LDFLAGS="-L$prefix/lib -L$prefix/lib64 $LDFLAGS"
AC_SUBST(CFLAGS)
AC_SUBST(CPPFLAGS)
AC_SUBST(LDFLAGS)


dnl
dnl Create setup.sh
dnl

echo "#!/bin/bash" > setup.sh

TEMPVAR="$prefix/bin"
if test "X${PATH}" = X ; then
  echo "export PATH=$TEMPVAR" >> setup.sh
else
  echo "export PATH=$TEMPVAR:\${PATH}" >> setup.sh
fi

case $host_os in
  darwin*)
    ;;
  *)
    TEMPVAR="$prefix/lib:$prefix/lib64"
    if test "X${LD_LIBRARY_PATH}" = X ; then
      echo "export LD_LIBRARY_PATH=$TEMPVAR" >> setup.sh
    else
      echo "export LD_LIBRARY_PATH=$TEMPVAR:\${LD_LIBRARY_PATH}" >> setup.sh
    fi
    ;;
esac

dnl
dnl Generate Makefiles
dnl

AC_CONFIG_FILES([Makefile
	dependencies/Makefile
	src/Makefile
	src/ucvm/Makefile
  src/plugin_adapters/Makefile
	model/Makefile
	model/1d/Makefile
	model/ucvm/Makefile
	model/cca/Makefile
	model/cvmh/Makefile
  model/usgs_cencalvm/Makefile
	man/Makefile
	conf/Makefile
	])

AC_OUTPUT


dnl
dnl Write summary
dnl

echo ""
echo "Models enabled:"
echo "  SCEC CVM-H: $enable_model_cvmh"
echo "  SCEC CCA: $enable_model_cca"
echo "  USGS CenCalVM: $enable_model_cencalvm"
echo ""
echo "Dependencies to be installed:"
echo "  Etree/Euclid (required): $install_etree"
echo "  Sqlite (required by proj): $install_sqlite"
echo "  Tiff (required by proj): $install_tiff"
echo "  Proj (required): $install_proj"
echo "  FFTW (required): $install_fftw"
dnl echo "  NetCDF (optional): $install_netcdf"
echo ""
echo "UCVM and its dependencies will be installed to $prefix"
echo ""
echo "IMPORTANT"
echo ""
echo "  Step 1"
echo "  BEFORE running \"make\", setup your environment so that all of the "
echo "  dependencies are consistent. See the file setup.sh in this directory "
echo "  for how to set your variables for the bash shell. You can either run "
echo "  \"source setup.sh\" in this terminal (i.e., shell) where you will "
echo "  build UCVM and it dependencies or add these settings to your "
echo "  .bashrc or equivalent file and open a new terminal (i.e., shell)."
echo ""
echo "  Step 2"
echo "  Running \"make\" will install UCVM and its dependencies along with "
echo "  the requested models."
echo ""
echo "  Step 3"
echo "  If you did not setup your .bashrc with the environment variables, be sure "
echo "  to run \"source setup.sh\" every time you open a new terminal (i.e., shell) "
echo "  BEFORE using the UCVM software."
echo ""
