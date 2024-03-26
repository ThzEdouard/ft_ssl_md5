#ifndef FT_SSL_H
# define FT_SSL_H

# include "./algorithme/md5.h"
# include "./algorithme/sha256.h"

# include <unistd.h>
# include <string.h>
# include <fcntl.h>
# include <errno.h>

typedef uint8_t	*(*cmdFunction)(const char *);
typedef void	(*cmdPrint)(uint8_t *);
typedef struct s_command
{
	const char	*cmd;
	cmdFunction		cmd_function;
	cmdPrint		cmd_print;
}				t_command;

typedef struct s_option
{
	uint32_t	flags;
	uint8_t		*input;
	uint8_t		*hash_input;
	uint8_t		*str;
	uint8_t		*hash_str;
	uint8_t		**file;
	uint32_t	size_file;
	t_command	cmd;
}			t_option;

// parsing.c
t_command	select_cmd(const char *cmd);
uint32_t	flags_or_index(uint32_t argc, char *argv[]);
uint32_t	argv_index(uint32_t flag_index);
uint32_t	getflags(uint32_t flag_index);
void		set_string_or_file(t_option *option, char **argv, int argc, int index);
//print.c
void	print_result(t_option *opt);

# define USAGE "usage: ft_ssl command [flags] [file/string]\n"
# define COMMAND_USAGE "ft_ssl: Error: '%s' is an invalid command.\n\nCommands:\nmd5\nsha256\nFlags:\n-p -q -r -s\n"

# define FLAGS(x) (1 << x)

# define FLAGS_P 1 << 0
# define FLAGS_Q 1 << 1
# define FLAGS_R 1 << 2
# define FLAGS_S 1 << 3

#endif