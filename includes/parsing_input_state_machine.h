/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_input_state_machine.h                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaugu <aaugu@student.42lausanne.ch>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/05 11:51:45 by aaugu             #+#    #+#             */
/*   Updated: 2023/06/20 13:20:19 by aaugu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSING_INPUT_STATE_MACHINE_H
# define PARSING_INPUT_STATE_MACHINE_H

/******************************************************************************
*							    INCLUDE										  *
******************************************************************************/

# include "parsing_input.h"
# include "parsing_states.h"

/******************************************************************************
*								STRUCTS									      *
******************************************************************************/

/* State machine */
typedef struct s_fsm
{
	enum e_state	current_state;
	int				quotes;
	enum e_type		type;
	int				input_size;
	char			*buf;
	int				buf_size;
	char			*tmp;
	int				tmp_size;
	char			**env;
	int				env_size;
}					t_fsm;

/******************************************************************************
*							    FUNCTIONS									  *
******************************************************************************/

t_token	*state_machine(char *input, char **envp, int env_size, int last_exit);
void	create_state_machine(t_fsm *fsm, char **env, int env_size, char *input);
void	init_state_machine(t_fsm *fsm);
void	clear_state_machine(t_fsm *fsm);
t_token	*create_content_empty_token(t_fsm *fsm);

/* Each function will set current state and decide to perform an action if
needed */
void	state_idle(t_fsm *fsm, t_token **tokens, char c);
void	state_space(t_fsm *fsm, t_token **tokens, char c);
void	state_less_than(t_fsm *fsm, t_token **tokens, char c);
void	state_less_than_d(t_fsm *fsm, t_token **tokens, char c);
void	state_greater_than(t_fsm *fsm, t_token **tokens, char c);
void	state_greater_than_d(t_fsm *fsm, t_token **tokens, char c);
void	state_quote_s(t_fsm *fsm, t_token **tokens, char c);
void	state_quote_d(t_fsm *fsm, t_token **tokens, char c);
void	state_pipe(t_fsm *fsm, t_token **tokens, char c);
void	state_dollar_idle(t_fsm *fsm, t_token **tokens, char c, int last_exit);
void	state_dollar_quotes(t_fsm *fsm, char c, int last_exit);
void	state_meta_chars(t_fsm *fsm, char c);
void	state_limiter_no_quotes(t_fsm *fsm, t_token **tokens, char c);
void	state_limiter_quotes_s(t_fsm *fsm, t_token **tokens, char c);
void	state_limiter_quotes_d(t_fsm *fsm, t_token **tokens, char c);

/* --------------------------------- ACTIONS ---------------------------------*/
void	add_to_buf(t_fsm *fsm, char c);
void	add_to_tmp_buf(t_fsm *fsm, char c);
void	reset_tmp_buf(t_fsm *fsm);
void	change_state_and_type(t_fsm *fsm, t_state state, t_type type);
void	state_type_add_buf(t_fsm *fsm, t_state state, t_type type, char c);
void	change_state_quotes(t_fsm *fsm, t_state state);
void	change_buf_to_var_content(t_fsm *fsm);
void	interpret_var_join(t_fsm *fsm);
void	join_var_to_buf(t_fsm *fsm, char *save);
void	tmp_exit_code_stop_char(t_fsm *fsm, int last_exit);
t_token	*create_node(t_fsm *fsm);
t_token	*lst_last(t_token *token);
void	get_next_type(t_fsm *fsm, char c);
void	finish_buf(t_fsm *fsm, t_token **tokens, char c);
void	finish_add(t_fsm *fsm, t_token **tokens, char c);
void	finish_add_state(t_fsm *fsm, t_token **tokens, char c, int state);
void	finish_add_tmp_state(t_fsm *fsm, t_token **tokens, char c, int state);
void	finish_stop(t_fsm *fsm, t_token **tokens, char c);

/* ------------------------------ ERROR MESSAGES -----------------------------*/
void	parsing_error(t_fsm *fsm, char *c);

#endif
