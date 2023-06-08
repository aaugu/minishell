/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lvogt <marvin@42lausanne.ch>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/05 11:35:41 by lvogt             #+#    #+#             */
/*   Updated: 2023/06/06 15:33:54 by lvogt            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/* ft_close_fd:
 *	Ferme les fd correspondant au in/out pour chaque pipe.
 */
void	ft_close_fd(int *fd_array, int pipe_nbr)
{
	int	i;
	int	index;

	index = 0;
	i = 0;
	if (pipe_nbr > 0 && fd_array)
	{
		while (index < pipe_nbr)
		{
			if (fd_array[i] > 0)
				close(fd_array[i]);
			if (fd_array[i + 1] > 0)
				close(fd_array[i + 1]);
			i += 2;
			index++;
		}
	}
}
