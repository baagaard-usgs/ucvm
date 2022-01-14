#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "ucvm_utils.h"
#include "ucvm_model_plugin.h"

#if defined(BUILD_SHARED_LIBRARY)
	#include <dlfcn.h>
#if !defined(SHARED_LIBRARY_EXT)
#define SHARED_LIBRARY_EXT so
#endif
#else

#ifdef _UCVM_ENABLE_IVLSU
	extern int ivlsu_init;
	extern int ivlsu_query;
	extern int ivlsu_finalize;
	extern int ivlsu_version;
#endif
#ifdef _UCVM_ENABLE_CVLSU
	extern int cvlsu_init;
	extern int cvlsu_query;
	extern int cvlsu_finalize;
	extern int cvlsu_version;
#endif
#ifdef _UCVM_ENABLE_ALBACORE
	extern int albacore_init;
	extern int albacore_query;
	extern int albacore_finalize;
	extern int albacore_version;
#endif
#ifdef _UCVM_ENABLE_CVMS5
	extern int cvms5_init;
	extern int cvms5_query;
	extern int cvms5_finalize;
	extern int cvms5_version;
#endif
#ifdef _UCVM_ENABLE_CCA
	extern int cca_init;
	extern int cca_query;
	extern int cca_finalize;
	extern int cca_version;
#endif
#ifdef _UCVM_ENABLE_CS173
	extern int cs173_init;
	extern int cs173_query;
	extern int cs173_finalize;
	extern int cs173_version;
#endif
#ifdef _UCVM_ENABLE_CS173H
	extern int cs173h_init;
	extern int cs173h_query;
	extern int cs173h_finalize;
	extern int cs173h_version;
#endif
#endif

// Variables

/** Have we initialized this model yet? */
int plugin_model_initialized = 0;
ucvm_plugin_model_t plugin_models[UCVM_MAX_MODELS];

/**
 * Initializes the model within the UCVM framework. This is accomplished
 * by dynamically loading the library symbols.
 *
 * @param id The model's id.
 * @param lib_dir Path to directory where UCVM libraries are installed ($prefix/lib).
 * @param models_dir Path to directory where UCVM models are installed ($prefix/share/ucvm/model).
 * @param conf The configuration file parameters for the model.
 * @return UCVM_CODE_SUCCESS on success or ERROR on failure.
 */
int ucvm_plugin_model_init(int id, const char *lib_dir, const char *models_dir, ucvm_modelconf_t *conf) {
	void *handle;
	char libpath[UCVM_MAX_PATH_LEN];

        ucvm_plugin_model_t *pptr=get_plugin_by_label(conf->label);
      
	// Have we initialized this model already?
	if (pptr) {
	  fprintf(stderr, "Model %d has already been initialized.\n", id);
	  return UCVM_CODE_ERROR;
	  } else {
          // grab the first available space
              pptr=get_plugin_by_order(plugin_model_initialized);
        }

#if defined(BUILD_SHARED_LIBRARY)
	snprintf(libpath, UCVM_MAX_PATH_LEN, "%s/lib%s.%s", lib_dir, conf->label, SHARED_LIBRARY_EXT);

	// Open the library.
	handle = dlopen(libpath, RTLD_LAZY);

	if (!handle) {
		fprintf(stderr, "Could not load %s. Error: %s.\n", conf->label, dlerror());
		return UCVM_CODE_ERROR;
	}

	// Load the symbols.
	MI_FNPTR init_fnptr;
	*(void**)(&init_fnptr) = dlsym(handle, "ucvmapi_model_init");
	if (dlerror() != NULL) {
		fprintf(stderr, "Could not load ucvmapi_model_init.\n");
		return UCVM_CODE_ERROR;
	}
	pptr->model_init = *init_fnptr;

	MF_FNPTR finalize_fnptr;
	*(void**)(&finalize_fnptr) = dlsym(handle, "ucvmapi_model_finalize");
	if (dlerror() != NULL) {
		fprintf(stderr, "Could not load ucvmapi_model_finalize.\n");
		return UCVM_CODE_ERROR;
	} 
	pptr->model_finalize = *finalize_fnptr;

	MV_FNPTR version_fnptr;
	*(void**)(&version_fnptr) = dlsym(handle, "ucvmapi_model_version");
	if (dlerror() != NULL) {
		fprintf(stderr, "Could not load ucvmapi_model_version.\n");
		return UCVM_CODE_ERROR;
	}
	pptr->model_version = *version_fnptr;

	MP_FNPTR set_param_fnptr;
	*(void**)(&set_param_fnptr) = dlsym(handle, "ucvmapi_model_set_param");
	if (dlerror() != NULL) {
		fprintf(stderr, "Could not load ucvmapi_model_set_param.\n");
		return UCVM_CODE_ERROR;
	}
	pptr->model_set_param = *set_param_fnptr;

	MQ_FNPTR query_fnptr;
	*(void**)(&query_fnptr) = dlsym(handle, "ucvmapi_model_query");
	if (dlerror() != NULL) {
		fprintf(stderr, "Could not load ucvmapi_model_query.\n");
		return UCVM_CODE_ERROR;
	}
	pptr->model_query = *query_fnptr;

	// Initialize the model.
	if (pptr->model_init(models_dir, conf->label) != 0) {
		fprintf(stderr, "Failed to initialize model '%s'.\n", conf->label);
		return UCVM_CODE_ERROR;
	}
#else

#ifdef _UCVM_ENABLE_CVLSU
        if (strcmp(conf->label, UCVM_MODEL_CVLSU) == 0) {
                pptr->model_init = cvlsu_init;
                pptr->model_finalize = cvlsu_finalize;
                pptr->model_version = cvlsu_version;
				pptr->model_set_param = cvlsu_set_param;
                pptr->model_query = cvlsu_query;
                if (pptr->model_init(conf->config, conf->label) != 0) {
                        fprintf(stderr, "Failed to initialize model '%s'.\n", conf->label);
                        return UCVM_CODE_ERROR;
                }
        }
#endif
#ifdef _UCVM_ENABLE_IVLSU
        if (strcmp(conf->label, UCVM_MODEL_IVLSU) == 0) {
                pptr->model_init = ivlsu_init;
                pptr->model_finalize = ivlsu_finalize;
                pptr->model_version = ivlsu_version;
				pptr->model_set_param = ivlsu_set_param;
                pptr->model_query = ivlsu_query;
                if (pptr->model_init(conf->config, conf->label) != 0) {
                        fprintf(stderr, "Failed to initialize model '%s'.\n", conf->label);
                        return UCVM_CODE_ERROR;
                }
        }
#endif
#ifdef _UCVM_ENABLE_ALBACORE
        if (strcmp(conf->label, UCVM_MODEL_ALBACORE) == 0) {
                pptr->model_init = albacore_init;
                pptr->model_finalize = albacore_finalize;
                pptr->model_version = albacore_version;
				pptr->model_set_param = albacore_set_param;
                pptr->model_query = albacore_query;
                if (pptr->model_init(conf->config, conf->label) != 0) {
                        fprintf(stderr, "Failed to initialize model '%s'.\n", conf->label);
                        return UCVM_CODE_ERROR;
                }
        }
#endif
#ifdef _UCVM_ENABLE_CVMS5
        if (strcmp(conf->label, UCVM_MODEL_CVMS5) == 0) {
                pptr->model_init = cvms5_init;
                pptr->model_finalize = cvms5_finalize;
                pptr->model_version = cvms5_version;
				pptr->model_set_param = cvms5_set_param;
                pptr->model_query = cvms5_query;
                if (pptr->model_init(conf->config, conf->label) != 0) {
                        fprintf(stderr, "Failed to initialize model '%s'.\n", conf->label);
                        return UCVM_CODE_ERROR;
                }
        }
#endif
#ifdef _UCVM_ENABLE_CCA
        if (strcmp(conf->label, UCVM_MODEL_CCA) == 0) {
                pptr->model_init = cca_init;
                pptr->model_finalize = cca_finalize;
                pptr->model_version = cca_version;
				pptr->model_set_param = cca_set_param;
                pptr->model_query = cca_query;
                if (pptr->model_init(conf->config, conf->label) != 0) {
                        fprintf(stderr, "Failed to initialize model '%s'.\n", conf->label);
                        return UCVM_CODE_ERROR;
                }
        }
#endif
#ifdef _UCVM_ENABLE_CS173
        if (strcmp(conf->label, UCVM_MODEL_CS173) == 0) {
                pptr->model_init = cs173_init;
                pptr->model_finalize = cs173_finalize;
                pptr->model_version = cs173_version;
				pptr->model_set_param = cs173_set_param;
                pptr->model_query = cs173_query;
                if (pptr->model_init(conf->config, conf->label) != 0) {
                        fprintf(stderr, "Failed to initialize model '%s'.\n", conf->label);
                        return UCVM_CODE_ERROR;
                }
        }
#endif
#ifdef _UCVM_ENABLE_CS173H
        if (strcmp(conf->label, UCVM_MODEL_CS173H) == 0) {
                pptr->model_init = cs173h_init;
                pptr->model_finalize = cs173h_finalize;
                pptr->model_version = cs173h_version;
				pptr->model_set_param = cs173h_set_param;
                pptr->model_query = cs173h_query;
                if (pptr->model_init(conf->config, conf->label) != 0) {
                        fprintf(stderr, "Failed to initialize model '%s'.\n", conf->label);
                        return UCVM_CODE_ERROR;
                }
        }
#endif
        if (pptr->model_init == NULL) {
                fprintf(stderr, "Model pointer not initialized.\n");
                return UCVM_CODE_ERROR;
        }

#endif

	// Assign the id.
        pptr->model_id = id;

	// Save the model configuration data.
	memcpy(&(pptr->model_conf), conf, sizeof(ucvm_modelconf_t));

	// Yes, this model has been initialized successfully.
	plugin_model_initialized += 1;

	return UCVM_CODE_SUCCESS;
}

/**
 * Finalizes the model and recovers all allocated memory.
 *
 * @return UCVM_CODE_SUCCESS
 */
int ucvm_plugin_model_finalize()
{
  int i;
  for(i=0; i< plugin_model_initialized; i++) {
    // Finalize the model.
     ucvm_plugin_model_t *pptr=&plugin_models[i];
     pptr->model_finalize();
  }

  // We're no longer initialized.
  plugin_model_initialized = 0;

  return UCVM_CODE_SUCCESS;
}

/**
 * Retrieves the version of the model with which we're working.
 *
 * @param The model id.
 * @param The version string to be returned.
 * @param The maximum length of the version string.
 * @return UCVM_CODE_SUCCESS if everything works, ERROR if not.
 */
int ucvm_plugin_model_version(int id, char *ver, int len)
{
  ucvm_plugin_model_t *pptr=get_plugin_by_id(id);
  if (!pptr) {
    fprintf(stderr, "Invalid model id.\n");
    return UCVM_CODE_ERROR;
  }

  if (pptr->model_version(ver, len) != 0) {
    return UCVM_CODE_ERROR;
  }

  return UCVM_CODE_SUCCESS;
}

/**
 * Retrieves the model's label.
 *
 * @param The id of the model.
 * @param The label to return.
 * @param The maximum length of the label.
 */
int ucvm_plugin_model_label(int id, char *lab, int len)
{
  ucvm_plugin_model_t *pptr=get_plugin_by_id(id);
  if (!pptr) {
    fprintf(stderr, "Invalid model id.\n");
    return UCVM_CODE_ERROR;
  }

  ucvm_strcpy(lab, pptr->model_conf.label, len);
  return UCVM_CODE_SUCCESS;
}

/**
 * This is the main function to query the model. It transfers to the point
 * buffer and then queries the model.
 *
 * @param The model id.
 * @param Co-ordinate mode (elevation or depth or neither).
 * @param The number of points in the point buffer.
 * @param The point buffer.
 * @param The data buffer.
 */
int ucvm_plugin_model_query(int id, ucvm_ctype_t cmode, int n, ucvm_point_t *pnt, ucvm_data_t *data) {
	int i = 0, j = 0, nn = 0;
	double depth = 0;
	int datagap = 0;

        ucvm_plugin_model_t *pptr=get_plugin_by_id(id);
        if (!pptr) {
	// Check the model id.
		fprintf(stderr, "Invalid model id.\n");
		return UCVM_CODE_ERROR;
	}

	// Ensure we're using depth or elevation queries.
	if (cmode != UCVM_COORD_GEO_DEPTH && cmode != UCVM_COORD_GEO_ELEV) {
		fprintf(stderr, "Unsupported coordinate system type.\n");
		return UCVM_CODE_ERROR;
	}

        /** Stores the points in in WGS84 format. */
        /** The returned data from the plugin model. */
        basic_point_t *ucvm_plugin_pnts_buffer = malloc(MODEL_POINT_BUFFER * sizeof(basic_point_t));
        basic_properties_t *ucvm_plugin_data_buffer = malloc(MODEL_POINT_BUFFER * sizeof(basic_properties_t));

        /** Stores the mapping between data array and query buffer array */
	int* index_mapping = malloc(sizeof(int)*MODEL_POINT_BUFFER);
	if (index_mapping==NULL || ucvm_plugin_pnts_buffer == NULL || ucvm_plugin_data_buffer == NULL) {
		fprintf(stderr, "Memory allocation of pnts_buffer, data_buffer or index_mapping failed, aborting.\n");
		return UCVM_CODE_ERROR;
	}

	for (i = 0; i < n; i++) {
	    if ((data[i].crust.source == UCVM_SOURCE_NONE) && ((data[i].domain == UCVM_DOMAIN_INTERP) || (data[i].domain == UCVM_DOMAIN_CRUST)) &&
	      	(region_contains_null(&(pptr->model_conf.region), cmode, &(pnt[i])))) {

	        /* Modify pre-computed depth to account for GTL interp range */
	        depth = data[i].depth + data[i].shift_cr;

                index_mapping[nn]=i;

    		ucvm_plugin_pnts_buffer[nn].longitude = pnt[i].coord[0];
    		ucvm_plugin_pnts_buffer[nn].latitude = pnt[i].coord[1];
    		ucvm_plugin_pnts_buffer[nn].depth = depth;
    		nn++;

	    	if (nn == MODEL_POINT_BUFFER || i == n - 1) {
	    		// We've reached the maximum buffer. Do the query.
	    		pptr->model_query(ucvm_plugin_pnts_buffer, ucvm_plugin_data_buffer, nn);
	    		// Transfer our findings.
	    		for (j = 0; j < nn; j++) {
	    			if (ucvm_plugin_data_buffer[j].vp >= 0 && ucvm_plugin_data_buffer[j].vs >= 0 && ucvm_plugin_data_buffer[j].rho >= 0) {
	    				data[index_mapping[j]].crust.source = pptr->model_id;
	    				data[index_mapping[j]].crust.vp = ucvm_plugin_data_buffer[j].vp;
	    				data[index_mapping[j]].crust.vs = ucvm_plugin_data_buffer[j].vs;
	    				data[index_mapping[j]].crust.rho = ucvm_plugin_data_buffer[j].rho;
	    			} else {
	    				datagap = 1;
	    			}
	    		}
	    	// Reset nn.
	    	nn = 0;
    		}
	    } else {
	    	if (data[i].crust.source == UCVM_SOURCE_NONE) datagap = 1;
	    }
	}
        /* catch the last bits of partial chunk */
        if(nn != 0) {
	    pptr->model_query(ucvm_plugin_pnts_buffer, ucvm_plugin_data_buffer, nn);
	    // Transfer our findings.
	    for (j = 0; j < nn; j++) {
	    	if (ucvm_plugin_data_buffer[j].vp >= 0 && ucvm_plugin_data_buffer[j].vs >= 0 && ucvm_plugin_data_buffer[j].rho >= 0) {
	    		data[index_mapping[j]].crust.source = pptr->model_id;
	    		data[index_mapping[j]].crust.vp = ucvm_plugin_data_buffer[j].vp;
	    		data[index_mapping[j]].crust.vs = ucvm_plugin_data_buffer[j].vs;
	    		data[index_mapping[j]].crust.rho = ucvm_plugin_data_buffer[j].rho;
	    	} else {
	    		datagap = 1;
	    	}
	   } 
        }

	free(index_mapping);
        free(ucvm_plugin_data_buffer);
        free(ucvm_plugin_pnts_buffer);

	if (datagap == 1) {
		return UCVM_CODE_DATAGAP;
	}

	return UCVM_CODE_SUCCESS;
}

/**
 * Fill model structure with the plugin model, if it exists.
 *
 * @param lib_dir The directory where the UCVM libraries were installed ($prefix/lib).
 * @param models_dir The directory where the UCVM models were intalled ($prefix/share/ucvm/model).
 * @param label The label of the plugin model.
 * @param m The model structure to be filled.
 * @return SUCCESS if the model found, FAIL if not.
 */
int ucvm_plugin_get_model(const char *lib_dir, const char *models_dir, const char *label, ucvm_model_t *m) {
	// Does this model exist?
	char libpath[UCVM_MAX_PATH_LEN];
	FILE *fp;

	snprintf(libpath, UCVM_MAX_PATH_LEN, "%s/lib%s.%s", lib_dir, label, SHARED_LIBRARY_EXT);
	if ((fp = fopen(libpath, "r"))) {
		fclose(fp);

		m->mtype = UCVM_MODEL_CRUSTAL;
		m->init = ucvm_plugin_model_init;
		m->finalize = ucvm_plugin_model_finalize;
		m->getversion = ucvm_plugin_model_version;
		m->getlabel = ucvm_plugin_model_label;
		m->setparam = ucvm_plugin_model_setparam;
		m->query = ucvm_plugin_model_query;
		return UCVM_CODE_SUCCESS;
	} else{
		return UCVM_CODE_ERROR;
	}
}

int ucvm_plugin_model_setparam(int id, int param, ...)
{
  va_list ap;
  char *pname;
  char *pvalue;

  ucvm_plugin_model_t *pptr=get_plugin_by_id(id);
  if (!pptr) {
    fprintf(stderr, "Invalid model id.\n");
    return(UCVM_CODE_ERROR);
  }
  if (!pptr->model_set_param) {
	  fprintf(stderr, "Plugin model with id '%d' missing set_param\n", id);
	  return(UCVM_CODE_ERROR);
  }

  va_start(ap, param);
  switch (param) {
  case UCVM_PARAM_MODEL_CONF:
	pname = va_arg(ap, char *);
	pvalue = va_arg(ap, char *);
	pptr->model_set_param(pname, pvalue);
	break;
  default:
    break;
  }

  va_end(ap);

  return(UCVM_CODE_SUCCESS);
}

ucvm_plugin_model_t *get_plugin_by_label(char *label) {
   int i;
   for(i =0; i< plugin_model_initialized; i++) {
     ucvm_modelconf_t *mptr = &(plugin_models[i].model_conf);
     if( strcmp(mptr->label,label) == 0) 
        return &plugin_models[i];
   }
   return(0);
};

ucvm_plugin_model_t *get_plugin_by_id(int id) {
   int i;
   for(i =0; i< plugin_model_initialized; i++) {
     if( plugin_models[i].model_id== id) 
        return &plugin_models[i];
   }
   return(0);
};

ucvm_plugin_model_t *get_plugin_by_order(int id) {
   if(id < UCVM_MAX_MODELS) {
        return &plugin_models[id];
   }
   return(0);
};


