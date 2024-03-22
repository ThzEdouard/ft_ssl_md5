#ifndef FT_SSL_H
# define FT_SSL_H

# include "./algorithme/md5.h"

typedef uint8_t	*(*cmdFunction)(const char *);
typedef struct s_command
{
	const char	*cmd;
	cmdFunction		cmd_function;
}				t_command;

typedef struct s_option
{
	uint32_t	flags;
	uint8_t		**string_file;
	cmdFunction	cmd;
}			t_option;

typedef struct s_result
{
	uint8_t	*filename;
	uint8_t	*hash;
}			t_result;

// parsing.c
cmdFunction select_cmd(const char *cmd);
uint32_t getflags(uint32_t argc, char *argv[]);

# define USAGE "usage: ft_ssl command [flags] [file/string]\n"
# define COMMAND_USAGE "ft_ssl: Error: '%s' is an invalid command.\n\nCommands:\nmd5\nsha256\nFlags:\n-p -q -r -s\n"

# define FLAGS(x) (1 << x)

#endif