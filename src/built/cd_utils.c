/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lvogt <marvin@42lausanne.ch>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/07 12:57:36 by lvogt             #+#    #+#             */
/*   Updated: 2023/06/07 12:57:36 by lvogt            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/* ft_oldpwd:
 *	Modifie l'env pour ajouter une ligne OLDPWD
 */
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

/* ft_change_oldpwd:
 *	Cherche la ligne OLDPWD puis la midifie.
 *	Si la ligne n'existe pas l'ajoute à l'env.
 */
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
