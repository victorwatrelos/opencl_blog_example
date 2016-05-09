#include "create_context.h"
#include "get_platforms_info.h"

int		main(void)
{
	t_opencl	opencl;

	get_platforms_info();
	/*
	if (!create_context(&opencl))//Get gpu context
		return (1);
		*/
	return (0);
}
