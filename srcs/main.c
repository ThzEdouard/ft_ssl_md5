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
	uint32_t flags_index = flags_or_index((uint32_t)argc, argv);

	print_hash(sha256("Hello!"));
	printf("Résultat des indicateurs : %u\n", getflags(flags_index));
	printf("Index final : %u\n", argv_index(flags_index));
	uint8_t *f = cmd("Hello");
	print_hash(f);
	free(f);
	return (0);
}