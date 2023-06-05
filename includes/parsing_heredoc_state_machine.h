/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_heredoc_state_machine.h                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaugu <aaugu@student.42lausanne.ch>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/05 15:22:10 by aaugu             #+#    #+#             */
/*   Updated: 2023/06/05 15:22:27 by aaugu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSING_HEREDOC_STATE_MACHINE_H
# define PARSING_HEREDOC_STATE_MACHINE_H

/******************************************************************************
*							    INCLUDE										  *
******************************************************************************/

# include "parsing_meta.h"
# include "parsing_states.h"

/******************************************************************************
*								STRUCTS									      *
******************************************************************************/

typedef struct s_m_fsm
{
	enum e_state	current_state;
	char			*buf;
	char			**env;
	int				buf_size;
	int				env_size;
	int				len;
}					t_m_fsm;

/******************************************************************************
*							    FUNCTIONS									  *
******************************************************************************/

t_meta	*meta_state_machine(char *str, char **env, int env_size);
void	init_meta_state_machine(t_m_fsm *fsm);

/* ---------------------------------- STATES ---------------------------------*/
void	state_idle_meta(t_m_fsm *fsm, t_meta **meta_strs, char c);
void	state_dollar(t_m_fsm *fsm, t_meta **meta_strs, char c);
void	state_chars(t_m_fsm *fsm, t_meta **meta_strs, char c);

/* --------------------------------- ACTIONS ---------------------------------*/
void	add_to_buf_meta(t_m_fsm *fsm, char c);
void	finish_buf_meta(t_m_fsm *fsm, t_meta **meta_strs);

void	parsing_error_meta(t_state *current_state);

#endif
