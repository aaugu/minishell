/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaugu <aaugu@student.42lausanne.ch>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/09 11:22:33 by lvogt             #+#    #+#             */
/*   Updated: 2023/06/15 10:52:35 by aaugu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "../../includes/minishell.h"
#include "../../libft/libft.h"
#include "../../includes/print_error.h"

void	print_with_quotes(t_data *data, char *s)
{
	int		i;
	char	*str;

	i = 0;
	while (s[i] != '=')
		i++;
	str = ft_substr(s, 0, i + 1);
	if (!str)
		data->exit_code = print_err("minishell: malloc() failed:", errno);
	printf("%s", str);
	printf("\"");
	free(str);
	str = ft_strchr((const char *)s, '=') + 1;
	printf("%s", str);
	printf("\"\n");
}

/* sort_env_alph:
 *	échange les lignes en les comparants avec ft_strncmp.
 */
void	sort_env_alph(char **env_copy, int count)
{
	int		i;
	int		j;
	char	*temp;

	i = -1;
	while (++i < count - 1)
	{
		j = i + 1;
		while (j < count)
		{
			if (ft_strncmp(env_copy[i], env_copy[j], 255) > 0)
			{
				temp = env_copy[i];
				env_copy[i] = env_copy[j];
				env_copy[j] = temp;
			}
			j++;
		}
	}
}

/* ft_env_alph_order:
 *	Copie l'env puis trie dans l'ordre Alpha
 */
void	ft_env_alph_order(t_data *data)
{
	int		i;
	char	**copy;

	i = -1;
	copy = malloc((data->env_size + 1) * sizeof(char *));
	if (!copy)
	{
		data->exit_code = print_err("minishell: malloc() failed:", errno);
		exit(errno);
	}
	while (++i < data->env_size)
		copy[i] = data->envp[i];
	copy[data->env_size] = NULL;
	sort_env_alph(copy, data->env_size);
	i = -1;
	while (++i < data->env_size)
	{
		printf("declare -x ");
		if (ft_strchr(copy[i], '=') != copy[i])
			print_with_quotes(data, copy[i]);
		else
			printf("%s\n", copy[i]);
	}
	free(copy);
}

/* ft_export:
 *	si rien n'est demandé print l'env dans l'ordre alphabétique
 *	dans l'autre cas compte le nombre d'export demandé
 *	si nous ne sommes pas dans le cas de pipe
 *	ajoute la ligne 
 */
int	ft_export(t_data *data)
{
	int		export_nbr;
	int		line;
	char	**export;

	line = 0;
	if (!data->cmd[1])
		ft_env_alph_order(data);
	else if (data->cmd[1])
	{
		export_nbr = ft_export_nbr(data);
		if (data->cmd_nbr == 1)
		{
			while (data->envp[line])
				line++;
			export = ft_add(line, export_nbr, data);
			ft_free_double(data->envp);
			data->envp = export;
			data->env_size = ft_strs_len(data->envp);
		}
	}
	return (0);
}
