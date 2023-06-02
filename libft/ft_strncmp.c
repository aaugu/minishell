/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaugu <aaugu@student.42lausanne.ch>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/14 09:23:08 by lvogt             #+#    #+#             */
/*   Updated: 2023/05/31 15:50:28 by aaugu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t		idx;

	if (n == 0)
		return (0);
	idx = 0;
	while (idx < n)
	{
		if (s1[idx] && s1[idx] == s2[idx])
		{
			while (s1[idx] && s1[idx] == s2[idx] && idx < n)
				idx++;
		}
		else
			return ((unsigned char)s1[idx] - (unsigned char)s2[idx]);
	}
	return (0);
}

int	ft_strcmp_caps(const char *s1, const char *s2, size_t n)
{
	char	*s1_upper;
	char	*s2_upper;
	int		result;
	size_t	i;

	i = -1;
	s1_upper = ft_strdup(s1);
	s2_upper = ft_strdup(s2);
	if (s1_upper == NULL || s2_upper == NULL)
		return (-1);
	while (++i < n && s1_upper[i] && s2_upper[i])
	{
		s1_upper[i] = ft_toupper(s1_upper[i]);
		s2_upper[i] = ft_toupper(s2_upper[i]);
	}
	result = ft_strncmp(s1_upper, s2_upper, n);
	free(s1_upper);
	free(s2_upper);
	return (result);
}
