/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   state_machine.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaugu <aaugu@student.42lausanne.ch>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/05 11:51:45 by aaugu             #+#    #+#             */
/*   Updated: 2023/05/15 11:04:06 by aaugu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STATE_MACHINE_H
# define STATE_MACHINE_H

/******************************************************************************
*							    INCLUDE										  *
******************************************************************************/

# include "parsing.h"

/******************************************************************************
*							    FUNCTIONS									  *
******************************************************************************/

t_token	**state_machine(t_sm *sm, char *input);

/* Each function will set current state and decide to perform an action if 
needed */
void	state_idle(t_sm *sm, t_token **tokens, char c);
void	state_less_than(t_sm *sm, t_token **tokens, char c);
void	state_less_than_d(t_sm *sm, t_token **tokens, char c);
void	state_greater_than(t_sm *sm, t_token **tokens, char c);
void	state_greater_than_d(t_sm *sm, t_token **tokens, char c);
void	state_minus(t_sm *sm, t_token **tokens, char c);
void	state_quote_s(t_sm *sm, t_token **tokens, char c);
void	state_quote_d(t_sm *sm, t_token **tokens, char c);
void	state_pipe(t_sm *sm, t_token **tokens, char c);

/* --------------------------------- ACTIONS ---------------------------------*/
void	add_to_buf(t_sm *sm, char c);
void	change_state_and_type(t_sm *sm, t_state state, t_type type, char c);
void	state_type_add_buf(t_sm *sm, t_state state, t_type type, char c);

void	finish_buf(t_sm *sm, t_token **tokens, char c);
void	finish_add(t_sm *sm, t_token **tokens, char c);
void	finish_add_idle(t_sm *sm, t_token **tokens, char c);
void	finish_stop(t_sm *sm, t_token **tokens, char c);

/* ---------------------------------- UTILS ----------------------------------*/
t_token	*create_node(char *buffer, t_type type, t_sm *sm, t_token **tokens);
t_token	*lst_last(t_token *lst);

/* ---------------------------------- CLEAR ----------------------------------*/
void	clear_parsing(t_sm *sm, t_token **tokens);
void	clear_state_machine(t_sm *sm);
void	clear_tokens(t_token **tokens);

#endif