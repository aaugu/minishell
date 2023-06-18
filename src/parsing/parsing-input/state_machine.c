/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   state_machine.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaugu <aaugu@student.42lausanne.ch>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/05 11:54:32 by aaugu             #+#    #+#             */
/*   Updated: 2023/06/18 11:37:18 by aaugu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdbool.h>
#include "../../../includes/parsing_input_state_machine.h"
#include "../../../libft/libft.h"

void	create_state_machine(t_fsm *fsm, char **env, int env_size, char *input);
void	execute_state_machine(t_fsm *fsm, t_token **tokens, char c, int last_e);
void	clear_state_machine(t_fsm *fsm);

/* Finite state machine. Will loop on each char to know how to separate each
token in a lineary way. */
t_token	*state_machine(char *input, char **envp, int env_size, int last_exit)
{
	t_token	*tokens;
	t_fsm	fsm;
	int		i;

	create_state_machine(&fsm, envp, env_size, input);
	init_state_machine(&fsm);
	tokens = NULL;
	i = 0;
	while (i <= (int)ft_strlen(input))
	{
		if (fsm.current_state == error || fsm.current_state == malloc_err)
			break ;
		else
			execute_state_machine(&fsm, &tokens, input[i], last_exit);
		i++;
	}
	if (fsm.current_state == error)
		create_content_empty_token(&fsm, &tokens);
	else if (fsm.current_state == malloc_err)
	{
		clear_tokens(&tokens);
		tokens = NULL;
	}
	clear_state_machine(&fsm);
	return (tokens);
}

/* Tells state machine what to do depending on current state. Method flexible,
as it is easy to modify and add conditions based on the state you're in. */
void	execute_state_machine(t_fsm *fsm, t_token **tokens, char c, int last_e)
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
		state_quote_d(fsm, c, last_e);
	else if (fsm->current_state == s_pipe)
		state_pipe(fsm, tokens, c);
	else if (fsm->current_state == dollar_idle)
		state_dollar_idle(fsm, tokens, c, last_e);
	else if (fsm->current_state == dollar_quotes)
		state_dollar_quote(fsm, tokens, c, last_e);
}

/* Create base of finite state machine */
void	create_state_machine(t_fsm *fsm, char **env, int env_size, char *input)
{
	fsm->buf = NULL;
	fsm->buf_size = 0;
	fsm->input_size = ft_strlen(input);
	fsm->current_state = idle;
	fsm->type = command;
	fsm->tmp = NULL;
	fsm->env_size = env_size;
	fsm->env = ft_strs_copy((const char **)env, env_size);
	if (!fsm->env)
		parsing_error(fsm, NULL);
}

/* Clear allocated memory of finite state machine */
void	clear_state_machine(t_fsm *fsm)
{
	if (fsm->buf)
		free(fsm->buf);
	if (fsm->tmp)
		free(fsm->tmp);
	if (fsm->env)
	{
		ft_strs_free(fsm->env, fsm->env_size);
		fsm->env = NULL;
	}
	fsm = (t_fsm *){0};
}
