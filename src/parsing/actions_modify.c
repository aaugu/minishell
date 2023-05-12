/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions_modify.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaugu <aaugu@student.42lausanne.ch>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/12 10:03:33 by aaugu             #+#    #+#             */
/*   Updated: 2023/05/12 15:32:31 by aaugu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/state_machine.h"

/* Add char to current buffer */
void	add_to_buf(char c, t_sm *sm)
{
	sm->buf[sm->buf_size] = c;
	sm->buf_size++;
}

/* Change state and add on-going type */
void	change_state_and_type(t_state state, t_type type, t_sm *sm)
{
	sm->current_state = state;
	sm->type = type;
}

/* Combination of change_state_and_type() and add_to_buf() */
void	state_type_add_buf(t_state state, t_type type, char *c, t_sm *sm)
{
	change_state_and_type(state, type, sm);
	add_to_buf(c, sm);
}

/* Define type of element depending on previous type saved */
void	get_next_type(t_sm *sm, char *c)
{
	if (sm->type == redir_in || sm->type == heredoc || sm->type == redir_out \
		|| sm->type == redir_out_ap)
	{
		if (sm->type == redir_in && c == '>')
			sm->type = redir_out;
		if (sm->type == redir_in)
			sm->type = infile;
		else if (sm->type == heredoc)
			sm->type = limiter;
		else if (sm->type == redir_out)
			sm->type = outfile;
		else if (sm->type == redir_out_ap)
			sm->type = outfile;
		else
			sm->type = cmd;
	}
}

/* Combination of get_type() and add_to_buf() */
void	set_type_add_buf(char *c, t_sm *sm)
{
	get_type(sm, c);
	add_to_buf(c, sm);
}
