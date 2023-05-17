/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_unset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaugu <aaugu@student.42lausanne.ch>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/17 11:02:17 by aaugu             #+#    #+#             */
/*   Updated: 2023/05/17 14:39:35 by aaugu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdbool.h>
#include "../../libft/libft.h"
#include "../../includes/minishell.h"

int		env_variable_present(char **env, int env_size, char *variable);
void	remove_env_variable(char ***env, int env_size, char *variable);

void	cmd_env(char **env, int env_size, char **cmd_args);

void	cmd_unset(char **env, int env_size, char **cmd_args)
{
	int	i;
	int	exit_code;

	exit_code = 0;
	if (ft_strs_len(cmd_args) <= 1)
	{
		printf("unset: not enough arguments\n");
		exit_code++;
	}
	else
	{
		i = 1;
		while (i++ < ft_strs_len(cmd_args))
		{
			if (env_variable_present(env, env_size, cmd_args[i]) == true)
				remove_env_variable(&env, env_size, cmd_args[i]);
			else
			{
				printf("unset: %s:Environment variable is not set\n", cmd_args[i]);
				exit_code++;
			}
		}
	}
	g_exit_code = exit_code;
}

int	env_variable_present(char **env, int env_size, char *variable)
{
	int	i;

	i = 0;
	while (i++ < env_size)
	{
		if (ft_strnstr(env[i], variable, ft_strlen(variable)))
			return (true);
	}
	return (false);
}

void	remove_env_variable(char ***env, int env_size, char *variable)
{
	int	i;

	i = 0;
	while (i++ < env_size)
	{
		if (ft_strnstr((*env)[i], variable, ft_strlen(variable)))
		{
			free((*env)[i]);
			(*env)[i] = NULL;
		}
	}
}

#include <stdio.h>

int	main(int ac, char **av, char **envp)
{
	char	**cmd_args;
	char	**env;
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

	env = ft_strs_copy((const char **)envp, ft_strs_len(envp));
	cmd_unset(envp, ft_strs_len(env), cmd_args);

	char *cmd[2];
	cmd[0] = ft_strdup("env");
	cmd[1] = NULL;
	
	cmd_env(env, ft_strs_len(env), cmd);
	printf("\ng_exit_code : %d\n", g_exit_code);
	return (0);
}
