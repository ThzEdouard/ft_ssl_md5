#include "../../include/algorithme/md5.h"


t_md5Context init()
{
	t_md5Context result;

	result.size = (uint64_t)0;
	result.state[0] = (uint32_t)A;
	result.state[1] = (uint32_t)B;
	result.state[2] = (uint32_t)C;
	result.state[3] = (uint32_t)B;
	return (result);
}

char	*md5(const char *str)
{

}