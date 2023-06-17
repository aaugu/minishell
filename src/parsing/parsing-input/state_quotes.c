/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   state_quotes.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaugu <aaugu@student.42lausanne.ch>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/05 09:55:39 by aaugu             #+#    #+#             */
/*   Updated: 2023/06/18 00:07:57 by aaugu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdbool.h>
#include <stdio.h>
#include "../../../includes/parsing_input_state_machine.h"
#include "../../../includes/parsing_meta.h"
#include "../../../libft/libft.h"

void	change_after_save(t_fsm *fsm, int last_exit);

/* Will set current state according to char and decide which action to perform
if needed */
void	state_quote_s(t_fsm *fsm, char c)
{
	if (c == '\'')
		change_state_quotes(fsm, idle);
	else if (c == '\0')
		parsing_error(fsm, "'");
	else
		add_to_buf(fsm, c);
}

/* Will set current state according to char and decide which action to perform
if needed */
void	state_quote_d(t_fsm *fsm, char c, int last_exit)
{
	// (void) last_exit;
	if ((c == '?' || c == '\0' || c == '\'' || c == '/' ||
		c == '-') && fsm->meta == true)
	{
		if (fsm->save)
			change_after_save(fsm, last_exit);
		else
			change_buf_to_var_content(fsm, last_exit);
	}
	if (c == '$')
		state_type_add_buf(fsm, meta_chars, fsm->type, c);
	else if (c == '\"')
		change_state_quotes(fsm, meta_chars);
	else if (c == '\0')
		parsing_error(fsm, "\"");
	else
		add_to_buf(fsm, c);
}

void	change_after_save(t_fsm *fsm, int last_exit)
{
	int	i;
	char	*tmp;

	i = 0;
	while (fsm->save[i] == fsm->buf[i])
		i++;
	tmp = parsing_meta(fsm->buf + i, fsm->env, fsm->env_size, last_exit);
	if (!tmp)
		parsing_error(fsm, NULL);
	free(fsm->buf);
	fsm->buf = NULL;
	fsm->buf = ft_strjoin(fsm->save, tmp);
	if (!fsm->buf)
		parsing_error(fsm, NULL);
	free(fsm->save);
	fsm->save = NULL;
	free(tmp);
}
