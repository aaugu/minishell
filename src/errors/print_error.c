/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_error.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaugu <aaugu@student.42lausanne.ch>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/23 15:23:09 by aaugu             #+#    #+#             */
/*   Updated: 2023/06/19 15:09:32 by aaugu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <string.h>
#include "print_error.h"

/* Print error message and return exit code*/
int	print_err(char *message, int errnum)
{
	if (errnum != 0)
	{
		printf("%s ", message);
		printf("%s\n", strerror(errnum));
		return (errnum);
	}
	else
	{
		printf("%s", message);
		return (1);
	}
}
