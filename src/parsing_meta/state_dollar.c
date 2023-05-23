/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   state_dollar.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaugu <aaugu@student.42lausanne.ch>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/23 16:38:09 by aaugu             #+#    #+#             */
/*   Updated: 2023/05/23 17:03:30 by aaugu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing_meta_state_machine.h"
#include "../../libft/libft.h"
#include "../../includes/minishell.h"

void	state_dollar(t_m_fsm *fsm, t_meta **meta_chars, char c)
{
	if (c == '?')
	{
		free(fsm->buf);
		fsm->buf = ft_itoa(g_exit_code);
		finish_buf_meta();
		fsm->current_state = idle;
	}
	else if (c == '\0')
		fsm->current_state = stop;
	else
	{
		remove_dollar();
		add_to_buf_meta();
	}
}
