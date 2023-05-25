/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_meta.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaugu <aaugu@student.42lausanne.ch>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/23 14:02:29 by aaugu             #+#    #+#             */
/*   Updated: 2023/05/25 13:44:25 by aaugu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "../../includes/minishell.h"
#include "../../includes/parsing_meta.h"
#include "../../includes/print_error.h"
#include "../../libft/libft.h"

char	*meta_interpret(char *s, char **env, int env_size)
{
	char	*interpreted_str;
	char	*tmp;
	t_meta	*meta_strs;

	meta_strs = meta_state_machine(*s, env, env_size);
	interpreted_str = ft_strdup("");
	if (!interpreted_str)
		return (NULL);
	while (meta_strs != NULL && meta_strs->next != NULL)
	{
		tmp = ft_strjoin(interpreted_str, meta_strs->content);
		if (!tmp)
			return (NULL);
		free(interpreted_str);
		interpreted_str = tmp;
		meta_strs = meta_strs->next;
	}
	//clear meta_strs
	return (interpreted_str);
}

void	clear_meta_strs(t_meta **meta_strs)
{
	t_meta	*next;

	if (!*meta_strs)
		return ;
	while (*meta_strs != NULL)
	{
		next = (*meta_strs)->next;
		if ((*meta_strs)->content)
			free((*meta_strs)->content);
		free(*meta_strs);
		*meta_strs = next;
	}
}

/*
#include <stdio.h>

int	main(int ac, char **av)
{
	int	*interpreted_str;

	printf("%s\n", interpreted_str = meta_interpret(av[1]));
	return (0);
}
*/