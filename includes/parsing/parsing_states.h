/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_states.h                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaugu <aaugu@student.42lausanne.ch>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/26 15:10:52 by aaugu             #+#    #+#             */
/*   Updated: 2023/06/17 21:14:48 by aaugu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSING_STATES_H
# define PARSING_STATES_H

/******************************************************************************
*								ENUM									      *
******************************************************************************/

/* Differents possible states of a state machine */
typedef enum e_state
{
	idle,
	less_than,
	less_than_d,
	greater_than,
	greater_than_d,
	quote_s,
	quote_d,
	s_pipe,
	dollar,
	meta_chars,
	chars,
	error,
	malloc_err,
	stop,
}			t_state;

#endif
