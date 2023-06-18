/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   state_idle.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaugu <aaugu@student.42lausanne.ch>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/23 16:38:26 by aaugu             #+#    #+#             */
/*   Updated: 2023/06/19 01:36:26 by aaugu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/parsing_meta_state_machine.h"

/* Will set current state according to char and decide which action to perform
if needed */
void	state_idle_meta(t_m_fsm *fsm, t_meta **meta_strs, char c)
{
	if (c == '$')
	{
		finish_state_meta(fsm, meta_strs, dollar, c);
		add_to_buf_meta(fsm, c);
	}
	else if (c == '\0')
	{
		finish_state_meta(fsm, meta_strs, stop, c);
	}
	else
		add_to_buf_meta(fsm, c);
}
