/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions_finish.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaugu <aaugu@student.42lausanne.ch>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/05 13:59:19 by aaugu             #+#    #+#             */
/*   Updated: 2023/05/16 13:15:56 by aaugu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/state_machine.h"

void	get_next_type(t_sm *sm, char c);

/* Finish buffer, create a node of tokens list and set its content. Then reset 
the buffer. Get next type if needed.*/
void	finish_buf(t_sm *sm, t_token **tokens, char c)
{
	t_token	*new_token;
	t_token	*prev;

	if (sm->buf_size != 0)
	{
		sm->buf[sm->buf_size] = '\0';
		new_token = create_node(sm->buf, sm->type, sm);
		if (!new_token)
			parsing_error(sm, 0);
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
		init_state_machine(sm);
		get_next_type(sm, c);
	}
}

/* Combination of finish_buf() and add_to_buff() */
void	finish_add(t_sm *sm, t_token **tokens, char c)
{
	finish_buf(sm, tokens, c);
	add_to_buf(sm, c);
}

/* Combination of finish_buff() and set current state to stop */
void	finish_stop(t_sm *sm, t_token **tokens, char c)
{
	finish_buf(sm, tokens, c);
	sm->current_state = stop;
}

/* Combination of finish_add() and set current state to idle */
void	finish_add_idle(t_sm *sm, t_token **tokens, char c)
{
	finish_add(sm, tokens, c);
	sm->current_state = idle;
}

/* Define type of element depending on previous type saved */
void	get_next_type(t_sm *sm, char c)
{
	if (sm->type == redir_in || sm->type == heredoc || sm->type == redir_out \
		|| sm->type == redir_out_ap)
	{
		if (sm->type == redir_in && c == '>')
			sm->type = redir_out;
		else if (sm->type == redir_in)
			sm->type = infile;
		else if (sm->type == heredoc)
			sm->type = limiter;
		else if (sm->type == redir_out)
			sm->type = outfile;
		else if (sm->type == redir_out_ap)
			sm->type = outfile;
	}
	else if (sm->type == cmd || sm->type == option)
		sm->type = option;
	else
		sm->type = cmd;
}
