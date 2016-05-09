#include "get_devices_info.h"

static char	*get_str_device_info(cl_device_info param_type, cl_device_id *device_id)
{
	size_t	size;
	cl_int	err;
	char	*str;

	err = clGetDeviceInfo(*device_id, param_type, 0, NULL, &size);
	if (err != CL_SUCCESS)
		return (NULL);
	if (!(str = malloc(sizeof(char) * size)))
		return (NULL);
	err = clGetDeviceInfo(*device_id, param_type, size, str, NULL);
	if (err != CL_SUCCESS)
		return (NULL);
	return (str);
}

static int	display_device_extensions(cl_device_id *device_id)
{
	char	*extensions;

	if (!(extensions= get_str_device_info(CL_DEVICE_EXTENSIONS, device_id)))
		return (0);
	printf("\t\tDevice extensions: %s\n", extensions);
	free(extensions);
	return (1);
}

static int	display_mem_size(cl_device_id *device_id)
{
	cl_int		err;
	cl_ulong	mem_size;

	err = clGetDeviceInfo(*device_id, CL_DEVICE_GLOBAL_MEM_SIZE, sizeof(cl_ulong), &mem_size, NULL);
	if (err != CL_SUCCESS)
		return (0);
	printf("\t\tGlobal memory size: %lluMB (%lluGB)\n", mem_size / (1024 * 1024), mem_size / (1024 * 1024 * 1024));
	err = clGetDeviceInfo(*device_id, CL_DEVICE_LOCAL_MEM_SIZE, sizeof(cl_ulong), &mem_size, NULL);
	if (err != CL_SUCCESS)
		return (0);
	printf("\t\tLocal memory size: %lluB (%lluKB)\n", mem_size, mem_size / 1024);
	return (1);
}

static int	display_name(cl_device_id *device_id)
{
	char	*str;

	if (!(str = get_str_device_info(CL_DEVICE_NAME, device_id)))
		return (0);
	printf("\t\tName: %s\n", str);
	free(str);
	if (!(str = get_str_device_info(CL_DEVICE_VENDOR, device_id)))
		return (0);
	printf("\t\tVendor: %s\n", str);
	free(str);
	if (!(str = get_str_device_info(CL_DEVICE_VERSION, device_id)))
		return (0);
	printf("\t\tDevice: %s\n", str);
	free(str);
	if (!(str = get_str_device_info(CL_DRIVER_VERSION, device_id)))
		return (0);
	printf("\t\tDriver: %s\n", str);
	free(str);
	return (1);
}

static int	display_working_size(cl_device_id *device_id)
{
	size_t	size;
	cl_uint	max_workitem_dim;
	cl_int	err;
	size_t	*work_item_size;
	int		i;
	
	err = clGetDeviceInfo(*device_id, CL_DEVICE_MAX_WORK_GROUP_SIZE, sizeof(size_t), &size, NULL);
	if (err != CL_SUCCESS)
		return (0);
	printf("\t\tMax work group size: %lu\n", size);
	err = clGetDeviceInfo(*device_id, CL_DEVICE_MAX_WORK_ITEM_DIMENSIONS, sizeof(cl_uint), &max_workitem_dim, NULL);
	if (err != CL_SUCCESS)
		return (0);
	printf("\t\tMax work item dimensions: %u\n", max_workitem_dim);
	if (!(work_item_size = malloc(sizeof(size_t) * max_workitem_dim)))
		return (0);
	err = clGetDeviceInfo(*device_id, CL_DEVICE_MAX_WORK_ITEM_SIZES, sizeof(size_t) * max_workitem_dim, work_item_size, NULL);
	if (err != CL_SUCCESS)
		return (0);
	printf("\t\tWork item size: (");
	for (i = 0; i < max_workitem_dim; i++)
	{
		printf("%lu", work_item_size[i]);
		if (i < max_workitem_dim - 1)
			printf(",");
	}
	printf(")\n");
	return (1);
}

static int	display_address_space(cl_device_id *device_id)
{
	cl_int		err;
	cl_uint		addr_size;

	err = clGetDeviceInfo(*device_id, CL_DEVICE_ADDRESS_BITS, sizeof(cl_uint), &addr_size, NULL);
	if (err != CL_SUCCESS)
		return (0);
	printf("\t\tAddress space size: %u\n", addr_size);
	return (1);
}

static int	display_device_available(cl_device_id *device_id)
{
	cl_int		err;
	cl_bool		available;

	err = clGetDeviceInfo(*device_id, CL_DEVICE_AVAILABLE, sizeof(cl_bool), &available, NULL);
	if (err != CL_SUCCESS)
		return (0);
	printf("\t\tDevice available: ");
	if (available == CL_TRUE)
		printf("Yes\n");
	else
		printf("No\n");
	return (1);
}

/*
 * There is implementation in order to get useful device info
 * I haven't implemented the check of CL_DEVICE_DOUBLE_FP_CONFIG which is useful if you have specifique needs about
 * precision of floating point compute
 */
static int	display_device_info(cl_device_id *device_id)
{
	if (!display_name(device_id))
		return (0);
	if (!display_mem_size(device_id))
		return (0);
	if (!display_working_size(device_id))
		return (0);
	if (!display_address_space(device_id))
		return (0);
	if (!display_device_available(device_id))
		return (0);
	if (!display_device_extensions(device_id))
		return (0);
	return (1);
}

static int	try_get_devices_info(cl_platform_id *platform_id)
{
	cl_int			err;
	cl_uint			nb_devices;
	cl_device_id	*devices_id;
	cl_uint			j;

	err = clGetDeviceIDs(*platform_id, CL_DEVICE_TYPE_ALL, 0, NULL, &nb_devices);//Get the number of device in the platform in order to malloc the needed size
	if (err != CL_SUCCESS)
		return (0);
	printf("There is %u devices\n", nb_devices);
	if (!(devices_id = malloc(sizeof(cl_device_id) * nb_devices)))//Malloc of the device_id
		return (0);
	err = clGetDeviceIDs(*platform_id, CL_DEVICE_TYPE_ALL, nb_devices, devices_id, NULL);//Fill devices_id with all devices id
	if (err != CL_SUCCESS)
		return (0);
	for (j = 0; j < nb_devices; j++)
	{
		printf("\tDevices: %u\n", j);
		display_device_info(devices_id + j);
	}
	return (1);
}

void		get_devices_info(cl_platform_id *platform_id)
{
	if (!try_get_devices_info(platform_id))
		printf("Unable to get devices of platform\n");
}
