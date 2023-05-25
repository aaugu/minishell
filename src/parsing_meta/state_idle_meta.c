/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   state_idle_meta.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaugu <aaugu@student.42lausanne.ch>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/23 16:38:26 by aaugu             #+#    #+#             */
/*   Updated: 2023/05/25 13:32:18 by aaugu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/parsing_meta_state_machine.h"

void	state_idle_meta(t_m_fsm *fsm, t_meta **meta_strs, char c)
{
	if (c == '$')
	{
		finish_buf_meta();
		add_to_buf_meta(fsm, c);
	}
	else if (c == '\0')
		fsm->current_state = stop;
	else
		add_to_buf_meta(fsm, c);
}
