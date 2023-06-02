/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   meta_interpret.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaugu <aaugu@student.42lausanne.ch>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/31 10:32:25 by aaugu             #+#    #+#             */
/*   Updated: 2023/06/02 15:41:36 by aaugu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/parsing_input.h"
#include "../../includes/parsing_meta.h"
#include "../../includes/print_error.h"
#include "../../includes/minishell.h"

void	meta_interpret(t_token *t, char **env, int env_size)
{
	char	*buf;

	while (t)
	{
		if (ft_strchr(t->content, '$') && t->meta == true && t->type != limiter)
		{
			buf = parsing_meta(t->content, env, env_size);
			if (!buf)
			{
				print_err("minishell: malloc() failed:", errno);
				return ;
			}
			if (!ft_strlen(buf) && (t->type == infile || t->type == outfile))
			{
				printf("minishell: %s: ambiguous redirect\n", t->content);
				g_exit_code = 1;
			}
			free(t->content);
			t->content = buf;
		}
		t = t->next;
	}
}
