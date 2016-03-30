#include "create_context.h"

int		create_context(t_opencl *opencl)
{
	cl_int		err;

	/*
	 * This will get the first opencl platform in opencl->platform and the total number of platform in
	 * opencl->nb_platforms
	 */
	err = clGetPlatformIDs(1, &(opencl->platform), &(opencl->nb_platforms));
	if (err != CL_SUCCESS)
	{
		printf("Something wrong append in clGetPlatformIDs\n");
	}
	if (opencl->nb_platforms <= 0)
	{
		printf("No opencl platform found\n");
		return (0);
	}

	/*
	 * This array define the properties of the context creation.
	 * In this example I only set CL_CONTEXT_PLATFORM, to choose wich platform use in the context creation but there is
	 * a lot of other parameter, like CL_GL_CONTEXT_KHR to bind opencl to opengl (to share buffer).
	 * For more info on this check the man page.
	 */
	cl_context_properties contextProperties[] =
	{
		CL_CONTEXT_PLATFORM,
		(cl_context_properties)opencl->platform,
		0
	};
	opencl->context = clCreateContextFromType(
			contextProperties,
			CL_DEVICE_TYPE_GPU,//OpenCL work on a lot of devices (CPU, GPU, accelaration card, ...). Here we choose only the GPU
			NULL, //Here you can set a callback that will be called if an error occure in the context (for more info check the man page
			NULL, //Parameter for the callback
			&err
		);
	if (err != CL_SUCCESS)
	{
		printf("Context creation fail\n");
		return (0);
	}
	return (1);
}
