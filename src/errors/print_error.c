/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_error.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaugu <aaugu@student.42lausanne.ch>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/23 15:23:09 by aaugu             #+#    #+#             */
/*   Updated: 2023/05/23 15:23:16 by aaugu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "print_error.h"

int	print_err(char *message, int errnum)
{
	if (errnum != 0)
	{
		printf(message, strerror(errnum));
		return (errnum);
	}
	else
	{
		printf("%s", message);
		return (1);
	}
}
