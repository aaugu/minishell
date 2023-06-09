/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_env.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaugu <aaugu@student.42lausanne.ch>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/17 11:02:10 by aaugu             #+#    #+#             */
/*   Updated: 2023/06/19 15:09:42 by aaugu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "minishell.h"
#include "built_ins.h"
#include "libft.h"

/*
Env in bash : Displays the current environment or sets the environment for the
execution of a command.
If no flags or parameters are specified, the env command displays your current
environment, showing one Name=Value pair per line.
*/

int	cmd_env(char **env, int env_size, char **cmd_args)
{
	int	i;

	if (ft_strs_len(cmd_args) == 1)
	{
		i = 0;
		while (i < env_size)
		{
			if (env[i] && strchr(env[i], '='))
				printf("%s\n", env[i]);
			i++;
		}
		return (0);
	}
	else
	{
		printf("env: too many arguments\n");
		return (1);
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
