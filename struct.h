#ifndef STRUCT_H
# define STRUCT_H

# include <OpenCL/opencl.h>

typedef struct		s_opencl
{
	cl_context		context;
	cl_int			nb_devices;
	cl_device_id	device;
	cl_platform_id	platform;
	cl_uint			nb_platforms;
}					t_opencl;

#endif
