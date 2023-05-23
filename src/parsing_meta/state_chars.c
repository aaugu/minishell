/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   state_chars.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaugu <aaugu@student.42lausanne.ch>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/23 16:37:55 by aaugu             #+#    #+#             */
/*   Updated: 2023/05/23 17:06:08 by aaugu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing_meta_state_machine.h"

void	state_dollar(t_m_fsm *fsm, t_meta **meta_chars, char c)
{
	if (c == '$')
	{
		find_var_content();
		finish_buf_meta();
		add_to_buf_meta();
		fsm->current_state = dollar;
	}
	else if (c == ' ')
	{
		find_var_content();
		finish_buf_meta();
		fsm->current_state = idle;
	}
	else if (c == '\0')
		fsm->current_state = stop;
	else
		add_to_buf_meta();
}
