/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaugu <aaugu@student.42lausanne.ch>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/03 11:27:29 by lvogt             #+#    #+#             */
/*   Updated: 2023/06/19 15:09:32 by aaugu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* ft_launcher:
 *	Retire le "." du début de la commande.
 *	Join avec le chemin du répertoire de travail courant.
 *	Return : la chaine de caractère qui permet l'access de la commande.
 */
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

/* ft_join:
 *	Ajoute un à la fin de chaque path.
 */
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

/* ft_find_path:
 *	Recherche la path dans l'environement et l'adapte
 *	pour la rendre utilisable par le programme.
 */
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
