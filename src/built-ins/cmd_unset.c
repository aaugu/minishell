/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_unset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaugu <aaugu@student.42lausanne.ch>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/17 11:02:17 by aaugu             #+#    #+#             */
/*   Updated: 2023/06/02 15:09:46 by aaugu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <errno.h>
#include <stdbool.h>
#include <string.h>
#include <stdio.h>
#include "../../includes/print_error.h"
#include "../../includes/minishell.h"
#include "../../includes/built_ins.h"
#include "../../libft/libft.h"

void	remove_var_env(t_data *d);
int		is_var_present(char ***env, int env_size, char *variable);
char	**get_new_env(t_data *data, int new_size);

/*
Unset in bash : Each variable or function specified by name shall be unset.

If neither -f nor -v is specified, name refers to a variable.
Unsetting a variable or function that was not previously set shall not be
considered an error and does not cause the shell to abort.
 */
void	cmd_unset(t_data *data)
{
	if (ft_strs_len(data->cmd) <= 1)
		g_exit_code = print_err("unset: not enough arguments\n", 0);
	else
		remove_var_env(data);
}

void	remove_var_env(t_data *d)
{
	int		i;
	int		res;
	int		count;
	char	**new_env;

	i = 0;
	count = 0;
	while (++i < ft_strs_len(d->cmd))
	{
		res = is_var_present(&d->envp, d->env_size, (d->cmd)[i]);
		if (res > 0)
			count ++;
		else if (res == -1)
			clear_minishell(d);
	}
	if (count > 0)
	{
		new_env = get_new_env(d, d->env_size - count);
		ft_strs_free(d->envp, d->env_size);
		d->envp = new_env;
		d->env_size -= count;
	}
}

int	is_var_present(char ***env, int env_size, char *variable)
{
	int		i;
	char	*var;

	var = ft_strjoin(variable, "=");
	if (!var)
	{
		g_exit_code = print_err("minishell: malloc() failed:", errno);
		return (-1);
	}
	i = 0;
	while (i < env_size)
	{
		if (ft_strnstr((*env)[i], var, ft_strlen(var)))
		{
			free((*env)[i]);
			(*env)[i] = NULL;
			free(var);
			return (true);
		}
		i++;
	}
	free(var);
	return (false);
}

char	**get_new_env(t_data *data, int new_size)
{
	char	**new_env;
	int		i;
	int		j;

	new_env = (char **)malloc(sizeof(char *) * (new_size + 1));
	if (!new_env)
		clear_minishell(data);
	new_env[new_size] = NULL;
	i = 0;
	j = 0;
	while (i < data->env_size)
	{
		if (data->envp[i])
		{
			new_env[j] = ft_strdup(data->envp[i]);
			if (!new_env[j++])
			{
				ft_strs_free(new_env, new_size);
				clear_minishell(data);
				return (NULL);
			}
		}
		i++;
	}
	return (new_env);
}

/*
int	main(int ac, char **av, char **envp)
{
	t_data	data;
	int		i = 0;
	data = (t_data){0};
	data.cmd = (char **)malloc(sizeof(char *) * (ac));
	if (!data.cmd)
	{
		printf("Malloc error\n");
		return (1);
	}
	data.cmd[ac - 1] = NULL;
	while (i < ac)
	{
		data.cmd[i] = av[i + 1];
		i++;
	}
	data.env_size = ft_strs_len(envp);
	data.envp = ft_strs_copy((const char **)envp, data.env_size);
	i = 0;
	while (i < data.env_size)
	{
		printf("%s\n", data.envp[i]);
		i++;
	}
	printf("%d\n\n", data.env_size);
	cmd_unset(&data);
	i = 0;
	while (i < data.env_size)
	{
		printf("%s\n", data.envp[i]);
		i++;
	}
	printf("%d\n", data.env_size);
	return (0);
}
*/