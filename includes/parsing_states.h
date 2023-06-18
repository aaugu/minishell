/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_states.h                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaugu <aaugu@student.42lausanne.ch>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/26 15:10:52 by aaugu             #+#    #+#             */
/*   Updated: 2023/06/19 00:12:34 by aaugu            ###   ########.fr       */
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
	limiter_quotes_s,
	limiter_quotes_d,
	limiter_no_quotes,
	quote_s,
	quote_d,
	s_pipe,
	dollar,
	dollar_idle,
	dollar_quotes,
	meta_chars,
	chars,
	error,
	malloc_err,
	stop,
}			t_state;

#endif
