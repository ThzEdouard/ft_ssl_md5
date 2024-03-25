# include "../include/ft_ssl.h"

#define BUFFER_SIZE 4096
char *ft_getline(int fd) {
    char *input = NULL;
    char buffer[BUFFER_SIZE];
    ssize_t bytesRead;
    size_t totalBytesRead = 0;
    size_t inputSize = 0;

    // Lecture du fichier
    while ((bytesRead = read(fd, buffer, BUFFER_SIZE)) > 0) {
        // Allouer plus de mémoire pour contenir les données lues jusqu'à présent
        char *temp = malloc(totalBytesRead + bytesRead + 1); // +1 pour le caractère nul
        if (temp == NULL) {
            perror("malloc");
            free(input); // Libérer la mémoire déjà allouée en cas d'échec de malloc
            return NULL;
        }
        inputSize += bytesRead;
        input = temp;

        // Copier les données lues dans le tampon de résultat
        memcpy(input + totalBytesRead, buffer, bytesRead);
        totalBytesRead += bytesRead;
    }

    if (bytesRead == -1) {
        perror("read");
        free(input); // Libérer la mémoire allouée en cas d'échec de lecture
        return NULL;
    }

    // Terminer la chaîne de résultat avec un caractère nul
    if (input != NULL)
        input[totalBytesRead] = '\0';

    return input;
}

void	print_stdin(t_option *opt, uint8_t *hash, const char *input)
{
	printf("(");
	opt->flags & FLAGS_P ? printf("\"%s\"", input) : printf("%s", "stdin");
	printf(")= ");
	opt->cmd.cmd_print(hash);
	printf("\n");
}

void	print_string(t_option *opt, uint8_t *hash, const char *input)
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

void	print_file(t_option *opt, uint8_t *hash, const char *input)
{
	if (opt->flags & FLAGS_Q)
		opt->cmd.cmd_print(hash);
	else if (opt->flags & FLAGS_R)
	{
		opt->cmd.cmd_print(hash);
		printf(" %s\n", input);
	}
	else
	{
		printf("%s (", opt->cmd.cmd);
		printf("%s", input);
		printf(")= ");
		opt->cmd.cmd_print(hash);
		printf("\n");
	}
}

void	pross_file(t_option *opt, uint8_t *filename)
{
	int fd = open((const char *)filename, O_RDONLY);
	if (fd == -1)
	{
		printf("ft_ssl: %s: %s: %s\n", opt->cmd.cmd, filename, strerror(errno));
		return ;
	}

	

}