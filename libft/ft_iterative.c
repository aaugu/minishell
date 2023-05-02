/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_iterative.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lvogt <marvin@42lausanne.ch>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/30 14:24:14 by lvogt             #+#    #+#             */
/*   Updated: 2023/01/30 14:24:28 by lvogt            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_iterative_power(int nb, int power)
{
	int	result;

	if (power < 0)
		return (0);
	if (power == 0)
		return (1);
	result = nb;
	while (power > 1)
	{
		result *= nb;
		power--;
	}
	return (result);
}

int	ft_iterative_factorial(int nb)
{
	int	fact_nb;

	if (nb < 0 || nb > 12)
		return (0);
	fact_nb = 1;
	while (nb > 0)
	{
		fact_nb *= nb;
		nb--;
	}
	return (fact_nb);
}
