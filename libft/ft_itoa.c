/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lvogt <marvin@42lausanne.ch>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/14 09:33:19 by lvogt             #+#    #+#             */
/*   Updated: 2023/01/30 14:38:42 by lvogt            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	len(long nb)
{
	int	len;

	len = 0;
	if (nb == 0)
		len = 1;
	else if (nb < 0)
	{
		nb *= -1;
		len++;
	}
	while (nb > 0)
	{
		nb /= 10;
		len++;
	}
	return (len);
}

char	*ft_itoa(int nb)
{
	char	*str;
	long	n;
	int		i;

	n = nb;
	i = len(n);
	str = (char *) malloc (i + 1);
	if (!str)
		return (NULL);
	str[i--] = '\0';
	if (n == 0)
		str[0] = '0';
	if (n < 0)
	{
		str[0] = '-';
		n *= -1;
	}
	while (n > 0)
	{
		str[i--] = '0' + (n % 10);
		n /= 10;
	}
	return (str);
}

char	*ft_ltoa(long n)
{
	int		i;
	int		numlen;
	u_long	num;
	char	*n_str;

	numlen = ft_get_numlen(n);
	n_str = malloc((numlen + 1) * sizeof(char));
	if (n_str == NULL)
		return (NULL);
	i = 0;
	if (n < 0)
		n_str[i++] = '-';
	num = ft_abs(n);
	while (i < numlen)
	{
		n_str[i] = (num / ft_iterative_power(10, numlen - i - 1)) % 10 + '0';
		i++;
	}
	n_str[i] = '\0';
	return (n_str);
}
