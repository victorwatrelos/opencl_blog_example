#include "get_devices_info.h"

static char	*get_str_platform_info(cl_platform_info param_type, cl_platform_id *platform_id)
{
	size_t	size;
	cl_int	err;
	char	*str;

	err = clGetPlatformInfo(*platform_id, param_type, 0, NULL, &size);
	if (err != CL_SUCCESS)
		return (NULL);
	if (!(str = malloc(sizeof(char) * size)))
		return (NULL);
	err = clGetPlatformInfo(*platform_id, param_type, size, str, NULL);
	if (err != CL_SUCCESS)
		return (NULL);
	return (str);
}

/*
 * All clGetPlatformInfo return a string
 */
static int	display_platform_info(cl_platform_id *platform_id)
{
	char	*profile;
	char	*version;
	char	*vendor;
	char	*name;
	char	*extensions;

	if (!(profile = get_str_platform_info(CL_PLATFORM_PROFILE, platform_id)))
		return (0);
	printf("\tProfile: %s\n", profile);
	free(profile);
	if (!(version = get_str_platform_info(CL_PLATFORM_VERSION, platform_id)))
		return (0);
	printf("\tVersion: %s\n", version);
	free(version);
	if (!(name = get_str_platform_info(CL_PLATFORM_NAME, platform_id)))
		return (0);
	printf("\tName: %s\n", name);
	free(name);
	if (!(vendor = get_str_platform_info(CL_PLATFORM_VENDOR, platform_id)))
		return (0);
	printf("\tVendor: %s\n", vendor);
	free(vendor);
	if (!(extensions = get_str_platform_info(CL_PLATFORM_EXTENSIONS, platform_id)))
		return (0);
	printf("\tExtensions: %s\n", extensions);
	free(extensions);
	return (1);
}

static int	try_get_platforms_info(void)
{
	cl_uint			nb_platforms;
	cl_platform_id	*platforms;
	cl_uint			j;
	cl_int			err;

	err = clGetPlatformIDs(0, NULL, &nb_platforms);
	if (err != CL_SUCCESS)
		return (0);
	printf("There is %u platforms\n", nb_platforms);
	if (!(platforms = malloc(sizeof(cl_platform_id) * nb_platforms)))
		return (0);
	err = clGetPlatformIDs(nb_platforms, platforms, NULL);
	if (err != CL_SUCCESS)
		return (0);
	for (j = 0; j < nb_platforms; j++)
	{
		printf("Platform %u\n", j);
		if (!display_platform_info(platforms + j))
			printf("Unable to find platform info for platform %d\n", j);
		get_devices_info(platforms + j);
	}
	free(platforms);
	return (1);
}

void		get_platforms_info(void)
{
	if (!try_get_platforms_info())
		printf("Unable to get opencl platforms\n");
}
