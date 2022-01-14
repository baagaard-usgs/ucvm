# GNU Automake config

dist_noinst_DATA = \
	floats.in \
	floats_complex.in \
	test-grid.in \
	test_latlons.txt \
	test_latlons_1d_pts.txt \
	test_latlons_albacore.txt \
	test_latlons_cvlsu.txt \
	test_latlons_cvms5_invalid.txt \
	test_latlons_cvms_bkg_pts.txt \
	test_latlons_ivlsu.txt \
	test_latlons_lemoore_pts.txt \
	test_latlons_socal_pts.txt \
	test_latlons_socal_pts_elev.txt \
	test_latlons_wfcvm.txt \
	test_latlonsonly.txt \
	test_latlonsonly_cencal_cvms_or_cvms5.txt

# 'export' the input files by performing a mock install
export_datadir = $(top_builddir)/test/inputs
export-data: $(dist_noinst_DATA)
	if [ "X$(top_srcdir)" != "X$(top_builddir)" ]; then for f in $(dist_noinst_DATA); do $(install_sh_DATA) $(srcdir)/$$f $(export_datadir); done; fi

clean-data:
	if [ "X$(top_srcdir)" != "X$(top_builddir)" ]; then for f in $(dist_noinst_DATA) $(noinst_TMP); do $(RM) $(RM_FLAGS) $(export_datadir)/$$f; done; fi

BUILT_SOURCES = export-data
clean-local: clean-data


# End of file
