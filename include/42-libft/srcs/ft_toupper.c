/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_toupper.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eflaquet <eflaquet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/05 21:18:03 by eflaquet          #+#    #+#             */
/*   Updated: 2024/03/26 11:42:24 by eflaquet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int	ft_toupper(int c)
{
	if (c >= 97 && c <= 122)
		c -= 32;
	return (c);
}

char	*ft_str_toupper(char *str)
{
	if (str)
		for (unsigned int i = 0; str[i] != 0; i++)
			str[i] = ft_toupper(str[i]);
	return (str);
}