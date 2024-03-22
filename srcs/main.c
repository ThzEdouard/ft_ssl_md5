# include "../include/ft_ssl.h"


void print_hash(uint8_t *p){
	for(unsigned int i = 0; i < 16; ++i){
		printf("%02x", p[i]);
	}
	printf("\n");
}

uint32_t	index_i(uint32_t flag_index)
{
	return (flag_index & 0xFFFF);
}

uint32_t	flags(uint32_t flag_index)
{
	return  (flag_index >> 16);
}

int	main(int argc, char *argv[])
{
	if (argc < 2)
		return (printf(USAGE), 1);
	cmdFunction	cmd = select_cmd(argv[1]);
	if (!cmd)
		return (1);
	uint32_t flags_index = getflags((uint32_t)argc, argv);

	printf("Résultat des indicateurs : %u\n", flags(flags_index));
	printf("Index final : %u\n", index_i(flags_index));
	uint8_t *f = cmd("Hello");
	print_hash(f);
	free(f);
	return (0);
}