/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_meta_state_machine.h                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaugu <aaugu@student.42lausanne.ch>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/23 14:08:12 by aaugu             #+#    #+#             */
/*   Updated: 2023/05/23 16:44:53 by aaugu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSING_META_STATE_MACHINE_H
# define PARSING_META_STATE_MACHINE_H

/******************************************************************************
*							    INCLUDE										  *
******************************************************************************/

# include "parsing_meta.h"

/******************************************************************************
*								ENUM									      *
******************************************************************************/

typedef enum e_m_state
{
	idle,
	dollar,
	chars,
	error,
	stop,
}			t_m_state;

/******************************************************************************
*								STRUCTS									      *
******************************************************************************/

typedef struct s_m_fsm
{
	enum e_m_state	current_state;
	char			*buf;
	int				buf_size;
}					t_m_fsm;

/******************************************************************************
*							    FUNCTIONS									  *
******************************************************************************/

t_meta	*meta_state_machine(char *str);

void	state_idle_meta(t_m_fsm *fsm, t_meta **meta_chars, char *s);
void	state_dollar(t_m_fsm *fsm, t_meta **meta_chars, char *s);
void	state_chars(t_m_fsm *fsm, t_meta **meta_chars, char *s);


#endif