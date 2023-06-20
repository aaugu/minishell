/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   state_dollar_quotes.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaugu <aaugu@student.42lausanne.ch>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/18 15:59:36 by aaugu             #+#    #+#             */
/*   Updated: 2023/06/19 23:23:15 by aaugu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "parsing_input_state_machine.h"
#include "libft.h"

void	dollar_quotes_empty(t_fsm *fsm, char c, int last_exit);
void	dollar_quotes_filled(t_fsm *fsm, char c);

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
		dollar_quotes_empty(fsm, c, last_exit);
	else if ((fsm->tmp_size > 1))
		dollar_quotes_filled(fsm, c);
}

void	dollar_quotes_empty(t_fsm *fsm, char c, int last_exit)
{
	if (c == '?')
		tmp_exit_code_stop_char(fsm, last_exit);
	if (ft_isalpha(c) || c == '_')
		add_to_tmp_buf(fsm, c);
	else
	{
		add_to_tmp_buf(fsm, c);
		join_var_to_buf(fsm, fsm->tmp);
		fsm->current_state = quote_d;
	}
}

void	dollar_quotes_filled(t_fsm *fsm, char c)
{
	if (ft_isalpha(c) || c == '_')
		add_to_tmp_buf(fsm, c);
	else if (c == '$')
		interpret_var_join(fsm);
	else
	{
		interpret_var_join(fsm);
		add_to_buf(fsm, c);
		fsm->current_state = quote_d;
	}
}
