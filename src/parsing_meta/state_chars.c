/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   state_chars.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaugu <aaugu@student.42lausanne.ch>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/23 16:37:55 by aaugu             #+#    #+#             */
/*   Updated: 2023/05/25 13:54:09 by aaugu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/parsing_meta_state_machine.h"

void	find_var_content(char **buf, char **envp, int env_size);

void	state_chars(t_m_fsm *fsm, t_meta **meta_strs, char c)
{
	if (c == '$')
	{
		find_var_content(&(fsm->buf), fsm->env, fsm->env_size);
		finish_buf_meta();
		add_to_buf_meta(fsm, c);
		fsm->current_state = dollar;
	}
	else if (c == ' ')
	{
		find_var_content(&(fsm->buf), fsm->env, fsm->env_size);
		finish_buf_meta();
		fsm->current_state = idle;
	}
	else if (c == '\0')
		fsm->current_state = stop;
	else
		add_to_buf_meta(fsm, c);
}

void	find_var_content(char **buf, char **envp, int env_size)
{
}
