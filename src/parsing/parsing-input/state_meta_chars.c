/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   state_meta_chars.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaugu <aaugu@student.42lausanne.ch>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/17 21:05:24 by aaugu             #+#    #+#             */
/*   Updated: 2023/06/18 00:08:54 by aaugu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdbool.h>
#include "../../../includes/parsing_input_state_machine.h"
#include "../../../libft/libft.h"

// void save_before_quotes(t_fsm *fsm, t_state state);

void	state_meta_chars(t_fsm *fsm, t_token **tokens, char c, int last_exit)
{
	// if (c == '?' || c == '$')
	// 	add_to_buf(fsm, c);
	if (c == '\'')
		fsm->buf[fsm->buf_size - 1] = '\0';
	if ((c == '?' || c == '\0' || c == '\'' || c == '\"' || c == '/' || c == '-'
		|| c == '<' || c == '>' || c == '|') && fsm->meta == true)
		change_buf_to_var_content(fsm, last_exit);
	if (c == '<' || c == '>' || c == '|')
		finish_add(fsm, tokens, c);
	if (c == '<')
		change_state_and_type(fsm, less_than, redir_in);
	else if (c == '>')
		change_state_and_type(fsm, greater_than, redir_out);
	else if (c == '|')
		change_state_and_type(fsm, s_pipe, t_pipe);
	else if (c == '\'')
		change_state_quotes(fsm, quote_s);
	else if (c == '\"')
		change_state_quotes(fsm, quote_d);
	else if (c == '\0')
		finish_stop(fsm, tokens, c);
	else if (c == ' ')
		finish_buf(fsm, tokens, c);
	else
	{
		add_to_buf(fsm, c);

	}
}

// void save_before_quotes(t_fsm *fsm, t_state state)
// {
// 	if (fsm->save)
// 		free(fsm->save);
// 	fsm->save = ft_strdup(fsm->buf);
// 	if (!fsm->save)
// 		parsing_error(fsm, NULL);
// 	change_state_quotes(fsm, state);
// }
