/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions_finish.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaugu <aaugu@student.42lausanne.ch>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/05 13:59:19 by aaugu             #+#    #+#             */
/*   Updated: 2023/05/22 14:05:07 by aaugu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/state_machine.h"

void	get_next_type(t_fsm *fsm, char c);

/* Finish buffer, create a node of tokens list and set its content. Then reset 
the buffer. Get next type if needed.*/
void	finish_buf(t_fsm *fsm, t_token **tokens, char c)
{
	t_token	*new_token;
	t_token	*prev;

	if (fsm->buf_size != 0)
	{
		fsm->buf[fsm->buf_size] = '\0';
		new_token = create_node(fsm->buf, fsm->type, fsm);
		if (!new_token)
			parsing_error(fsm, 0);
		if (*tokens == NULL)
			*tokens = new_token;
		else
		{
			prev = lst_last(*tokens);
			prev->next = new_token;
			new_token->prev = prev;
		}
		if (fsm->meta == false)
			new_token->meta = false;
		init_state_machine(fsm);
		get_next_type(fsm, c);
	}
}

/* Combination of finish_buf() and add_to_buff() */
void	finish_add(t_fsm *fsm, t_token **tokens, char c)
{
	finish_buf(fsm, tokens, c);
	add_to_buf(fsm, c);
}

/* Combination of finish_buff() and set current state to stop */
void	finish_stop(t_fsm *fsm, t_token **tokens, char c)
{
	finish_buf(fsm, tokens, c);
	fsm->current_state = stop;
}

/* Combination of finish_add() and set current state to idle */
void	finish_add_idle(t_fsm *fsm, t_token **tokens, char c)
{
	finish_add(fsm, tokens, c);
	fsm->current_state = idle;
}

/* Define type of element depending on previous type saved */
void	get_next_type(t_fsm *fsm, char c)
{
	if (fsm->type == redir_in || fsm->type == heredoc || fsm->type == redir_out \
		|| fsm->type == redir_out_ap)
	{
		if (fsm->type == redir_in && c == '>')
			fsm->type = redir_out;
		else if (fsm->type == redir_in)
			fsm->type = infile;
		else if (fsm->type == heredoc)
			fsm->type = limiter;
		else if (fsm->type == redir_out)
			fsm->type = outfile;
		else if (fsm->type == redir_out_ap)
			fsm->type = outfile;
	}
	else if (fsm->type == cmd || fsm->type == option)
		fsm->type = option;
	else
		fsm->type = cmd;
}
