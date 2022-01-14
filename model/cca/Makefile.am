# GNU Automake config
CCA_VER=1.1.0
CCA_URL=https://github.com/baagaard-usgs/cca/releases/download/v$(CCA_VER)
CCA_TARBALL=cca-$(CCA_VER).tar.gz

all: installed_cca

cca:
	if [ ! -f "$(CCA_TARBALL)" ]; then $(CURL) -L -O $(CCA_URL)/$(CCA_TARBALL); fi
	$(TAR) -xf $(CCA_TARBALL)
	$(MKDIR_P) cca-build
	cd cca-build && \
		../cca-$(CCA_VER)/configure \
			--prefix=$(prefix) --datarootdir=$(prefix)/share/ucvm --disable-proj --disable-etree \
			CC=$(CC) CPPFLAGS="$(CPPFLAGS)" CFLAGS="$(CFLAGS)" LDFLAGS="$(LDFLAGS)"; \
			make && make install && make check && \
			touch $(abs_builddir)/installed_$@

installed_cca:
	$(MAKE) $(AM_MAKEFLAGS) cca

# End of file
