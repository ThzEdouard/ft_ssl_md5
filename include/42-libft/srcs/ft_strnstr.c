/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eflaquet <eflaquet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/04 18:50:36 by eflaquet          #+#    #+#             */
/*   Updated: 2024/03/26 11:37:59 by eflaquet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/libft.h"

char	*ft_strnstr(const char *haystack, const char *needle, size_t len)
{
	size_t	i;
	size_t	j;

	i = 0;
	if (!haystack || !needle || (ft_strlen(needle) > len))
		return (NULL);
	if (needle[i] == 0)
		return ((char *)haystack);
	while (haystack[i] && i <= (len - ft_strlen(needle)))
	{
		j = 0;
		while (haystack[i] && (haystack[i + j] == needle[j]))
		{
			j++;
			if (needle[j] == 0)
				return ((char *)(haystack + i));
		}
		i++;
	}
	return (NULL);
}
