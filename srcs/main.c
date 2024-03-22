# include "../include/ft_ssl.h"


void print_hash(uint8_t *p){
    for(unsigned int i = 0; i < 16; ++i){
        printf("%02x", p[i]);
    }
    printf("\n");
}

int	main(void)
{
	uint8_t *f = md5("Hello, World!");
	print_hash(f);
	free(f);
	return (0);
}