/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   state_machine.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaugu <aaugu@student.42lausanne.ch>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/05 11:51:45 by aaugu             #+#    #+#             */
/*   Updated: 2023/05/05 14:25:50 by aaugu            ###   ########.fr       */
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

/* Each function will set current state according to char and add to/finish 
buffer if needed */
void	state_idle(char c, t_state_machine *sm, t_token *tokens);
void	state_less_than(char c, t_state_machine *sm, t_token *tokens);
void	state_less_than_d(char c, t_state_machine *sm, t_token *tokens);
void	state_greater_than(char c, t_state_machine *sm, t_token *tokens);
void	state_greater_than_d(char c, t_state_machine *sm, t_token *tokens);
void	state_backslash(char c, t_state_machine *sm, t_token *tokens);
void	state_quote_s(char c, t_state_machine *sm, t_token *tokens);
void	state_quote_d(char c, t_state_machine *sm, t_token *tokens);
void	state_pipe(char c, t_state_machine *sm, t_token *tokens);

/* ------------------------------ TOOLS -------------------------------------*/
void	finish_and_reset_buf(t_state_machine *sm, t_token *tokens);
void	add_to_buf(char c, t_state_machine *sm, t_token *tokens);
void	finish_add(char c, t_state_machine *sm, t_token *tokens);

#endif