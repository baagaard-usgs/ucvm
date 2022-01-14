# GNU Automake config
CVMH_VER=22.X.0
CVMH_URL=https://github.com/baagaard-usgs/cvmh/releases/download/v$(CVMH_VER)
CVMH_TARBALL=cvmh-$(CVMH_VER).tar.gz

all: installed_cvmh

cvmh:
	if [ ! -f "$(CVMH_TARBALL)" ]; then $(CURL) -L -O $(CVMH_URL)/$(CVMH_TARBALL); fi
	$(TAR) -xf $(CVMH_TARBALL)
	$(MKDIR_P) cvmh-build
	cd cvmh-build && \
		../cvmh-$(CVMH_VER)/configure \
			--prefix=$(prefix) --datarootdir=$(prefix)/share/ucvm \
			CC=$(CC) CPPFLAGS="$(CPPFLAGS)" CFLAGS="$(CFLAGS)" LDFLAGS="$(LDFLAGS)"; \
			make && make install && make check && \
			touch $(abs_builddir)/installed_$@

installed_cvmh:
	$(MAKE) $(AM_MAKEFLAGS) cvmh

# End of file
