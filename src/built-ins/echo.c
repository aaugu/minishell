/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lvogt <marvin@42lausanne.ch>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/09 10:40:25 by lvogt             #+#    #+#             */
/*   Updated: 2023/06/07 14:30:07 by lvogt            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/* ft_print_echo:
 *	print chaque element demandé suivi par un " " puis finit par un \n.
 */
static void	ft_print_echo(t_data *data)
{
	int	i;

	i = 1;
	while (data->cmd[i])
	{
		printf("%s", data->cmd[i++]);
		if (!data->cmd[i])
			printf("\n");
		else
			printf(" ");
		i++;
	}
}
/* ft_echo:
 *	print un \n si rien est demander.
 *	si un -n est demander print chaque element demandé suivi par un " ".
 *	sans /n à la fin sinon l'ajoutera.
 */
void	ft_echo(t_data *data)
{
	int	i;

	if (!data->cmd[1])
		printf("\n");
	else if (data->cmd[1] && ft_strncmp(data->cmd[1], "-n", 2) == 0
		&& ft_strlen(data->cmd[1]) == 2)
	{
		i = 2;
		if (data->cmd[i])
		{
			while (data->cmd[i])
			{
				printf("%s", data->cmd[i++]);
				if (data->cmd[i])
					printf(" ");
			}
		}
	}
	else
		ft_print_echo(data);
}
