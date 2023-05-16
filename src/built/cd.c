/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lvogt <marvin@42lausanne.ch>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/09 10:52:48 by lvogt             #+#    #+#             */
/*   Updated: 2023/05/09 12:46:13 by lvogt            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	ft_oldpwd(t_data *data, char *old_cd)
{
	int		i;
	char	**old_pwd;

	i = 0;
	while (data->envp[i])
			i++;
	old_pwd = (char **)malloc(sizeof(char *) * (i + 2));
	if (!old_pwd)
		return ;
	i = 0;
	while (data->envp[i])
	{
		old_pwd[i] = ft_strdup(data->envp[i]);
		i++;
	}
	old_pwd[i++] = ft_strjoin("OLDPWD=", old_cd);
	old_pwd[i] = NULL;
	ft_free_double(data->envp);
	data->envp = old_pwd;
}

void	ft_change_oldpwd(t_data *data, char *old_cd)
{
	int	i;

	i = 0;
	while (data->envp[i]
		&& ft_strncmp(data->envp[i], "OLDPWD=", 4) != 0)
		i++;
	if (!data->envp[i]
		|| ft_strncmp(data->envp[i], "OLDPWD=", 4 != 0))
		ft_oldpwd(data, old_cd);
	else
	{
		free(data->envp[i]);
		data->envp[i] = ft_strjoin("OLDPWD=", old_cd);
	}
}

void	ft_change_pwd(t_data *data, char *new_cd)
{
	int		i;

	i = 0;
	while (data->envp[i]
		&& ft_strncmp(data->envp[i], "PWD=", 4) != 0)
		i++;
	if (!data->envp[i]
		|| ft_strncmp(data->envp[i], "PWD=", 4 != 0))
		return ;
	free(data->envp[i]);
	data->envp[i] = ft_strjoin("PWD=", new_cd);
}

char	*ft_new_cd(t_data *data)
{
	char	*new_cd;

	if (!data->cmd[1])
	{
		new_cd = ft_getenv(data->envp, "HOME=");
		if (new_cd == NULL)
		{
			write(2, "cd: No home directory found\n", 28);
			return (NULL);
		}
	}
	else
		new_cd = data->cmd[1];
	return (new_cd);
}

int	ft_cd_dont_exec(t_data *data)
{
	int	fd;

	if (data->cmd[1])
	{
		fd = open(data->cmd[1], O_RDONLY);
		if (fd == -1)
		{
			write(2, "cd: ", 4);
			write (2, data->cmd[1], ft_strlen(data->cmd[1]));
			write (2, ": no such file or directory\n", 28);
			return (1);
		}   
		close(fd);
	}
	return (0);
}

int	ft_do_cd(char *n_cd, char *o_pwd, t_data *data)
{
	char	new_pwd[1024];

	if (chdir(n_cd) == -1)
	{
		write(2, "minishell: cd: ", 15);
		write(2, n_cd, ft_strlen(n_cd));
		write(2, ": no such file or directory\n", 28);
		if (!data->cmd[1] && n_cd)
			free(n_cd);
		return (1);
	}
	if (!data->cmd[1] && n_cd)
		free(n_cd);
	ft_change_oldpwd(data, o_pwd);
	if (getcwd(new_pwd, sizeof(new_pwd)) != NULL)
		ft_change_pwd(data, new_pwd);
	return (0);
}

int	ft_cd(t_data *data)
{
	char	*new_cd;
	char	old_pwd[1024];

	if (getcwd(old_pwd, sizeof(old_pwd)) == NULL)
		return (-1);
	new_cd = ft_new_cd(data);
	if (data->cmd_nbr > 1)
	{
		if (!data->cmd[1] && new_cd)
		{
			free(new_cd);
			new_cd = NULL;
		}
		if (ft_cd_dont_exec(data) == 0)
			return (0);
		return (1);
	}
	else if (new_cd && data->cmd_nbr < 2)
	{
		if (ft_do_cd(new_cd, old_pwd, data) == 0)
			return (0);
		return (1);
	}
	return (1);
}
