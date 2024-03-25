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
	cmdFunction	cmd = select_cmd(argv[1]);
	if (!cmd)
		return (1);
	t_option	opt;
	uint32_t	flags_index = flags_or_index((uint32_t)argc, argv);

	opt.cmd = cmd;
	opt.flags = getflags(flags_index);
	set_string_or_file(&opt, argv, argc, argv_index(flags_index));

	pross_stdin(cmd, argv[1], &opt);
	
	// for (int i = 0; opt.string_file[i] != NULL; ++i)
	// 	printf("%s\n", opt.string_file[i]);
	// print_hash(sha256("Hello!"));
	// printf("Résultat des indicateurs : %u\n", getflags(flags_index));
	// printf("Index final : %u\n", argv_index(flags_index));
	// uint8_t *f = cmd("Hello");
	// print_hash(f);
	// free(f);
	return (0);
}