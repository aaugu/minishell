/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   end_state_machine.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaugu <aaugu@student.42lausanne.ch>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/08 09:55:57 by aaugu             #+#    #+#             */
/*   Updated: 2023/05/12 10:31:00 by aaugu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/parsing.h"

void	clear_parsing(t_state_machine *sm, t_token **tokens);
void	clear_state_machine(t_state_machine *sm);
void	clear_tokens(t_token **tokens);

void	parsing_error(t_state_machine *sm, t_token **tokens, char *s)
{
	if (s)
		printf("minishell: syntax error near unexpected token `%s'\n", s);
	else
		printf("minishell: malloc: malloc failed\n");
	clear_parsing(sm, tokens);
	sm->current_state = error;
}

void	clear_parsing(t_state_machine *sm, t_token **tokens)
{
	clear_state_machine(sm);
	clear_tokens(tokens);
}

void	clear_state_machine(t_state_machine *sm)
{
	if (sm->buf)
		free(sm->buf);
	sm = (t_state_machine *){0};
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
