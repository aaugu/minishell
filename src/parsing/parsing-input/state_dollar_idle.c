/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   state_dollar_idle.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaugu <aaugu@student.42lausanne.ch>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/17 21:05:24 by aaugu             #+#    #+#             */
/*   Updated: 2023/06/19 01:53:27 by aaugu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing_input_state_machine.h"
#include "libft.h"
#include "minishell.h"

void	tmp_empty_stop_char(t_fsm *fsm, t_token **tokens, char c);
void	tmp_exit_code_stop_char(t_fsm *fsm, int last_exit);
void	tmp_filled_stop_char(t_fsm *fsm, t_token **tokens, char c);

void	state_dollar_idle(t_fsm *fsm, t_token **tokens, char c, int last_exit)
{
	if (fsm->tmp_size == 1)
	{
		if (c == '-' || c == '\'' || c == '\"' || c == '$' || c == '/'
			|| c == ' ' || c == '<' || c == '>' || c == '|' || c == '\0'
			|| ft_isdigit(c))
			tmp_empty_stop_char(fsm, tokens, c);
		else if (c == '?')
			tmp_exit_code_stop_char(fsm, last_exit);
		else
			add_to_tmp_buf(fsm, c);
	}
	else if ((fsm->tmp_size > 1))
	{
		if (c == '-' || c == '\'' || c == '\"' || c == '$' || c == '/'
			|| c == '?' || c == ' ' || c == '<' || c == '>' || c == '|'
			|| c == '\0' || ft_isdigit(c))
			tmp_filled_stop_char(fsm, tokens, c);
		else
			add_to_tmp_buf(fsm, c);
	}
}

void	tmp_empty_stop_char(t_fsm *fsm, t_token **tokens, char c)
{
	if (c == '-' || c == '\'' || c == '\"' || c == '$' || c == ' ' || c == '<'
		|| c == '>' || c == '|' || c == '\0' || ft_isdigit(c))
		fsm->tmp[fsm->tmp_size - 1] = '\0';
	if (c == '/')
		add_to_tmp_buf(fsm, c);
	if (c == ' ' || c == '<' || c == '>' || c == '|' || c == '\0')
		add_to_buf(fsm, '$');
	if (c == '<' || c == '>' || c == '|')
		finish_add(fsm, tokens, c);
	if (c == '-' || c == '$' || c == ' ' || c == '/' || ft_isdigit(c))
		fsm->current_state = idle;
	if (c == '\'')
		change_state_quotes(fsm, quote_s);
	else if (c == '\"')
		change_state_quotes(fsm, quote_d);
	else if (c == '<')
		change_state_and_type(fsm, less_than, redir_in);
	else if (c == '>')
		change_state_and_type(fsm, greater_than, redir_out);
	else if (c == '|')
		change_state_and_type(fsm, s_pipe, t_pipe);
	else if (c == '\0')
		finish_stop(fsm, tokens, c);
}

void	tmp_filled_stop_char(t_fsm *fsm, t_token **tokens, char c)
{
	interpret_var_join(fsm);
	if (c == '-' || c == '/' || c == '?')
		add_to_buf(fsm, c);
	if (c == '<' || c == '>' || c == '|')
		finish_add(fsm, tokens, c);
	if (c == '-' || c == ' ' || c == '/' || c == '?' || ft_isdigit(c))
		fsm->current_state = idle;
	if (c == '$')
		add_to_tmp_buf(fsm, c);
	else if (c == '\'')
		change_state_quotes(fsm, quote_s);
	else if (c == '\"')
		change_state_quotes(fsm, quote_d);
	else if (c == '<')
		change_state_and_type(fsm, less_than, redir_in);
	else if (c == '>')
		change_state_and_type(fsm, greater_than, redir_out);
	else if (c == '|')
		change_state_and_type(fsm, s_pipe, t_pipe);
	else if (c == '\0')
		finish_stop(fsm, tokens, c);
}

void	tmp_exit_code_stop_char(t_fsm *fsm, int last_exit)
{
	free(fsm->tmp);
	fsm->tmp = ft_itoa(last_exit);
	if (!fsm->tmp)
	{
		parsing_error(fsm, NULL);
		return ;
	}
	join_var_to_buf(fsm, fsm->tmp);
	fsm->current_state = idle;
}
