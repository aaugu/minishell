/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strs_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaugu <aaugu@student.42lausanne.ch>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/02 10:55:09 by aaugu             #+#    #+#             */
/*   Updated: 2023/05/31 11:18:04 by aaugu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strs_len(char **strs)
{
	int	i;

	i = 0;
	while (strs[i])
		i++;
	return (i);
}

void	ft_strs_free(char **strs, int size)
{
	int	i;

	i = 0;
	while (i < size && strs[i])
	{
		if (strs[i])
			free(strs[i]);
		i++;
	}
	free(strs);
	strs = NULL;
}

char	**ft_strs_copy(const char **src, int size)
{
	int		i;
	char	**dest;

	i = 0;
	dest = (char **)malloc(sizeof(char *) * (size + 1));
	if (!dest)
		return (NULL);
	dest[size] = NULL;
	while (i < size)
	{
		dest[i] = ft_strdup(src[i]);
		if (!dest[i++])
		{
			ft_strs_free(dest, size);
			return (NULL);
		}
	}
	return (dest);
}
