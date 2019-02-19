/*
 * ADIOS is freely available under the terms of the BSD license described
 * in the COPYING file in the top level directory of this source distribution.
 *
 * Copyright (c) 2008 - 2009.  UT-BATTELLE, LLC. All rights reserved.
 */

#ifndef ADIOS_H
#define ADIOS_H

#include <stdint.h>

#include "adios_version.h"
#include "adios_mpi.h"
#include "adios_types.h"
#include "adios_error.h"

// ADIOS - Adaptable IO System

#ifdef __cplusplus
extern "C" {
#endif

/* Most functions return 0 if OK, and !=0 on error 
   which is the value of the variable 'adios_errno'.
   On error, one can use char * adios_get_last_errmsg() from adios_error.h
   to retrieve the error string of the last error. 

   exceptions: int64_t adios_define_var() returns a variable ID, 0 indicates an error
*/

// Global setup using the XML file
// Only processes of the provided communicator can later participate
// in any adios activity
int adios_init (const char * config, MPI_Comm comm);
int adios_is_initialized(void);

int adios_finalize (int mype);

// end user calls for each I/O operation
// modes = "r" = "read", "w" = "write", "a" = "append", "u" = "update"
int adios_open (int64_t * fd, 
                const char * group_name, 
                const char * name,
                const char * mode, 
                MPI_Comm comm
               );

int adios_group_size (int64_t fd_p, 
                      uint64_t data_size,
                      uint64_t * total_size
                     ); 

int adios_write (int64_t fd_p, const char * name, const void * var);

int adios_get_write_buffer (int64_t fd_p, 
                            const char * name,
                            uint64_t * size,
                            void ** buffer
                           );

int adios_read (int64_t fd_p, 
                const char * name, 
                void * buffer,
                uint64_t buffer_size
               );

// OBSOLETE, kept only for backward compatibility of old codes
// Inconsistent behavior with new ADIOS variable naming
int adios_set_path (int64_t fd_p, const char * path);
// OBSOLETE, kept only for backward compatibility of old codes
// name should be the full path of the variable (as it was defined)
// in adios_write(), still the OLD full path should be used otherwise
// the variable is not found in the hash table
int adios_set_path_var (int64_t fd_p, const char * path, const char * name);

int adios_end_iteration (void);

int adios_start_calculation (void);

int adios_stop_calculation (void);

int adios_close (int64_t fd_p);

// ADIOS No-XML API's
int adios_init_noxml (MPI_Comm comm);

// To allocate ADIOS buffer OBSOLETE
int adios_allocate_buffer (
        enum ADIOS_BUFFER_ALLOC_WHEN adios_buffer_alloc_when,
        uint64_t buffer_size
        );

// To set maximum buffer size for each adios_open()...adios_close() operation.
void adios_set_max_buffer_size (uint64_t max_buffer_size_MB);

// To declare a ADIOS group
int adios_declare_group (int64_t * id, 
                         const char * name,
                         const char * time_index, 
                         enum ADIOS_STATISTICS_FLAG stats
                        );

// To free a ADIOS group
int adios_free_group (int64_t id);

// To set time aggregation of a group output in a certain buffer size but
// flush whenever the synced group is being output
int adios_set_time_aggregation(int64_t groupid,
                               uint64_t buffersize,
                               int64_t syncgroupid
                              );

// To select a I/O method for a ADIOS group
int adios_select_method (int64_t group, 
                         const char * method,
                         const char * parameters,
                         const char * base_path
                        );

// To define a ADIOS variable
// Returns a variable ID, which can be used in adios_write_byid()
// 0 return value indicates an error
int64_t adios_define_var (int64_t group_id, 
                          const char * name,
                          const char * path,
                          enum ADIOS_DATATYPES type,
                          const char * dimensions,
                          const char * global_dimensions,
                          const char * local_offsets
                         );

// To remove all variable definitions from a group.
// Use it if you want to have a new set of variables defined
// for the next output step.
int adios_delete_vardefs (int64_t id);

// Return the expected size (in bytes) of a defined variable.
// It is simply the product of local dimensions and byte-size of type.
// It works only if the variable is defined with numeric dimensions or
// the dimension variables are already written with adios_write().
// Input is id returned by adios_define_var().
// Returns 0 on error, check adios_errno for error code
uint64_t adios_expected_var_size (int64_t var_id);

// To set the transform method for a variable just defined 
// var_id is the value returned by adios_define_var
// returns adios_errno (0=OK)
int adios_set_transform (int64_t var_id, const char *transform_type_str);

int adios_define_attribute (int64_t group, 
                            const char * name,
                            const char * path, 
                            enum ADIOS_DATATYPES type,
                            const char * value, 
                            const char * var
                           );

// define an attribute with values. 
// it can define an (1D) array of scalars, 'nelems' elements
// 'values' should point to the array of 'nelems' number of values of the specified type
int adios_define_attribute_byvalue (int64_t group, 
                            const char * name,
                            const char * path, 
                            enum ADIOS_DATATYPES type,
                            int  nelems,
                            const void * values
                           );

int adios_delete_attrdefs (int64_t id);

/** This function does similar function as adios_write. It is, however, used
 * in the following scenario that
 * 1. numbers, instead of a variable, are used to annotate array dimensions, and
 * 2. a variable is written mutiple times on a processor (e.g., AMR codes)
 */
int adios_write_byid (int64_t fd_p, int64_t id, const void * var);

/** Set the application's ID for adios_read_init()
 *  when using a staging method (DATASPACES, DIMES, NSSI or DATATAP).
 *  The ID should be unique for each application accessing the staging area
 *  IN:  id   a number unique for this application
 *  RETURN:       0 if accepted, <0 on error
 *  It is optional to use it before calling adios_init. Default is 1. 
 *  It has no effect for file based methods.
 *  Note: this function is defined both in adios.h and adios_read.h so that
 *  writing-only and reading-only applications can both use it.
 */ 
/*int adios_set_application_id (int id);*/

void adios_timing_write_xml (int64_t fd_p, const char* filename);

// no-xml schema API
// Define adios schema version
// The function implements the same as "schema version="1.1 ""in xml
int adios_define_schema_version (int64_t group_id, const char * schema_version);

// Assign mesh to a variable
// The function implements the same as "var name="Var1" mesh="meshname" " in xml 
int adios_define_var_mesh(int64_t group_id, const char * varname, const char * meshname);

// Define centering of the variable value onto the mesh, centering is "cell" or "point"
int adios_define_var_centering(int64_t group_id, const char * varname, const char * centering);

// Define a external file where mesh variables are written
int adios_define_mesh_file(int64_t group_id, const char * name, const char * file);

// The time-­steps points to time variables using steps, starting from step 0
int adios_define_var_timesteps (const char * timesteps, int64_t group_id, const char * name);

// The time-­steps points to time variables using real time, starting from time 
// Exactly like the time steps except with real numbers
int adios_define_var_timescale (const char * timescale, int64_t group_id, const char * name);

// Describe the padding pattern for output images
// If this number is 4, then the time-steps for images will be padded with 0 up to 4 digit numbers
int adios_define_var_timeseriesformat (const char * timeseries, int64_t group_id, const char * name);

// Use the concept of start, stride and count in all dimensions of a variable to identify a subset of a dataset
int adios_define_var_hyperslab (const char * hyperslab, int64_t group_id, const char * name);

// Describe if the mesh changes over time, and the option is "yes" or "no" 
int adios_define_mesh_timevarying (const char * timevarying, int64_t group_id, const char * name);

// The time-­steps points to time variables using steps, starting from step 0
int adios_define_mesh_timesteps (const char * timesteps, int64_t group_id, const char * name);

// The time-­steps points to time variables using real time, starting from time 0
int adios_define_mesh_timescale (const char * timescale, int64_t group_id, const char * name);

// Represent an integer for padding and formatting output image files
// If this number is 4, then the time-steps for images will be padded with 0 up to 4 digit number
int adios_define_mesh_timeseriesformat (const char * timeseries, int64_t group_id, const char * name);

// Indicates where (which ADIOS group) mesh variables are stored
int adios_define_mesh_group (const char * group, int64_t group_id, const char * name);

// Defines a uniform mesh
// For not requried attributes in this function, please use 0 instead
int adios_define_mesh_uniform (const char * dimensions,
                               const char * origin,
                               const char * spacing,
                               const char * maximum,
                               const char * nspace,
                               int64_t group_id,
                               const char * name);

// Defines a rectilinear mesh
// For not requried attributes in this function, please use 0 instead
int adios_define_mesh_rectilinear (const char * dimensions,
                                   const char * coordinates,
                                   const char * nspace,
                                   int64_t group_id,
                                   const char * name);

// Defines a structured mesh
// For not requried attributes in this function, please use 0 instead
int adios_define_mesh_structured (const char * dimensions,
                                  const char * points,
                                  const char * nspace,
                                  int64_t group_id,
                                  const char * name);

// Define an unstructured mesh
// For not requried attributes in this function, please use 0 instead
int adios_define_mesh_unstructured (const char * points,
                                    const char * data,
                                    const char * count,
                                    const char * cell_type,
                                    const char * npoints,
                                    const char * nspace,
                                    int64_t group_id,
                                    const char * name);


typedef struct
{
    int nmethods; 		// number of available methods
    char ** name;     	// array of transport method names
} ADIOS_AVAILABLE_WRITE_METHODS;

/* Provide the names of transport methods available in the running application
 */
ADIOS_AVAILABLE_WRITE_METHODS * adios_available_write_methods();

void adios_available_write_methods_free (ADIOS_AVAILABLE_WRITE_METHODS *);


#ifdef __cplusplus
}
#endif


#endif
