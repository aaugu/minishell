/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   end_state_machine.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaugu <aaugu@student.42lausanne.ch>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/08 09:55:57 by aaugu             #+#    #+#             */
/*   Updated: 2023/05/15 15:34:47 by aaugu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/parsing.h"
#include "../../includes/minishell.h"

void	clear_parsing(t_sm *sm, t_token **tokens);
void	clear_state_machine(t_sm *sm);
void	clear_tokens(t_token **tokens);

void	parsing_error(t_sm *sm, t_token **tokens, char *s)
{
	if (s)
	{
		if (!ft_strncmp(s, "newline", 7))
			printf("minishell: syntax error near unexpected token `%s'\n", s);
		else
			printf("minishell: syntax error near unexpected token `%c'\n", s[0]);
		g_exit_code = 258;
	}
	else
	{
		printf("minishell: malloc() failed: %s\n", strerror(errno));
		g_exit_code = errno;
	}
	clear_parsing(sm, tokens);
	sm->current_state = error;
}

void	clear_parsing(t_sm *sm, t_token **tokens)
{
	clear_state_machine(sm);
	clear_tokens(tokens);
}

void	clear_state_machine(t_sm *sm)
{
	if (sm->buf)
		free(sm->buf);
	sm = (t_sm *){0};
}

void	clear_tokens(t_token **tokens)
{
	t_token	*next;

	if (!*tokens)
		return ;
	while (*tokens != NULL)
	{
		next = (*tokens)->next;
		if ((*tokens)->content)
			free((*tokens)->content);
		free(*tokens);
		*tokens = next;
	}
	free(tokens);
}
