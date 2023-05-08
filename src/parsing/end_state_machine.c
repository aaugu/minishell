/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   end_state_machine.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaugu <aaugu@student.42lausanne.ch>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/08 09:55:57 by aaugu             #+#    #+#             */
/*   Updated: 2023/05/08 14:45:57 by aaugu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/state_machine.h"

void	parsing_error(t_state_machine *sm, t_token *tokens, char c)
{
	printf("minishell: syntax error near unexpected token `%c'", c);
	sm->current_state = error;
}

void	clear_state_machine(t_state_machine *sm)
{
	if (sm->buf)
		free(sm->buf);
}

void	clear_tokens(t_token **tokens)
{
	t_token	*next;

	if (!tokens)
		return ;
	while (*tokens != NULL)
	{
		next = (*tokens)->next;
		if ((*tokens)->content)
			free((*tokens)->content);
		free(*tokens);
		*tokens = next;
	}
}
