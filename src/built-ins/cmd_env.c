/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_env.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaugu <aaugu@student.42lausanne.ch>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/17 11:02:10 by aaugu             #+#    #+#             */
/*   Updated: 2023/05/22 13:42:22 by aaugu            ###   ########.fr       */
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

void	cmd_env(char **env, int env_size, char **cmd_args)
{
	int	i;

	if (ft_strs_len(cmd_args) == 1)
	{
		i = 0;
		while (i++ < env_size)
		{
			if (env[i])
				printf("%s\n", env[i]);
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