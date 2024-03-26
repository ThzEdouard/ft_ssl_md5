#ifndef MD5_H
# define MD5_H

# include <stdio.h>
# include <stdint.h>
# include <string.h>
# include <stdlib.h>

# include "../42-libft/include/libft.h"

# define A 0x67452301
# define B 0xefcdab89
# define C 0x98badcfe
# define D 0x10325476

# define F(X, Y, Z) ((X & Y) | (~X & Z))
# define G(X, Y, Z) ((X & Z) | (Y & ~Z))
# define H(X, Y, Z) (X ^ Y ^ Z)
# define I(X, Y, Z) (Y ^ (X | ~Z))

# define LEFTROTATE(x, c) (((x) << (c)) | ((x) >> (32 - (c))))

typedef struct
{
	uint64_t	size;
	uint32_t	buffer[4];
	uint8_t		input[64];
	uint8_t		digest[16];
}				t_md5Context;


t_md5Context	md5_init();
void			md5_update(t_md5Context *ctx, uint8_t *input_buf, size_t input_len);
void			md5_step(uint32_t *buffer, uint32_t *input);
void			md5_finalize(t_md5Context *ctx);
uint8_t			*md5(const char *str);
void			print_md5hash(uint8_t *p);


#endif