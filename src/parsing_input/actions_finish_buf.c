/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions_finish_buf.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaugu <aaugu@student.42lausanne.ch>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/05 13:59:19 by aaugu             #+#    #+#             */
/*   Updated: 2023/05/23 15:44:49 by aaugu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <stdbool.h>
#include "../../includes/parsing_input_state_machine.h"
#include "../../includes/parsing_meta_state_machine.h"

char	*get_final_buffer(char *buf, int buf_size, t_type type, int meta);
void	get_next_type(t_fsm *fsm, char c);

/* Finish buffer, create a node of tokens list and set its content. Then reset 
the buffer. Get type of next node.*/
void	finish_buf(t_fsm *fsm, t_token **tokens, char c)
{
	t_token	*new_token;
	t_token	*prev;
	char	*buf;

	if (fsm->buf_size != 0)
	{
		buf = get_final_buffer(fsm->buf, fsm->buf_size, fsm->type, fsm->meta);
		if (!buf)
			parsing_error(fsm, 0);
		new_token = create_node(buf, fsm->type, fsm);
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
		init_state_machine(fsm);
		get_next_type(fsm, c);
	}
}

/* Modify buffer if meta characters should be interpreted */
char	*get_final_buffer(char *buf, int buf_size, t_type type, int meta)
{
	char	*buffer;

	buf[buf_size] = '\0';
	if (meta == true && type != limiter)
	{
		buffer = meta_interpret(buf);
		if (!buffer)
			return (NULL);
	}
	else
		buffer = buf;
	return (buffer);
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
	else if (fsm->type == command || fsm->type == option)
		fsm->type = option;
	else
		fsm->type = command;
}
