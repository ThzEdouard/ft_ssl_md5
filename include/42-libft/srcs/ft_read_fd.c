/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_read_fd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eflaquet <eflaquet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/26 14:30:42 by eflaquet          #+#    #+#             */
/*   Updated: 2024/03/26 14:46:54 by eflaquet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/libft.h"
#define BUFFER_SIZE 4096

char *ft_read_fd(int fd) {
	char *input = NULL;
	char buffer[BUFFER_SIZE];
	ssize_t bytesRead;
	size_t totalBytesRead = 0;

	while ((bytesRead = read(fd, buffer, BUFFER_SIZE)) > 0) {
		char *temp = malloc(totalBytesRead + bytesRead + 1);
		if (temp == NULL) {
			ft_free(input);
			return NULL;
		}
		if (input != NULL) {
			ft_memcpy(temp, input, totalBytesRead);
			ft_free(input);
		}
		input = temp;
		ft_memcpy(input + totalBytesRead, buffer, bytesRead);
		totalBytesRead += bytesRead;
	}

	if (bytesRead == -1) {
		ft_free(input);
		return NULL;
	}
	if (input != NULL)
		input[totalBytesRead] = '\0';
	return input;
}