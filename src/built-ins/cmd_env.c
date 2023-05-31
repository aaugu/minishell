/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_env.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lvogt <marvin@42lausanne.ch>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/17 11:02:10 by aaugu             #+#    #+#             */
/*   Updated: 2023/05/31 11:00:56 by lvogt            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "../../includes/minishell.h"
#include "../../libft/libft.h"

/*
Env in bash : Displays the current environment or sets the environment for the
execution of a command.
If no flags or parameters are specified, the env command displays your current
environment, showing one Name=Value pair per line.
*/

void	cmd_env(t_data *data)
{
	int	i;

	if (ft_strs_len(data->cmd) == 1)
	{
		i = 0;
		while (i++ < data->env_size)
		{
			if (data->envp[i])
				printf("%s\n", data->envp[i]);
		}
	}
	else
	{
		printf("env: too many arguments");
		g_exit_code = 1;
	}
}

/*
int	main(int ac, char **av, char **envp)
{
	char	**cmd_args;
	int		i = 0;

	cmd_args = (char **)malloc(sizeof(char *) * (ac));
	if (!cmd_args)
	{
		printf("Malloc error\n");
		return (1);
	}
	cmd_args[ac] = NULL;
	while (i < ac)
	{
		cmd_args[i] = av[i + 1];
		i++;
	}
	cmd_env(envp, ft_strs_len(envp), cmd_args);
	printf("\ng_exit_code : %d\n", g_exit_code);
	return (0);
}
*/