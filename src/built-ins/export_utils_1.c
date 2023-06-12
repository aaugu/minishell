/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils_1.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lvogt <marvin@42lausanne.ch>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/07 12:46:35 by lvogt             #+#    #+#             */
/*   Updated: 2023/06/07 12:46:35 by lvogt            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/*len_equal:
 *	mesure la len jusqu'à un pottentiel =
 */
int	len_equal(char *str)
{
	int	i;

	i = 0;
	while (str[i] && str[i] != '=')
		i++;
	return (i);
}

/* ft_only_digit:
 *	Vérifie l'input jusqu'à un pottentiel =
 *	compte le nombre de digit
 *	si c'est la totalité de l'input revoie 1
 *	0 sinon
 */
int	ft_only_digit(char *str)
{
	int	i;
	int	forbiden;

	i = 0;
	forbiden = 0;
	while (str[i] && str[i] != '=')
	{
		if (ft_isdigit(str[i]) == 1)
			forbiden++;
		else if (str[i] != '_' && ft_isalpha(str[i]) != 1)
			forbiden++;
		i++;
	}
	if (forbiden == len_equal(str))
		return (1);
	return (0);
}

/* ft_other_than_alnum:
 *	Vérifie l'input jusqu'à un pottentiel =
 *	si autre chose qu'un cara alnum (ou _) est trouvé
 *	renvoie 1, sinon 0
 */
int	ft_other_than_alnum(char *str)
{
	int	i;

	i = 0;
	while (str[i] && str[i] != '=')
	{
		if (ft_isalnum(str[i]) == 0)
		{
			if (str[i] != '_')
				return (1);
		}
		i++;
	}
	if (str[i] && str[i] == '=')
		return (0);
	else if (!str[i])
		return (0);
	return (1);
}

/* ft_digit_equal:
 *	vérifie si l'input est valide
 */
int	ft_digit_equal(char *str)
{
	int	flag;

	flag = 0;
	flag += ft_only_digit(str);
	flag += ft_other_than_alnum(str);
	if (flag > 0)
		return (1);
	return (0);
}

/* ft_export_nbr:
 *	compte le nombre d'export en vérifiant si l'input est valide
 *	sinon écrit un message d'erreur.
 */
int	ft_export_nbr(t_data *data)
{
	int	i;
	int	export_nbr;

	i = 1;
	export_nbr = 0;
	while (data->cmd[i])
	{
		if (ft_digit_equal(data->cmd[i]) == 0)
			export_nbr++;
		else
		{
			write(2, "minishell: export: ", 19);
			write(2, data->cmd[i], ft_strlen(data->cmd[i]));
			write(2, ": not a valid identifier\n", 25);
		}
		i++;
	}
	return (export_nbr);
}
