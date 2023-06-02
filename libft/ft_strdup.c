/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaugu <aaugu@student.42lausanne.ch>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/14 09:28:20 by lvogt             #+#    #+#             */
/*   Updated: 2023/06/02 11:18:38 by aaugu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
The strdup() function allocates sufficient memory for a copy of the string src,
does the copy, and returns a pointer to it. The pointer may subsequently be used
as an argument to the function free(3). If insufficient memory is available,
NULL is returned and errno is set to ENOMEM. The strndup() function copies at
most n characters from the string src always NUL terminating the copied string.
*/

char	*ft_strdup(const char *src)
{
	int		i;
	char	*dest;

	i = 0;
	dest = malloc(sizeof(*src) * (ft_strlen(src) + 1));
	if (!dest)
		return (NULL);
	while (src[i])
	{
		dest[i] = src[i];
		i++;
	}
	dest[i] = '\0';
	return (dest);
}
