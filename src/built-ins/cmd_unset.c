/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_unset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lvogt <marvin@42lausanne.ch>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/17 11:02:17 by aaugu             #+#    #+#             */
/*   Updated: 2023/05/31 13:39:27 by lvogt            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <errno.h>
#include <stdbool.h>
#include <string.h>
#include <stdio.h>
#include "../../includes/print_error.h"
#include "../../includes/minishell.h"
#include "../../libft/libft.h"

int		remove_env_variable(char ***env, int env_size, char *variable);
int		print_err(char *message, int errnum);

/*
Unset in bash : Each variable or function specified by name shall be unset.

If neither -f nor -v is specified, name refers to a variable.
Unsetting a variable or function that was not previously set shall not be 
considered an error and does not cause the shell to abort.
 */

void	cmd_unset(t_data *data)
{
	int		i;
	int		res;

	if (ft_strs_len(data->cmd) <= 1)
		g_exit_code = print_err("unset: not enough arguments\n", 0);
	else
	{
		i = 0;
		while (++i < ft_strs_len(data->cmd))
		{
			res = remove_env_variable(&data->envp, data->env_size, data->cmd[i]);
			if (res == -1)
			{
				g_exit_code = print_err("minishell: malloc() failed: %s\n", \
				errno);
				break ;
			}
		}
	}
}

int	remove_env_variable(char ***env, int env_size, char *variable)
{
	int		i;
	char	*var;

	i = 0;
	var = ft_strjoin(variable, "=");
	if (!var)
		return (-1);
	while (i < env_size)
	{
		printf("test [%d]\n", i);
		if (ft_strnstr((*env)[i], var, ft_strlen(var)))
		{
			free((*env)[i]);
			(*env)[i] = NULL;
		}
		i++;
	}
	free(var);
	return (0);
}

/*
void	cmd_env(char **env, int env_size, char **cmd_args);

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
	cmd_unset(env, ft_strs_len(env), cmd_args);

	char *cmd[2];
	cmd[0] = ft_strdup("env");
	cmd[1] = NULL;

	cmd_env(env, 34, cmd);
	printf("\ng_exit_code : %d\n", g_exit_code);
	return (0);
}
*/