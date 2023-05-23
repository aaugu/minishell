/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   state_machine_meta.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaugu <aaugu@student.42lausanne.ch>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/23 14:44:53 by aaugu             #+#    #+#             */
/*   Updated: 2023/05/23 16:42:56 by aaugu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing_meta.h"
#include "parsing_meta_state_machine.h"
#include "../../libft/libft.h"

void	execute_state_machine_meta(t_m_fsm *fsm, t_meta **meta_chars, char *s);
void	clear_state_machine(t_m_fsm *fsm);

t_meta	*meta_state_machine(char *str)
{
	t_m_fsm	fsm;
	t_meta	*meta_chars;
	int		i;

	fsm.current_state = idle;
	init_meta_state_machine(&fsm, ft_strlen(str));
	meta_chars = NULL;
	i = 0;
	while (i++ <= ft_strlen(str))
		execute_state_machine_meta(&fsm, &meta_chars, str);
	clear_state_machine(&fsm);
	if (fsm.current_state == stop)
		return (meta_chars);
	return (NULL);
}

void	execute_meta_state_machine(t_m_fsm *fsm, t_meta **meta_chars, char *s)
{
	if (fsm->current_state == idle)
		state_idle_meta(fsm, meta_chars, s);
	else if (fsm->current_state == dollar)
		state_dollar(fsm, meta_chars, s);
	else if (fsm->current_state == chars)
		state_chars(fsm, meta_chars, s);
}

void	clear_state_machine(t_m_fsm *fsm)
{
	if (fsm->buf)
		free(fsm->buf);
	fsm = (t_m_fsm *){0};
}
