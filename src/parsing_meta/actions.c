/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaugu <aaugu@student.42lausanne.ch>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/25 11:16:13 by aaugu             #+#    #+#             */
/*   Updated: 2023/05/25 11:40:23 by aaugu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/parsing_meta_state_machine.h"

/* Add char to current buffer */
void	add_to_buf_meta(t_m_fsm *fsm, char c)
{
	fsm->buf[fsm->buf_size] = c;
	fsm->buf_size++;
}
