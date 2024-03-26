/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_tolower.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eflaquet <eflaquet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/05 21:17:58 by eflaquet          #+#    #+#             */
/*   Updated: 2024/03/26 11:42:15 by eflaquet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int	ft_tolower(int c)
{
	if (c >= 65 && c <= 90)
		c += 32;
	return (c);
}

char	*ft_str_toupper(char *str)
{
	if (str)
		for (unsigned int i = 0; str[i] != 0; i++)
			str[i] = ft_tolower(str[i]);
	return (str);
}