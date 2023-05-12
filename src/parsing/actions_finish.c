/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions_finish.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaugu <aaugu@student.42lausanne.ch>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/05 13:59:19 by aaugu             #+#    #+#             */
/*   Updated: 2023/05/12 11:02:14 by aaugu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/state_machine.h"

/* Finish buffer, create a node of tokens list and set its content. Then reset
the buffer. */
void	finish_buf(t_state_machine *sm, t_token **tokens)
{
	t_token	*new_token;
	t_token	*prev;

	if (sm->buf_size != 0)
	{
		sm->buf[sm->buf_size] = '\0';
		new_token = create_node(sm->buf, sm, tokens);
		if (!new_token)
			parsing_error(sm, tokens, 0);
		if (*tokens == NULL)
			*tokens = new_token;
		else
		{
			prev = lst_last(*tokens);
			prev->next = new_token;
			new_token->prev = prev;
		}
		if (sm->meta == false)
			new_token->meta = false;
		init_state_machine(sm, tokens);
	}
}

/* Combination of finish_buf() and add_to_buff() */
void	finish_add(char c, t_state_machine *sm, t_token **tokens)
{
	finish_buf(sm, tokens);
	add_to_buf(c, sm);
}

/* Combination of finish_buff() and set current state to stop */
void	finish_stop(t_state_machine *sm, t_token **tokens)
{
	finish_buf(sm, tokens);
	sm->current_state = stop;
}

/* Combination of finish_add() and set current state to idle */
void	finish_add_idle(char c, t_state_machine *sm, t_token **tokens)
{
	finish_add(c, sm, tokens);
	sm->current_state = idle;
}
