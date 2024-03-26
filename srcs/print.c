# include "../include/ft_ssl.h"

#define BUFFER_SIZE 4096

char *ft_getline(int fd) {
	char *input = NULL;
	char buffer[BUFFER_SIZE];
	ssize_t bytesRead;
	size_t totalBytesRead = 0;

	while ((bytesRead = read(fd, buffer, BUFFER_SIZE)) > 0) {
		char *temp = malloc(totalBytesRead + bytesRead + 1);
		if (temp == NULL) {
			if (input != NULL) free(input);
			return NULL;
		}
		if (input != NULL) {
			memcpy(temp, input, totalBytesRead);
			free(input);
		}
		input = temp;
		memcpy(input + totalBytesRead, buffer, bytesRead);
		totalBytesRead += bytesRead;
	}

	if (bytesRead == -1) {
		if (input != NULL)
			free(input);
		return NULL;
	}
	if (input != NULL)
		input[totalBytesRead] = '\0';
	return input;
}

void	print_stdin(t_option *opt, uint8_t *hash, uint8_t *input)
{
	if (opt->flags & FLAGS_Q && opt->flags & FLAGS_P)
	{
		printf("%s\n", input);
		opt->cmd.cmd_print(hash);
	} else
	{
		printf("(");
		opt->flags & FLAGS_P ? printf("\"%s\"", input) : printf("%s", "stdin");
		printf(")= ");
		opt->cmd.cmd_print(hash);
	}
	printf("\n");
}

void	print_string(t_option *opt, uint8_t *hash, uint8_t *input)
{
	if (opt->flags & FLAGS_Q)
		opt->cmd.cmd_print(hash);
	else if (opt->flags & FLAGS_R) {
		opt->cmd.cmd_print(hash);
		printf(" \"%s\"", input);
	} else {
		printf("%s (", opt->cmd.cmd);
		printf("\"%s\"", input);
		printf(")= ");
		opt->cmd.cmd_print(hash);
	}
	printf("\n");
}

void	print_file(t_option *opt, uint8_t *hash, uint8_t *input)
{
	if (opt->flags & FLAGS_Q)
		opt->cmd.cmd_print(hash);
	else if (opt->flags & FLAGS_R)
	{
		opt->cmd.cmd_print(hash);
		printf(" %s", input);
	}
	else
	{
		printf("%s (", opt->cmd.cmd);
		printf("%s", input);
		printf(")= ");
		opt->cmd.cmd_print(hash);
	}
	printf("\n");
}

void	pross_file(t_option *opt, uint8_t *filename)
{
	int fd = open((const char *)filename, O_RDONLY);
	if (fd == -1)
	{
		printf("ft_ssl: %s: %s: %s\n", opt->cmd.cmd, filename, strerror(errno));
		return ;
	}

	char *input = ft_getline(fd);
	if (!input)
	{
		close(fd);
		return;
	}
	uint8_t *hash = opt->cmd.cmd_function(input);
	print_file(opt, hash, filename);
	if (hash)
		free(hash);
	free(input);
	close(fd);
}

void	print_result(t_option *opt)
{
	if (opt->flags & FLAGS_P || !opt->file)
		print_stdin(opt, opt->hash_input, opt->input);
	if (opt->flags & FLAGS_S)
		print_string(opt, opt->hash_str, opt->str);
	if (opt->file)
		for (uint32_t i = 0; i < opt->size_file; ++i)
			pross_file(opt, opt->file[i]);
}