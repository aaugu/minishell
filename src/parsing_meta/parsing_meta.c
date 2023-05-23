/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_meta.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaugu <aaugu@student.42lausanne.ch>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/23 14:02:29 by aaugu             #+#    #+#             */
/*   Updated: 2023/05/23 15:31:01 by aaugu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "../../includes/minishell.h"
#include "../../includes/parsing_meta.h"
#include "../../includes/print_error.h"
#include "../../libft/libft.h"

char	*meta_interpret(char *s)
{
	char	*interpreted_str;
	char	*tmp;
	t_meta	*meta_strs;

	meta_strs = meta_state_machine(*s);
	interpreted_str = ft_strdup("");
	if (!interpreted_str)
	{
		g_exit_code = print_err("minishell: malloc() failed: %s\n", errno);
		return (NULL);
	}
	while (meta_strs != NULL && meta_strs->next != NULL)
	{
		tmp = ft_strjoin(interpreted_str, meta_strs->content);
		free(interpreted_str);
		interpreted_str = tmp;
		meta_strs = meta_strs->next;
	}
	return (interpreted_str);
}