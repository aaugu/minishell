/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   state_machine.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaugu <aaugu@student.42lausanne.ch>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/05 11:51:45 by aaugu             #+#    #+#             */
/*   Updated: 2023/05/09 13:28:51 by aaugu            ###   ########.fr       */
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

t_token	*state_machine(t_state_machine *sm, char *input);

/* Each function will set current state and decide to perform an action if 
needed */
void	state_idle(char c, t_state_machine *sm, t_token *tokens);
void	state_less_than(char c, t_state_machine *sm, t_token *tokens);
void	state_less_than_d(char c, t_state_machine *sm, t_token *tokens);
void	state_greater_than(char c, t_state_machine *sm, t_token *tokens);
void	state_greater_than_d(char c, t_state_machine *sm, t_token *tokens);
void	state_quote_s(char c, t_state_machine *sm, t_token *tokens);
void	state_quote_d(char c, t_state_machine *sm, t_token *tokens);
void	state_pipe(char c, t_state_machine *sm, t_token *tokens);

/* ----------------------------- ACTIONS ------------------------------------*/
void	add_to_buf(char c, t_state_machine *sm);
void	finish_buf(t_state_machine *sm, t_token **tokens);
void	finish_add(char c, t_state_machine *sm, t_token *tokens);
void	finish_add_idle(char c, t_state_machine *sm, t_token *tokens);
void	finish_stop(t_state_machine *sm, t_token *tokens);

/* ----------------------------- UTILS ------------------------------------*/
t_token	*create_node(char *buffer, t_state_machine *sm, t_token **tokens);
t_token	*lst_last(t_token *lst);

/* ----------------------------- CLEAR ------------------------------------*/
void	clear_parsing(t_state_machine *sm, t_token **tokens);
void	clear_state_machine(t_state_machine *sm);
void	clear_tokens(t_token **tokens);

#endif