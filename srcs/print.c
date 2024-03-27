# include "../include/ft_ssl.h"

static void	print_stdin(t_option *opt, uint8_t *hash, uint8_t *input)
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

static void	print_string(t_option *opt, uint8_t *hash, uint8_t *input)
{
	if (opt->flags & FLAGS_Q)
		opt->cmd.cmd_print(hash);
	else if (opt->flags & FLAGS_R) {
		opt->cmd.cmd_print(hash);
		printf(" \"%s\"", input);
	} else {
		printf("%s (", opt->cmd.cmd);
		printf("\"%s\"", input);
		printf(") = ");
		opt->cmd.cmd_print(hash);
	}
	printf("\n");
}

static void	print_file(t_option *opt, uint8_t *hash, uint8_t *input)
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
		printf(") = ");
		opt->cmd.cmd_print(hash);
	}
	printf("\n");
}

static void	pross_file(t_option *opt, uint8_t *filename)
{
	uint8_t	*hash = NULL;
	char	*input = NULL;
	int fd = open((const char *)filename, O_RDONLY);
	if (fd == -1)
	{
		printf("ft_ssl: %s: %s: %s\n", opt->cmd.cmd, filename, strerror(errno));
		return ;
	}
	input = ft_read_fd(fd);
	if (!input)
	{
		close(fd);
		return;
	}
	hash = opt->cmd.cmd_function(input);
	print_file(opt, hash, filename);
	ft_free(hash);
	ft_free(input);
	close(fd);
}

void	print_result(t_option *opt)
{
	if (opt->flags & FLAGS_P || (!opt->file && !(opt->flags & FLAGS_S)))
		print_stdin(opt, opt->hash_input, opt->input);
	if (opt->flags & FLAGS_S)
		print_string(opt, opt->hash_str, opt->str);
	if (opt->file)
		for (uint32_t i = 0; i < opt->size_file; ++i)
			pross_file(opt, opt->file[i]);
}