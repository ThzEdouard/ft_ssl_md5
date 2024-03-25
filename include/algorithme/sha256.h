#ifndef SHA256_H
# define SHA256_H

# include <stdio.h>
# include <stdint.h>
# include <string.h>
# include <stdlib.h>

# define SHA_A 0x6a09e667
# define SHA_B 0xbb67ae85
# define SHA_C 0x3c6ef372
# define SHA_D 0xa54ff53a
# define SHA_E 0x510e527f
# define SHA_F 0x9b05688c
# define SHA_G 0x1f83d9ab
# define SHA_H 0x5be0cd19

# define RIGHTROTATE(x, c) (((x) >> (c)) | ((x) << (32 - (c))))
# define CH(x, y, z) (((x) & (y)) ^ (~(x) & (z)))
# define MAJ(x, y, z) (((x) & (y)) ^ ((x) & (z)) ^ ((y) & (z)))
#define EP0(x) (RIGHTROTATE(x,2) ^ RIGHTROTATE(x,13) ^ RIGHTROTATE(x,22))
#define EP1(x) (RIGHTROTATE(x,6) ^ RIGHTROTATE(x,11) ^ RIGHTROTATE(x,25))
#define SIG0(x) (RIGHTROTATE(x,7) ^ RIGHTROTATE(x,18) ^ ((x) >> 3))
#define SIG1(x) (RIGHTROTATE(x,17) ^ RIGHTROTATE(x,19) ^ ((x) >> 10))

typedef struct s_sha256
{
	uint32_t	datalen;
	uint64_t	bitlen;
	uint8_t		data[64];
	uint32_t	buffer[8];
	uint8_t		digest[32];
}				t_sha256;

t_sha256		sha_init();
void			sha_update(t_sha256 *ctx, uint8_t *input_buf, size_t input_len);
void			sha_step(uint32_t *buffer, uint8_t *input);
void			sha_finalize(t_sha256 *ctx);
uint8_t			*sha256(const char *str);

# endif