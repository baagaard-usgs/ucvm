# GNU Automake config
CENCALVM_VER=1.2.0
CENCALVM_URL=https://github.com/usgs/earthquake-cencalvm/releases/download/v$(CENCALVM_VER)
CENCALVM_TARBALL=cencalvm-$(CENCALVM_VER).tar.gz

MODEL_LABEL=usgs_cencalvm
MODEL_DIR=$(pkgdatadir)/model/$(MODEL_LABEL)
MODEL_VER=08.3.0
MODEL_URL=ftp://ftpext.usgs.gov/pub/wr/ca/menlo.park/ehzftp/baagaard/cencalvm/database
DETAILED_MODEL=USGSBayAreaVM-$(MODEL_VER).etree.gz
REGIONAL_MODEL=USGSBayAreaVMExt-$(MODEL_VER).etree.gz

all: installed_cencalvm installed_detailed_model installed_regional_model

cencalvm:
	if [ ! -f "$(CENCALVM_TARBALL)" ]; then $(CURL) -L -O $(CENCALVM_URL)/$(CENCALVM_TARBALL); fi
	$(TAR) -xf $(CENCALVM_TARBALL)
	$(MKDIR_P) cencalvm-build
	cd cencalvm-build && \
		../cencalvm-$(CENCALVM_VER)/configure \
			--prefix=$(prefix) --datarootdir=$(prefix)/share/ucvm \
			CC=$(CC) CPPFLAGS="$(CPPFLAGS)" CFLAGS="$(CFLAGS)" LDFLAGS="$(LDFLAGS)"; \
			make && make install && make check && \
			touch $(abs_builddir)/installed_$@

detailed_model:
	$(MKDIR_P) $(MODEL_DIR) && \
		cd $(MODEL_DIR) && \
		if [ ! -f "$(DETAILED_MODEL)" ]; then $(CURL) -L -O $(MODEL_URL)/$(DETAILED_MODEL) && \
		$(GUNZIP) $(MODEL_URL)/$(DETAILED_MODEL); fi
	touch $(abs_builddir)/installed_$@

regional_model:
	$(MKDIR_P) $(MODEL_DIR) && \
		cd $(MODEL_DIR) && \
		if [ ! -f "$(REGIONAL_MODEL)" ]; then $(CURL) -L -O $(MODEL_URL)/$(REGIONAL_MODEL) && \
		$(GUNZIP) $(MODEL_URL)/$(REGIONAL_MODEL); fi
	touch $(abs_builddir)/installed_$@


installed_cencalvm:
	$(MAKE) $(AM_MAKEFLAGS) cencalvm

installed_detailed_model:
	$(MAKE) $(AM_MAKEFLAGS) detailed_model

installed_regional_model:
	$(MAKE) $(AM_MAKEFLAGS) regional_model



# End of file
