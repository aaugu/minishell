/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_unset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lvogt <marvin@42lausanne.ch>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/17 11:02:17 by aaugu             #+#    #+#             */
/*   Updated: 2023/06/20 09:30:33 by lvogt            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <errno.h>
#include <stdbool.h>
#include <string.h>
#include <stdio.h>
#include "print_error.h"
#include "minishell.h"
#include "built_ins.h"
#include "libft.h"

void	remove_var_env(t_data *d);
int		is_var_present(t_data *data, char *variable);
char	**get_new_env(t_data *data, int new_size);

/*
Unset in bash : Each variable or function specified by name shall be unset.

If neither -f nor -v is specified, name refers to a variable.
Unsetting a variable or function that was not previously set shall not be
considered an error and does not cause the shell to abort.
 */
int	cmd_unset(t_data *data)
{
	int	prob;
	int	i;

	i = 1;
	prob = 0;
	while (data->cmd[i])
	{
		if (ft_strs_len(data->cmd) <= 1)
			data->exit_code = 0;
		else if (data->cmd[i] && (ft_isalpha(data->cmd[i][0]) == 0
			&& data->cmd[i][0] != '_'))
		{
			write(2, "minishell: unset: `", 19);
			write(2, data->cmd[i], ft_strlen(data->cmd[i]));
			write(2, "': not a valid identifier\n", 26);
			prob = 1;
		}
		else
			remove_var_env(data);
		if (prob == 1)
			data->exit_code = 1;
	i++;
	}
	return (data->exit_code);
}

/* Will try to remove the env variables passed as arguments if found */
void	remove_var_env(t_data *data)
{
	int		i;
	int		res;
	int		count;
	char	**new_env;

	i = 0;
	count = 0;
	while (++i < ft_strs_len(data->cmd))
	{
		res = is_var_present(data, (data->cmd)[i]);
		if (res > 0)
			count ++;
		else if (res == -1)
			clear_minishell(data, EXIT_FAILURE);
	}
	if (count > 0)
	{
		new_env = get_new_env(data, data->env_size - count);
		ft_strs_free(data->envp, data->env_size);
		data->envp = new_env;
		data->env_size -= count;
	}
}

/* Check if env variable is present in environment and, if found, free it*/
int	is_var_present(t_data *data, char *variable)
{
	int		i;
	char	*var;

	var = ft_strjoin(variable, "=");
	if (!var)
	{
		data->exit_code = print_err("minishell: malloc() failed:", errno);
		return (-1);
	}
	i = 0;
	while (data->envp[i])
	{
		if (ft_strnstr(data->envp[i], var, ft_strlen(var))
			|| (ft_strncmp(data->envp[i], variable, ft_strlen(variable)) == 0
				&& ft_strlen(data->envp[i]) == ft_strlen(variable)))
		{
			free(data->envp[i]);
			data->envp[i] = NULL;
			free(var);
			return (true);
		}
		i++;
	}
	free(var);
	return (false);
}

/* Re create env with env variables left */
char	**get_new_env(t_data *data, int new_size)
{
	char	**new_env;
	int		i;
	int		j;

	new_env = (char **)malloc(sizeof(char *) * (new_size + 1));
	if (!new_env)
		clear_minishell(data, EXIT_FAILURE);
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
				clear_minishell(data, EXIT_FAILURE);
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
