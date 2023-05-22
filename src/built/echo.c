/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lvogt <marvin@42lausanne.ch>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/09 10:40:25 by lvogt             #+#    #+#             */
/*   Updated: 2023/05/09 10:50:17 by lvogt            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

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
