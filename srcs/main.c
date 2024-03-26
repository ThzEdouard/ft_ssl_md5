# include "../include/ft_ssl.h"


static void ft_free(void *p)
{
	if (p)
		free(p);
}

static void init(t_option *opt)
{
	opt->file = NULL;
	opt->input = NULL;
	opt->hash_input = NULL;
	opt->str = NULL;
	opt->hash_str = NULL;
	opt->flags = 0;
	opt->size_file = 0;
}

static void hash_argv(t_option *opt)
{
	opt->hash_input = opt->cmd.cmd_function((const char *)opt->input);
	if (opt->input)
	{
		size_t input_length = strlen((char *)opt->input);
		if (input_length > 0 && opt->input[input_length - 1] == '\n') {
			opt->input[input_length - 1] = '\0';
		}
	}
	opt->hash_str = opt->cmd.cmd_function((const char *)opt->str);
}

static void cleanup(t_option *opt)
{
	ft_free(opt->file);
	ft_free(opt->input);
	ft_free(opt->hash_input);
	ft_free(opt->str);
	ft_free(opt->hash_str);
}

int	main(int argc, char *argv[])
{
	t_command	cmd;
	t_option	opt;
	uint32_t	flags_index;
	if (argc < 2)
		return (printf(USAGE), 1);
	cmd = select_cmd(argv[1]);
	if (!cmd.cmd)
		return (1);
	init(&opt);
	opt.cmd = cmd;
	flags_index = flags_or_index((uint32_t)argc, argv);
	opt.flags = getflags(flags_index);
	set_string_or_file(&opt, argv, argc, argv_index(flags_index));
	if ((opt.flags & FLAGS_P) || !opt.file)
		opt.input = (uint8_t *)ft_getline(0);
	hash_argv(&opt);
	print_result(&opt);
	cleanup(&opt);
	return (0);
}