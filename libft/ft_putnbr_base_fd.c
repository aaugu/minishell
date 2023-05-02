/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_base_fd.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lvogt <marvin@42lausanne.ch>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/31 11:11:56 by lvogt             #+#    #+#             */
/*   Updated: 2023/01/31 11:12:15 by lvogt            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_check_base(char *base)
{
	int		i;
	int		j;

	if (ft_strlen(base) < 2)
		return (0);
	i = 0;
	while (base[i])
	{
		if (base[i] == '-' || base[i] == '+' || !ft_isprint(base[i]))
			return (0);
		j = i + 1;
		while (base[j])
		{
			if (base[i] == base[j])
				return (0);
			j++;
		}
		i++;
	}
	return (1);
}

static void	putunbr_base_fd(u_long num, char *base, int fd)
{
	u_int	i;

	i = 0;
	while (base[i])
		i++;
	if (num < i)
		ft_putchar_fd(base[num], fd);
	if (num >= i)
	{
		putunbr_base_fd(num / i, base, fd);
		putunbr_base_fd(num % i, base, fd);
	}
}

int	ft_putunbr_base_fd(u_long num, char *base, int fd)
{
	if (!ft_check_base(base))
		return (0);
	putunbr_base_fd(num, base, fd);
	return (ft_get_unumlen_base(num, ft_strlen(base)));
}
