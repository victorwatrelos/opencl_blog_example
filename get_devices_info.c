#include "get_devices_info.h"

static int	display_platform_info(cl_platform_id *platform_id)
{
	size_t	size;
	char	*profile;
	int		err;

	err = clGetPlatformInfo(*platform_id, CL_PLATFORM_PROFILE, 0, NULL, &size);
	if (err != CL_SUCCESS)
		return (0);
	profile = malloc(sizeof(char) * size);
	err = clGetPlatformInfo(*platform_id, CL_PLATFORM_PROFILE, size, profile, NULL);
	if (err != CL_SUCCESS)
		return (0);
	printf("Profile: %s\n", profile);
	return (1);
}

void		get_devices_info(void)
{
	cl_uint			nb_platforms;
	cl_platform_id	*platforms;
	cl_int			j;

	clGetPlatformIDs(0, NULL, &nb_platforms);
	platforms = malloc(sizeof(cl_platform_id) * nb_platforms);
	clGetPlatformIDs(nb_platforms, platforms, NULL);
	printf("There is %u platforms\n", nb_platforms);
	for (j = 0; j < nb_platforms; j++)
	{
		display_platform_info(platforms + j);
	}
	free(platforms);
}
