/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_error.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lvogt <marvin@42lausanne.ch>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/23 15:23:09 by aaugu             #+#    #+#             */
/*   Updated: 2023/06/19 18:41:41 by lvogt            ###   ########.fr       */
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

void	exit_print_error(t_data *d, int errnum)
{
	d->exit_code = print_err("minishell: malloc() failed:", errnum);
	exit(errno);
}
