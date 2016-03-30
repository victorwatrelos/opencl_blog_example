#include "create_context.h"

int		main(void)
{
	t_opencl	opencl;

	if (!create_context(&opencl))//Get gpu context
		return (1);
	return (0);
}
