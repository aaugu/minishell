/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaugu <aaugu@student.42lausanne.ch>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/05 13:59:19 by aaugu             #+#    #+#             */
/*   Updated: 2023/05/08 15:37:50 by aaugu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/state_machine.h"

/* Finish buffer, create a node of tokens list and set its content. Then reset
the buffer. */
void	finish_buf(t_state_machine *sm, t_token *tokens)
{
	t_token	*new_token;

	sm->buf[sm->buf_size] = '\0';
	new_token = create_node(sm->buf);
	if (sm->quotes_d = true)
	{
		if (ft_strchr(sm->buf, '$'))
			
	}
	sm->quotes_d = false;
	free(sm->buf)
}

/* Add char to current buffer */
void	add_to_buf(char c, t_state_machine *sm, t_token *tokens)
{
}

/* Combination of finish_buf() and add_to_buff() */
void	finish_add(char c, t_state_machine *sm, t_token *tokens)
{
	finish_buf(sm, tokens);
	add_to_buf(c, sm, tokens);
}

/* Combination of finish_buff() and set current state to stop */
void	finish_stop(t_state_machine *sm, t_token *tokens)
{
	finish_buf(sm, tokens);
	sm->current_state = stop;
}

/* Combination of finish_add() and set current state to idle */
void	finish_add_to_idle(char c, t_state_machine *sm, t_token *tokens)
{
	finish_add(c, sm, tokens);
	sm->current_state = idle;
}
