/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_get_len.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lvogt <marvin@42lausanne.ch>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/30 14:22:46 by lvogt             #+#    #+#             */
/*   Updated: 2023/01/30 14:31:37 by lvogt            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_get_numlen(long n)
{
	int	numlen;

	numlen = 1;
	if (n < 0)
		numlen++;
	while (n / 10)
	{
		numlen++;
		n /= 10;
	}
	return (numlen);
}

int	ft_get_numlen_base(long n, u_int base)
{
	int	numlen;

	numlen = 1;
	if (n < 0)
		numlen++;
	while (n / base)
	{
		numlen++;
		n /= base;
	}
	return (numlen);
}

int	ft_get_unumlen(u_long nb)
{
	int	count;

	count = 1;
	while (nb >= 10)
	{
		nb /= 10;
		count++;
	}
	return (count);
}

int	ft_get_unumlen_base(u_long n, u_int base)
{
	int	numlen;

	numlen = 1;
	while (n / base)
	{
		numlen++;
		n /= base;
	}
	return (numlen);
}
