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

void	pross_stdin(cmdFunction cmd, char *cmd_name, bool flags)
{

	char *input = ft_getline(0);
	// (void)cmd;
	(void)cmd_name;

	char *hash = cmd(input);
	printf("(");
	flags ? printf("\"%s\n", input) : printf("%s", "stdin");
	printf(")= ");
	printf("%s\n", hash);

}

// void	pross_string(cmdFunction cmd, uint8_t *cmd_name, t_option *opt)
// {

// }

// void	pross_file(cmdFunction cmd, uint8_t *cmd_name, t_option *opt)
// {

// }
