/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaugu <aaugu@student.42lausanne.ch>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/14 09:26:33 by lvogt             #+#    #+#             */
/*   Updated: 2023/05/31 15:43:48 by aaugu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *str, const char *to_find, size_t len)
{
	size_t		position;

	if (*to_find == '\0')
		return ((char *)str);
	position = ft_strlen((char *)to_find);
	while (*str != '\0' && len-- >= position)
	{
		if (*str == *to_find && ft_memcmp(str, to_find, position) == 0)
			return ((char *)str);
		str++;
	}
	return (NULL);
}
