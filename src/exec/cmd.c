/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lvogt <marvin@42lausanne.ch>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/05 12:03:10 by lvogt             #+#    #+#             */
/*   Updated: 2023/05/22 13:17:41 by lvogt            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	*ft_getenv(char **envp, char *var)
{
	char	*find;
	int		i;

	i = 0;
	while (envp[i])
	{
		if (ft_strncmp(envp[i], var, ft_strlen(var)) == 0)
		{
			find = ft_strtrim(envp[i], var);
			return (find);
		}
		i++;
	}
	return (NULL);
}

char	*ft_launcher(t_data *data)
{
	char	*pwd;
	char	*tmp;
	char	*tmp2;

	pwd = ft_getenv(data->envp, "PWD=");
	if (pwd != NULL)
	{
		tmp2 = ft_strtrim(data->cmd[0], ".");
		tmp = ft_strjoin(pwd, tmp2);
		free(tmp2);
		free(pwd);
		if (access(tmp, X_OK | F_OK) == 0)
			return (tmp);
	}
	return (NULL);
}

char	*find_cmd_path(t_data *data)
{
	int		i;
	char	*tmp;

	i = 0;
	if (!data->cmd[0])
		return (NULL);
	if (ft_strncmp(data->cmd[0], "./", 2) == 0)
		return (ft_launcher(data));
	else if (ft_strncmp(data->cmd[0], "/", 1) == 0)
	{
		if (access(data->cmd[0], X_OK) == 0)
		{
			tmp = ft_strdup(data->cmd[0]);
			return (tmp);
		}
	}
	while (data->all_path[i])
	{
		tmp = ft_strjoin(data->all_path[i], data->cmd[0]);
		if (access(tmp, X_OK | F_OK) == 0)
			return (tmp);
		free(tmp);
		i++;
	}
	return (NULL);
}

void	ft_builtins_or_cmd(t_data *d, t_token *tmp, pid_t *pid)
{
	if (d->is_builtin > 0 && d->is_builtin < 5)
	{
		if (d->cmd_nbr == 1 || d->is_builtin == 2
			|| d->is_builtin == 1 || (d->is_builtin == 4 && d->cmd[1]))
			ft_which_builtins(d, tmp, pid);
	}
	else if (d->cmd && d->is_builtin < 0)
	{
		if (d->all_path || ft_strncmp(d->cmd[0], "/", 1) == 0)
			d->cmd_path = find_cmd_path(d);
	}
}

char	*ft_full_str(t_token *token)
{
	t_token	*tmp;
	char	*str;

	tmp = token;
	str = ft_strdup(tmp->content);
	while (tmp->next && tmp->next->type == option)
	{
		tmp = tmp->next;
		str = ft_strjoin(str, " ");
		str = ft_strjoin(str, tmp->content);
	}
	if (str)
			return (str);
	return (NULL);
}

char	**ft_find_cmd(t_token *token)
{
	t_token	*tmp;
	char	**cmd;
	char	*str;

	tmp = token;
	if (tmp && tmp->type == t_pipe)
		tmp = tmp->next;
	while (tmp && tmp->type != t_pipe && tmp->type != command)
		tmp = tmp->next;
	if (tmp && tmp->type == command)
	{
		str = ft_full_str(tmp);
		cmd = ft_split(str, ' ');
		free(str);
		if (cmd)
			return (cmd);
	}
	return (NULL);
}

int	ft_is_cmd(t_token *token)
{
	t_token	*tmp;

	tmp = token;
	if (tmp->type == t_pipe)
		tmp = tmp->next;
	while (tmp && tmp->type != t_pipe)
	{
		if (tmp->type == command)
			return (1);
		tmp = tmp->next;
	}
	return (0);
}
