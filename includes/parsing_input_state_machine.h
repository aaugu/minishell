/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_input_state_machine.h                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaugu <aaugu@student.42lausanne.ch>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/05 11:51:45 by aaugu             #+#    #+#             */
/*   Updated: 2023/05/26 15:11:42 by aaugu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSING_INPUT_STATE_MACHINE_H
# define PARSING_INPUT_STATE_MACHINE_H

/******************************************************************************
*							    INCLUDE										  *
******************************************************************************/

# include "parsing_input.h"
# include "parsing.h"

/******************************************************************************
*								STRUCTS									      *
******************************************************************************/

/* State machine */
typedef struct s_fsm
{
	enum e_state	current_state;
	char			*buf;
	int				buf_size;
	int				input_size;
	int				meta;
	int				quotes;
	enum e_type		type;
}					t_fsm;

/******************************************************************************
*							    FUNCTIONS									  *
******************************************************************************/

t_token	*state_machine(char *input);
void	init_state_machine(t_fsm *fsm);

/* Each function will set current state and decide to perform an action if 
needed */
void	state_idle(t_fsm *fsm, t_token **tokens, char c);
void	state_less_than(t_fsm *fsm, t_token **tokens, char c);
void	state_less_than_d(t_fsm *fsm, t_token **tokens, char c);
void	state_greater_than(t_fsm *fsm, t_token **tokens, char c);
void	state_greater_than_d(t_fsm *fsm, t_token **tokens, char c);
void	state_quote_s(t_fsm *fsm, char c);
void	state_quote_d(t_fsm *fsm, char c);
void	state_pipe(t_fsm *fsm, t_token **tokens, char c);

/* --------------------------------- ACTIONS ---------------------------------*/
void	add_to_buf(t_fsm *fsm, char c);
void	change_state_and_type(t_fsm *fsm, t_state state, t_type type, char c);
void	state_type_add_buf(t_fsm *fsm, t_state state, t_type type, char c);

void	finish_buf(t_fsm *fsm, t_token **tokens, char c);
void	finish_add(t_fsm *fsm, t_token **tokens, char c);
void	finish_add_idle(t_fsm *fsm, t_token **tokens, char c);
void	finish_stop(t_fsm *fsm, t_token **tokens, char c);

/* ------------------------------ ERROR MESSAGES -----------------------------*/
void	parsing_error(t_fsm *fsm, char *c);

#endif