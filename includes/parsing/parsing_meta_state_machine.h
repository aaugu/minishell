/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_meta_state_machine.h                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaugu <aaugu@student.42lausanne.ch>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/17 22:38:41 by aaugu             #+#    #+#             */
/*   Updated: 2023/06/17 22:54:21 by aaugu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSING_META_STATE_MACHINE_H
# define PARSING_META_STATE_MACHINE_H

/******************************************************************************
*							    INCLUDE										  *
******************************************************************************/

# include "parsing_states.h"
# include "parsing_meta_heredoc.h"

/******************************************************************************
*							    FUNCTIONS									  *
******************************************************************************/

t_meta	*meta_state_machine(char *str, char **env, int env_size, int last_exit);
void	init_meta_state_machine(t_m_fsm *fsm);

/* ---------------------------------- STATES ---------------------------------*/
void	state_idle_meta(t_m_fsm *fsm, t_meta **meta_strs, char c);
void	state_dollar(t_m_fsm *fsm, t_meta **meta_strs, char c, int last_exit);
void	state_chars(t_m_fsm *fsm, t_meta **meta_strs, char c);

/* --------------------------------- ACTIONS ---------------------------------*/
void	add_to_buf_meta(t_m_fsm *fsm, char c);
void	finish_buf_meta(t_m_fsm *fsm, t_meta **meta_strs);
void	get_var_content(t_m_fsm *fsm);

void	parsing_error_meta(t_state *current_state);

#endif
