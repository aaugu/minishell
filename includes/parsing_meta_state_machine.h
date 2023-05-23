/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_meta_state_machine.h                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaugu <aaugu@student.42lausanne.ch>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/23 14:08:12 by aaugu             #+#    #+#             */
/*   Updated: 2023/05/23 14:19:25 by aaugu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSING_META_STATE_MACHINE_H
# define PARSING_META_STATE_MACHINE_H

typedef enum e_m_state
{
	idle,
	dollar,
	chars,
	error,
	stop,
}			t_m_state;

typedef struct s_m_fsm
{
	enum e_m_state	current_state;
	char			*buf;
	int				buf_size;
}					t_m_fsm;

#endif