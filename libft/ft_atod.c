/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atod.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lvogt <marvin@42lausanne.ch>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/30 14:18:00 by lvogt             #+#    #+#             */
/*   Updated: 2023/01/30 14:46:01 by lvogt            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

long	ft_atol(const char *nptr)
{
	long	result;
	int		offset;
	int		sign;

	result = 0;
	offset = 0;
	sign = 1;
	while (nptr[offset] == ' ' || (nptr[offset] >= 9 && nptr[offset] <= 13))
		offset++;
	if (nptr[offset] == '-')
	{
		sign *= -1;
		offset++;
	}
	else if (nptr[offset] == '+')
		offset++;
	while (ft_isdigit(nptr[offset]))
	{
		result *= 10;
		result += nptr[offset] - '0';
		offset++;
	}
	return (result * sign);
}

static double	process_decimal(const char *nptr)
{
	size_t	count;
	double	decimal;

	decimal = ft_atol(nptr);
	count = 0;
	while (ft_isdigit(nptr[count]))
		count++;
	return (decimal / ft_iterative_power(10, count));
}

double	ft_atod(const char *nptr)
{
	int8_t	sign;
	size_t	offset;
	double	result;

	sign = 1;
	offset = 0;
	while (nptr[offset] == ' ' || (nptr[offset] >= 9 && nptr[offset] <= 13))
		offset++;
	if (nptr[offset] == '-')
	{
		sign *= -1;
		offset++;
	}
	else if (nptr[offset] == '+')
		offset++;
	result = ft_atol(&nptr[offset]);
	offset += ft_get_unumlen(result);
	if (nptr[offset] == '.' || nptr[offset] == ',')
		result += process_decimal(&nptr[offset + 1]);
	return (sign * result);
}
