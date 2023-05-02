/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrev.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lvogt <marvin@42lausanne.ch>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/03 10:34:19 by lvogt             #+#    #+#             */
/*   Updated: 2023/02/03 12:38:05 by lvogt            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrev(char *str)
{
	int		i;
	int		length;
	char	temporary;

	i = -1;
	length = 0;
	temporary = str[i];
	while (str[length])
		length++;
	while (++i < --length)
	{
		str[i] = str[length];
		str[length] = temporary;
	}
	return (str);
}
