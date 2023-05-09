/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaugu <aaugu@student.42lausanne.ch>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/05 13:59:19 by aaugu             #+#    #+#             */
/*   Updated: 2023/05/09 15:22:26 by aaugu            ###   ########.fr       */
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
		printf("%p\n", new_token);
		if (!new_token)
			parsing_error(sm, tokens, 0);
		if (tokens == NULL)
		{
			*tokens = new_token;
			printf("ici\n");
		}
		else
		{
			prev = lst_last(*tokens);
			prev->next = new_token;
		}
		if (sm->quotes_d == true)
		{
			if (ft_strchr(sm->buf, '$'))
				new_token->meta = true;
		}
		init_state_machine(sm, tokens);
	}
}

/* Add char to current buffer */
void	add_to_buf(char c, t_state_machine *sm)
{
	sm->buf[sm->buf_size] = c;
	sm->buf_size++;
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
