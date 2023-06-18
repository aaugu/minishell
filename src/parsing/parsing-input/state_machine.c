/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   state_machine.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaugu <aaugu@student.42lausanne.ch>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/05 11:54:32 by aaugu             #+#    #+#             */
/*   Updated: 2023/06/18 23:12:13 by aaugu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdbool.h>
#include "parsing_input_state_machine.h"
#include "libft.h"

void	loop_state_machine(t_fsm *fsm, t_token **tokens, char *str, int last_e);
void	exe_state_machine_one(t_fsm *fsm, t_token **tokens, char c);
void	exe_state_machine_two(t_fsm *fsm, t_token **tokens, char c, int last_e);

/* Finite state machine. Will loop on each char to know how to separate each
token in a lineary way. */
t_token	*state_machine(char *input, char **envp, int env_size, int last_exit)
{
	t_token	*tokens;
	t_fsm	fsm;

	create_state_machine(&fsm, envp, env_size, input);
	init_state_machine(&fsm);
	tokens = NULL;
	loop_state_machine(&fsm, &tokens, input, last_exit);
	if (fsm.current_state == error)
	{
		clear_tokens(&tokens);
		create_content_empty_token(&fsm, &tokens);
	}
	else if (fsm.current_state == malloc_err)
	{
		clear_tokens(&tokens);
		tokens = NULL;
	}
	clear_state_machine(&fsm);
	return (tokens);
}

void	loop_state_machine(t_fsm *fsm, t_token **tokens, char *str, int last_e)
{
	int	i;

	i = 0;
	while (i <= (int)ft_strlen(str))
	{
		if (fsm->current_state == error || fsm->current_state == malloc_err)
			break ;
		else
		{
			exe_state_machine_one(fsm, tokens, str[i]);
			exe_state_machine_two(fsm, tokens, str[i], last_e);
		}
		i++;
	}
}

/* Tells state machine what to do depending on current state. Method flexible,
as it is easy to modify and add conditions based on the state you're in. */
void	exe_state_machine_one(t_fsm *fsm, t_token **tokens, char c)
{
	if (fsm->current_state == idle)
		state_idle(fsm, tokens, c);
	else if (fsm->current_state == less_than)
		state_less_than(fsm, tokens, c);
	else if (fsm->current_state == less_than_d)
		state_less_than_d(fsm, tokens, c);
	else if (fsm->current_state == greater_than)
		state_greater_than(fsm, tokens, c);
	else if (fsm->current_state == greater_than_d)
		state_greater_than_d(fsm, tokens, c);
	else if (fsm->current_state == quote_s)
		state_quote_s(fsm, c);
	else if (fsm->current_state == quote_d)
		state_quote_d(fsm, c);
}

void	exe_state_machine_two(t_fsm *fsm, t_token **tokens, char c, int last_e)
{
	if (fsm->current_state == s_pipe)
		state_pipe(fsm, tokens, c);
	else if (fsm->current_state == dollar_idle)
		state_dollar_idle(fsm, tokens, c, last_e);
	else if (fsm->current_state == dollar_quotes)
		state_dollar_quotes(fsm, c, last_e);
	else if (fsm->current_state == meta_chars)
		state_meta_chars(fsm, c);
	else if (fsm->current_state == limiter_no_quotes)
		state_limiter_no_quotes(fsm, tokens, c);
	else if (fsm->current_state == limiter_quotes_s)
		state_limiter_quotes_s(fsm, tokens, c);
	else if (fsm->current_state == limiter_quotes_d)
		state_limiter_quotes_d(fsm, tokens, c);
}
