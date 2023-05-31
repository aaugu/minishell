/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   state_machine_meta_utils.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaugu <aaugu@student.42lausanne.ch>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/23 16:31:28 by aaugu             #+#    #+#             */
/*   Updated: 2023/05/26 13:23:17 by aaugu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "../../includes/parsing_meta_state_machine.h"
#include "../../libft/libft.h"

void	init_meta_state_machine(t_m_fsm *fsm)
{
	if (fsm->buf)
		free(fsm->buf);
	fsm->buf = (char *)ft_calloc(fsm->len, sizeof(char));
	if (!fsm->buf)
		parsing_error_meta(&(fsm->current_state));
	fsm->buf_size = 0;
}
