# GNU Automake config

subpkgdatadir = $(pkgdatadir)/model/ucvm

dist_subpkgdata_DATA = \
	ucvm.conf \
	ucvm_utah.conf

MODEL_DIR=$(subpkgdatadir)
MODEL_URL=https://g-c662a6.a78b8.36fe.data.globus.org/ucvm/v21_10/etree

model_files = \
	ucvm.e \
	ucvm_utah.e

installed_data:
	$(MKDIR_P) $(MODEL_DIR)
	for f in $(model_files); do $(CURL) -o $(MODEL_DIR)/$$f $(MODEL_URL)/$$f; done
	touch $(abs_builddir)/installed_data

install-data-local: installed_data


# End of file
