# include "../include/ft_ssl.h"


void print_hash(uint8_t *p){
	for(unsigned int i = 0; i < 32; ++i){
		printf("%02x", p[i]);
	}
	printf("\n");
}

int	main(int argc, char *argv[])
{
	if (argc < 2)
		return (printf(USAGE), 1);
	t_command	cmd = select_cmd(argv[1]);
	if (!cmd.cmd)
		return (1);
	t_option	opt;
	uint32_t	flags_index = flags_or_index((uint32_t)argc, argv);

	opt.cmd = cmd;
	opt.flags = getflags(flags_index);
	set_string_or_file(&opt, argv, argc, argv_index(flags_index));

	if (opt.flags & FLAGS_P)
		print_stdin(&opt, opt.cmd.cmd_function("hello"), "hello");
	if (opt.flags & FLAGS_S)
	{
		print_string(&opt, opt.cmd.cmd_function((const char *)opt.string_file[0]), (const char *)opt.string_file[0]);
		for (uint32_t i = 1; opt.string_file[i] != NULL; ++i)
			pross_file(&opt, opt.string_file[i]);
	}
	else
		for (uint32_t i = 0; opt.string_file[i] != NULL; ++i)
			pross_file(&opt, opt.string_file[i]);
	return (0);
}