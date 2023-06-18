/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   state_dollar.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaugu <aaugu@student.42lausanne.ch>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/23 16:38:09 by aaugu             #+#    #+#             */
/*   Updated: 2023/06/19 00:22:00 by aaugu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <errno.h>
#include "parsing_meta_state_machine.h"
#include "minishell.h"
#include "print_error.h"
#include "libft.h"

/* Will set current state according to char and decide which action to perform
if needed */
void	state_dollar(t_m_fsm *fsm, t_meta **meta_strs, char c, int last_exit)
{
	if (c == '?')
	{
		free(fsm->buf);
		fsm->buf = ft_itoa(last_exit);
		if (!fsm->buf)
		{
			parsing_error_meta(&(fsm->current_state));
			return ;
		}
		finish_buf_meta(fsm, meta_strs);
		fsm->current_state = idle;
	}
	else if (c == '$' || c == '-' || ft_isdigit(c))
	{
		fsm->buf[0] = '\0';
		finish_buf_meta(fsm, meta_strs);
		fsm->current_state = idle;
	}
	else if (c == '\0')
	{
		finish_buf_meta(fsm, meta_strs);
		fsm->current_state = stop;
	}
	else if (ft_isalpha(c) || c == '_')
	{
		fsm->buf[0] = '\0';
		add_to_buf_meta(fsm, c);
		fsm->current_state = chars;
	}
	else
	{
		add_to_buf_meta(fsm, c);
		finish_buf_meta(fsm, meta_strs);
		fsm->current_state = idle;
	}
}
