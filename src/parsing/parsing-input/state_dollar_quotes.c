/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   state_dollar_quotes.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaugu <aaugu@student.42lausanne.ch>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/18 15:59:36 by aaugu             #+#    #+#             */
/*   Updated: 2023/06/19 03:10:36 by aaugu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "parsing_input_state_machine.h"
#include "libft.h"

void	specials_or_meta_chars(t_fsm *fsm, char c, int last_exit);

void	state_dollar_quotes(t_fsm *fsm, char c, int last_exit)
{
	if (c == '\"')
	{
		interpret_var_join(fsm);
		fsm->current_state = idle;
	}
	else if (c == '\0')
		parsing_error(fsm, "\"");
	else if (fsm->tmp_size == 1)
		specials_or_meta_chars(fsm, c, last_exit);
	else if ((fsm->tmp_size > 1))
	{
		if (c == '$')
			join_var_to_buf(fsm, fsm->tmp);
		else
			add_to_tmp_buf(fsm, c);
	}
}

void	specials_or_meta_chars(t_fsm *fsm, char c, int last_exit)
{
	if (c == '-' || c == '$' || ft_isdigit(c))
	{
		fsm->tmp[0] = '\0';
		join_var_to_buf(fsm, fsm->tmp);
		change_state_quotes(fsm, quote_d);
	}
	else if (c == '/' || c == '<' || c == '>' || c == '|' || c == '\''
		|| c == ' ')
	{
		add_to_tmp_buf(fsm, c);
		join_var_to_buf(fsm, fsm->tmp);
		change_state_quotes(fsm, quote_d);
	}
	else if (c == '?')
		tmp_exit_code_stop_char(fsm, last_exit);
	else
	{
		add_to_tmp_buf(fsm, c);
		fsm->current_state = meta_chars;
	}
}

void	state_meta_chars(t_fsm *fsm, char c)
{
	if (c == '\"')
	{
		interpret_var_join(fsm);
		fsm->current_state = idle;
	}
	else if (c == '\0')
		parsing_error(fsm, "\"");
	else if (c == '$')
	{
		interpret_var_join(fsm);
		add_to_tmp_buf(fsm, c);
		fsm->current_state = dollar_quotes;
	}
	else if (c == '-' || c == '\'' || c == '$' || c == ' ' || c == '<'
		|| c == '>' || c == '|' || c == '/')
	{
		interpret_var_join(fsm);
		add_to_buf(fsm, c);
		change_state_quotes(fsm, quote_d);
	}
	else
		add_to_tmp_buf(fsm, c);
}
