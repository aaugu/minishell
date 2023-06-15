/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   meta_interpret.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaugu <aaugu@student.42lausanne.ch>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/31 10:32:25 by aaugu             #+#    #+#             */
/*   Updated: 2023/06/15 15:35:40 by aaugu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/parsing_input.h"
#include "../../includes/parsing_meta.h"
#include "../../includes/print_error.h"
#include "../../includes/minishell.h"

/* If needed, will interpret meta chars in token list elements to change them
as env variables */
void	meta_interpret(t_data *d, t_token *t)
{
	char	*buf;

	while (t)
	{
		if (ft_strchr(t->content, '$') && t->meta == true && \
			t->type != limiter)
		{
			buf = parsing_meta(t->content, d->envp, d->env_size, d->exit_code);
			if (!buf)
			{
				d->exit_code = print_err("minishell: malloc() failed:", errno);
				clear_minishell(d, d->exit_code);
			}
			if (!ft_strlen(buf) && (t->type == infile || t->type == outfile))
			{
				printf("minishell: %s: ambiguous redirect\n", t->content);
				d->exit_code = 1;
			}
			free(t->content);
			t->content = buf;
		}
		t = t->next;
	}
}
