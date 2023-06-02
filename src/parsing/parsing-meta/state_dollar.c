/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   state_dollar.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaugu <aaugu@student.42lausanne.ch>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/23 16:38:09 by aaugu             #+#    #+#             */
/*   Updated: 2023/06/02 15:34:42 by aaugu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <errno.h>
#include "../../../includes/parsing_meta_state_machine.h"
#include "../../../includes/minishell.h"
#include "../../../includes/print_error.h"
#include "../../../libft/libft.h"

void	state_dollar(t_m_fsm *fsm, t_meta **meta_strs, char c)
{
	if (c == '?' || c == '$')
		fsm->current_state = idle;
	if (c == '?')
	{
		free(fsm->buf);
		fsm->buf = ft_itoa(g_exit_code);
		if (!fsm->buf)
		{
			parsing_error_meta(&(fsm->current_state));
			return ;
		}
		finish_buf_meta(fsm, meta_strs);
	}
	else if (c == '$')
		init_meta_state_machine(fsm);
	else if (c == '\0')
	{
		finish_buf_meta(fsm, meta_strs);
		fsm->current_state = stop;
	}
	else
	{
		add_to_buf_meta(fsm, c);
		fsm->current_state = chars;
	}
}
