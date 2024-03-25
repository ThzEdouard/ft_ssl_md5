# include "../../include/algorithme/sha256.h"

static uint32_t K[] = {0x428a2f98, 0x71374491, 0xb5c0fbcf, 0xe9b5dba5, 0x3956c25b, 0x59f111f1, 0x923f82a4, 0xab1c5ed5,
					   0xd807aa98, 0x12835b01, 0x243185be, 0x550c7dc3, 0x72be5d74, 0x80deb1fe, 0x9bdc06a7, 0xc19bf174,
					   0xe49b69c1, 0xefbe4786, 0x0fc19dc6, 0x240ca1cc, 0x2de92c6f, 0x4a7484aa, 0x5cb0a9dc, 0x76f988da,
					   0x983e5152, 0xa831c66d, 0xb00327c8, 0xbf597fc7, 0xc6e00bf3, 0xd5a79147, 0x06ca6351, 0x14292967,
					   0x27b70a85, 0x2e1b2138, 0x4d2c6dfc, 0x53380d13, 0x650a7354, 0x766a0abb, 0x81c2c92e, 0x92722c85,
					   0xa2bfe8a1, 0xa81a664b, 0xc24b8b70, 0xc76c51a3, 0xd192e819, 0xd6990624, 0xf40e3585, 0x106aa070,
					   0x19a4c116, 0x1e376c08, 0x2748774c, 0x34b0bcb5, 0x391c0cb3, 0x4ed8aa4a, 0x5b9cca4f, 0x682e6ff3,
					   0x748f82ee, 0x78a5636f, 0x84c87814, 0x8cc70208, 0x90befffa, 0xa4506ceb, 0xbef9a3f7, 0xc67178f2};

t_sha256	sha_init()
{
	t_sha256 ctx;

	ctx.datalen = 0;
	ctx.bitlen = 0;

	ctx.buffer[0] = SHA_A;
	ctx.buffer[1] = SHA_B;
	ctx.buffer[2] = SHA_C;
	ctx.buffer[3] = SHA_D;
	ctx.buffer[4] = SHA_E;
	ctx.buffer[5] = SHA_F;
	ctx.buffer[6] = SHA_G;
	ctx.buffer[7] = SHA_H;

	return (ctx);
}

void	sha_update(t_sha256 *ctx, uint8_t *input_buf, size_t input_len)
{
	for (uint32_t i = 0; i < input_len; ++i)
	{
		ctx->data[ctx->datalen++] = input_buf[i];
		if(ctx->datalen % 64 == 0)
		{
			sha_step(ctx->buffer, ctx->data);
			ctx->bitlen += 512;
			ctx->datalen = 0;
		}
	}
}

void	sha_finalize(t_sha256 *ctx)
{
	uint32_t i;
	i = ctx->datalen;
	if (ctx->datalen < 56) {
		ctx->data[i++] = 0x80;
		while (i < 56)
			ctx->data[i++] = 0x00;
	}
	else {
		ctx->data[i++] = 0x80;
		while (i < 64)
			ctx->data[i++] = 0x00;
		sha_step(ctx->buffer, ctx->data);
		memset(ctx->data, 0, 56);
	}

	ctx->bitlen += ctx->datalen * 8;
	ctx->data[63] = ctx->bitlen;
	ctx->data[62] = ctx->bitlen >> 8;
	ctx->data[61] = ctx->bitlen >> 16;
	ctx->data[60] = ctx->bitlen >> 24;
	ctx->data[59] = ctx->bitlen >> 32;
	ctx->data[58] = ctx->bitlen >> 40;
	ctx->data[57] = ctx->bitlen >> 48;
	ctx->data[56] = ctx->bitlen >> 56;
	sha_step(ctx->buffer, ctx->data);

	for (i = 0; i < 4; ++i) {
		ctx->digest[i]      = (ctx->buffer[0] >> (24 - i * 8)) & 0x000000ff;
		ctx->digest[i + 4]  = (ctx->buffer[1] >> (24 - i * 8)) & 0x000000ff;
		ctx->digest[i + 8]  = (ctx->buffer[2] >> (24 - i * 8)) & 0x000000ff;
		ctx->digest[i + 12] = (ctx->buffer[3] >> (24 - i * 8)) & 0x000000ff;
		ctx->digest[i + 16] = (ctx->buffer[4] >> (24 - i * 8)) & 0x000000ff;
		ctx->digest[i + 20] = (ctx->buffer[5] >> (24 - i * 8)) & 0x000000ff;
		ctx->digest[i + 24] = (ctx->buffer[6] >> (24 - i * 8)) & 0x000000ff;
		ctx->digest[i + 28] = (ctx->buffer[7] >> (24 - i * 8)) & 0x000000ff;
	}
}

void	sha_step(uint32_t *buffer, uint8_t *input)
{
	uint32_t AA = buffer[0];
	uint32_t BB = buffer[1];
	uint32_t CC = buffer[2];
	uint32_t DD = buffer[3];
	uint32_t EE = buffer[4];
	uint32_t FF = buffer[5];
	uint32_t GG = buffer[6];
	uint32_t HH = buffer[7];

	uint32_t w[64],i, j;
	for (i = 0, j = 0; i < 16; ++i, j += 4)
		w[i] = (input[j] << 24) | (input[j + 1] << 16) | (input[j + 2] << 8) | (input[j + 3]);
	for ( ; i < 64; ++i)
		w[i] = SIG1(w[i - 2]) + w[i - 7] + SIG0(w[i - 15]) + w[i - 16];

	for (i = 0; i < 64; ++i)
	{
		uint32_t t1 = HH + EP1(EE) + CH(EE, FF, GG) + K[i] + w[i];
		uint32_t t2 = EP0(AA) + MAJ(AA, BB, CC);
		HH = GG;
		GG = FF;
		FF = EE;
		EE = DD + t1;
		DD = CC;
		CC = BB;
		BB = AA;
		AA = t1 + t2;
	}

	buffer[0] += AA;
	buffer[1] += BB;
	buffer[2] += CC;
	buffer[3] += DD;
	buffer[4] += EE;
	buffer[5] += FF;
	buffer[6] += GG;
	buffer[7] += HH;
}

uint8_t	*sha256(const char *str)
{
	uint8_t	*result = malloc(32 * sizeof(uint8_t));
	if (!result)
		return (NULL);
	t_sha256 ctx = sha_init();
	sha_update(&ctx, (uint8_t *)str, strlen(str));
	sha_finalize(&ctx);

	memcpy(result, ctx.digest, 32);
	return (result);
}

//a changer 
void	print_sha256hash(uint8_t *p){
	for(unsigned int i = 0; i < 32; ++i){
		printf("%02x", p[i]);
	}
}