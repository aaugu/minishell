/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   state_dollar_idle.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaugu <aaugu@student.42lausanne.ch>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/17 21:05:24 by aaugu             #+#    #+#             */
/*   Updated: 2023/06/19 14:40:51 by aaugu            ###   ########.fr       */
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
		if (c == '?')
			tmp_exit_code_stop_char(fsm, last_exit);
		else if (ft_isalpha(c) || c == '_')
			add_to_tmp_buf(fsm, c);
		else
			tmp_empty_stop_char(fsm, tokens, c);
	}
	else if ((fsm->tmp_size > 1))
	{
		if (ft_isalpha(c) || c == '_' || ft_isdigit(c))
			add_to_tmp_buf(fsm, c);
		else
			tmp_filled_stop_char(fsm, tokens, c);
	}
}

void	tmp_empty_stop_char(t_fsm *fsm, t_token **tokens, char c)
{
	if (ft_isdigit(c) || c == '\'' || c == '\"')
		fsm->tmp[fsm->tmp_size - 1] = '\0';
	if (c == '<' || c == '>' || c == '|')
		finish_add(fsm, tokens, c);
	else
	{
		add_to_tmp_buf(fsm, c);
		join_var_to_buf(fsm, fsm->tmp);
	}
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
	else
		fsm->current_state = idle;
}

void	tmp_filled_stop_char(t_fsm *fsm, t_token **tokens, char c)
{
	interpret_var_join(fsm);
	if (c == '$')
	{
		add_to_tmp_buf(fsm, c);
		fsm->current_state = dollar_idle;
	}
	else if (c == '<' || c == '>' || c == '|')
		finish_add(fsm, tokens, c);
	else if (!ft_isalpha(c) && (c != '_' || c != '\'' || c != '\"'))
	{
		add_to_buf(fsm, c);
		fsm->current_state = idle;
	}
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
