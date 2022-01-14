# GNU Automake config

DEPS_URL=https://g-c662a6.a78b8.36fe.data.globus.org/ucvm/v21_10/lib
PROJ_URL=https://download.osgeo.org/proj
PROJ_VER=5.0.0
PROJ_DATUM_VER=1.7
FFTW_VER=3.3.3
EUCLID_VER=3.1.4


all: installed_etree installed_proj installed_fftw

# ------------------------------------------------------------------------------
# ETREE/EUCLID
# ------------------------------------------------------------------------------
etree:
if INSTALL_ETREE
EUCLID_URL=https://github.com/baagaard-usgs/euclid-etree/releases/download/v$(EUCLID_VER)
EUCLID_TARBALL=euclid-$(EUCLID_VER).tar.gz
	if [ ! -f "$(EUCLID_TARBALL)" ]; then $(CURL) -L -O $(EUCLID_URL)/$(EUCLID_TARBALL); fi
	$(TAR) -xf $(EUCLID_TARBALL)
	$(MKDIR_P) euclid-build
	cd euclid-build && \
		../euclid-$(EUCLID_VER)/configure \
			--prefix=$(prefix) \
			CC=$(CC) CPPFLAGS="$(CPPFLAGS)" CFLAGS="$(CFLAGS)" LDFLAGS="$(LDFLAGS)"; \
		make -C libsrc && make install -C libsrc && \
		touch $(abs_builddir)/installed_$@
else
	@echo "Using existing $@ installation."
	touch $(abs_builddir)/installed_$@
endif

installed_etree:
	$(MAKE) $(AM_MAKEFLAGS) etree

# ------------------------------------------------------------------------------
# PROJ
# ------------------------------------------------------------------------------
proj:
if INSTALL_PROJ
PROJ_TARBALL=proj-$(PROJ_VER).tar.gz
PROJ_DATUM_TARBALL=proj-datumgrid-$(PROJ_DATUM_VER).tar.gz
	if [ ! -f "$(PROJ_TARBALL)" ]; then $(CURL) -O $(DEPS_URL)/$(PROJ_TARBALL); fi
	if [ ! -f "$(PROJ_DATUM_TARBALL)" ]; then $(CURL) -O $(PROJ_URL)/$(PROJ_DATUM_TARBALL); fi
	$(TAR) -xf $(PROJ_TARBALL)
	$(MKDIR_P) proj-build
	cd proj-build && \
		../proj-$(PROJ_VER)/configure --with-jni=no \
			--prefix=$(prefix) \
			CC=$(CC) CPPFLAGS="$(CPPFLAGS)" CFLAGS="$(CFLAGS)" LDFLAGS="$(LDFLAGS)"; \
		make && make install && \
		cd $(prefix)/share/proj && \
		$(TAR) -xf $(abs_builddir)/$(PROJ_DATUM_TARBALL) && \
		touch $(abs_builddir)/installed_$@
else
	@echo "Using existing $@ installation."
	touch $(abs_builddir)/installed_$@
endif

installed_proj:
	$(MAKE) $(AM_MAKEFLAGS) proj

# ------------------------------------------------------------------------------
# FFTW
# ------------------------------------------------------------------------------
fftw:
if INSTALL_FFTW
FFTW_TARBALL=fftw-$(FFTW_VER).tar.gz
	if [ ! -f "$(FFTW_TARBALL)" ]; then $(CURL) -O $(DEPS_URL)/$(FFTW_TARBALL); fi
	$(TAR) -xf $(FFTW_TARBALL)
	$(MKDIR_P) fftw-build
	cd fftw-build && \
		../fftw-$(FFTW_VER)/configure --enable-fortran=no \
			--prefix=$(prefix) \
			CC=$(CC) CPPFLAGS="$(CPPFLAGS)" CFLAGS="$(CFLAGS)" LDFLAGS="$(LDFLAGS)"; \
		make && make install && \
		touch $(abs_builddir)/installed_$@
else
	@echo "Using existing $@ installation."
	touch $(abs_builddir)/installed_$@
endif

installed_fftw:
	$(MAKE) $(AM_MAKEFLAGS) fftw


# End of file
