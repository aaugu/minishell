/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lvogt <marvin@42lausanne.ch>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/03 11:27:29 by lvogt             #+#    #+#             */
/*   Updated: 2023/05/31 13:56:10 by lvogt            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	**ft_join(char **path)
{
	int		i;
	char	*tmp;

	i = 0;
	while (path[i])
	{
		tmp = ft_strjoin(path[i], "/");
		free(path[i]);
		path[i++] = tmp;
	}
	return (path);
}

char	**ft_find_path(t_data *data)
{
	char	*trim;
	char	**path;
	int		i;

	path = NULL;
	i = 0;
	while (data->envp[i])
	{
		if (ft_strncmp("PATH=", data->envp[i], 5) == 0)
		{
			trim = ft_strtrim(data->envp[i], "PATH=");
			path = ft_split(trim, ':');
			free(trim);
			path = ft_join(path);
			break ;
		}
		i++;
	}
	return (path);
}
