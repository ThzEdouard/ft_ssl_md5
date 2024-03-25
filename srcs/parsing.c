# include "../include/ft_ssl.h"

static const char	*flags[] = {"-p", "-q", "-r", "-s", NULL};

static const t_command command_hash_map[] =
{
	{"md5", md5},
	{"sha256", NULL},
	{NULL, NULL}
};

cmdFunction select_cmd(const char *cmd)
{
	for(uint32_t i = 0; command_hash_map[i].cmd != NULL; ++i)
		if (strcmp((char *)cmd, command_hash_map[i].cmd) == 0)
			return (command_hash_map[i].cmd_function);
	printf(COMMAND_USAGE, cmd);
	return (NULL);
}

uint32_t flags_or_index(uint32_t argc, char *argv[])
{
	uint32_t x, index, result = 0;

	for (index = 2; index < argc; ++index)
	{
		for(x = 0; flags[x] != NULL; ++x)
		{
			if (strcmp(flags[x], argv[index]) == 0)
			{
				result |= FLAGS(x);
				break;
			}
		}
		if (flags[x] == NULL)
			break;
	}
	return (result << 16) | (index);
}

void	set_string_or_file(t_option *option, char **argv, int argc, int index)
{
	int i = 0;
	for ( ;index < argc; ++index)
	{
		option->string_file[i] = (uint8_t *)argv[index];
		++i;
	}
}

uint32_t	argv_index(uint32_t flag_index)
{
	return (flag_index & 0xFFFF);
}

uint32_t	getflags(uint32_t flag_index)
{
	return  (flag_index >> 16);
}