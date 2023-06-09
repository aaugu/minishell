/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   state_chars_heredoc.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaugu <aaugu@student.42lausanne.ch>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/02 15:30:35 by aaugu             #+#    #+#             */
/*   Updated: 2023/06/08 13:18:00 by aaugu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"
#include "../../../includes/parsing_meta_heredoc_state_machine.h"
#include "../../../libft/libft.h"

/* Will set current state according to char and decide which action to perform
if needed */
void	state_chars_heredoc(t_m_fsm *fsm, t_meta **meta_strs, char c)
{
	if (c == '$' || c == ' ' || c == '\0' || c == '\'' || c == '\"' || c == '/' \
		|| c == '-')
	{
		fsm->buf[fsm->buf_size] = '\0';
		get_var_content(fsm);
		if (fsm->current_state == error)
			return ;
		finish_buf_meta(fsm, meta_strs);
	}
	if (c == '$')
	{
		add_to_buf_meta(fsm, c);
		fsm->current_state = dollar;
	}
	else if (c == ' ' || c == '\'' || c == '\"' || c == '/' || c == '-')
	{
		add_to_buf_meta(fsm, c);
		fsm->current_state = idle;
	}
	else if (c == '\0')
		fsm->current_state = stop;
	else
		add_to_buf_meta(fsm, c);
}
