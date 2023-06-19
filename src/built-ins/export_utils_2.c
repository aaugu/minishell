/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils_2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lvogt <marvin@42lausanne.ch>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/07 12:48:11 by lvogt             #+#    #+#             */
/*   Updated: 2023/06/07 12:48:11 by lvogt            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* copy_exist:
 *	fait une copie de l'env.
 */
char	**copy_exist(t_data *data, int line, int export_nbr, int *i)
{
	char	**export;

	export = (char **)ft_calloc((line + export_nbr + 1), sizeof(char *));
	if (!export)
		return (NULL);
	while (*i < line)
	{
		export[*i] = ft_strdup(data->envp[*i]);
		if (!export[*i])
			return (NULL);
		*i += 1;
	}
	return (export);
}

/* ft_dup_export:
 *	ajoute une ligne à l'export.
 *	incrément i
 */
char	*ft_dup_export(char **export, t_data *d, int *i, int j)
{
	export[*i] = ft_strdup(d->cmd[j]);
	if (!export[*i])
		return (NULL);
	*i += 1;
	return (export[*i]);
}

/* ft_does_it_exist:
 *	renvoie le numéro de la ligne si l'export demandé existe déjà.
 */
int	ft_does_it_exist(int i, int j, char **export, t_data *data)
{
	int	n;

	n = 0;
	while (n < i)
	{
		if (ft_strncmp(export[n], data->cmd[j], len_equal(data->cmd[j])) == 0)
		{
			if (ft_strchr(data->cmd[j], '=') == 0)
			{
				if (len_equal(export[n]) == len_equal(data->cmd[j]))
					return (n);
			}
			else if (len_equal(export[n])
				== len_equal(ft_strtrim(data->cmd[j], "=")))
				return (n);
		}
		n++;
	}
	return (-1);
}

/* ft_add:
 *	copie l'env, vérifi la pré-existance d'une ligne dedans.
 *	si l'input est valide, sois modifi la ligne ou la crée.
 */
char	**ft_add(int line, int export_nbr, t_data *data)
{
	char	**export;
	int		exist;
	int		i;
	int		j;

	j = 0;
	i = 0;
	export = copy_exist(data, line, export_nbr, &i);
	while (data->cmd[++j])
	{
		exist = ft_does_it_exist(i, j, export, data);
		if (ft_digit_equal(data->cmd[j]) == 0)
		{
			if (exist >= 0)
			{
				free(export[exist]);
				export[exist] = ft_strdup(data->cmd[j]);
			}
			else
				export[i] = ft_dup_export(export, data, &i, j);
		}
	}
	export[i] = NULL;
	return (export);
}
