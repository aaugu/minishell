/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_meta_heredoc_state_machine.h               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaugu <aaugu@student.42lausanne.ch>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/23 14:08:12 by aaugu             #+#    #+#             */
/*   Updated: 2023/06/08 11:33:39 by aaugu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSING_META_HEREDOC_STATE_MACHINE_H
# define PARSING_META_HEREDOC_STATE_MACHINE_H

/******************************************************************************
*							    INCLUDE										  *
******************************************************************************/

# include "parsing_states.h"

/******************************************************************************
*								STRUCTS									      *
******************************************************************************/

typedef struct s_meta
{
	char			*content;
	struct s_meta	*next;
}					t_meta;

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
t_meta	*heredoc_state_machine(char *str, char **env, int env_size);

/* ------------------------------ FSM FUNCTIONS ------------------------------*/
void	create_meta_fsm(t_m_fsm *fsm, char **env, int env_size, char *s);
void	init_meta_state_machine(t_m_fsm *fsm);
void	clear_meta_state_machine(t_m_fsm *fsm);

/* ------------------------------ COMMON STATES ------------------------------*/
void	state_idle_meta(t_m_fsm *fsm, t_meta **meta_strs, char c);
void	state_dollar(t_m_fsm *fsm, t_meta **meta_strs, char c);

/* ------------------------------ SPECIFIC STATE -----------------------------*/
void	state_chars(t_m_fsm *fsm, t_meta **meta_strs, char c);
void	state_chars_heredoc(t_m_fsm *fsm, t_meta **meta_strs, char c);

/* --------------------------------- ACTIONS ---------------------------------*/
void	add_to_buf_meta(t_m_fsm *fsm, char c);
void	finish_buf_meta(t_m_fsm *fsm, t_meta **meta_strs);
void	get_var_content(t_m_fsm *fsm);

void	parsing_error_meta(t_state *current_state);

#endif
