/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   state_idle_meta.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaugu <aaugu@student.42lausanne.ch>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/23 16:38:26 by aaugu             #+#    #+#             */
/*   Updated: 2023/05/26 14:21:22 by aaugu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/parsing_meta_state_machine.h"

void	state_idle_meta(t_m_fsm *fsm, t_meta **meta_strs, char c)
{
	(void) meta_strs;
	if (c == '$')
	{
		finish_buf_meta(fsm, meta_strs);
		add_to_buf_meta(fsm, c);
		fsm->current_state = dollar;
	}
	else if (c == '\0')
		fsm->current_state = stop;
	else
		add_to_buf_meta(fsm, c);
}
