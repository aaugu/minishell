/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_error.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaugu <aaugu@student.42lausanne.ch>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/08 09:55:57 by aaugu             #+#    #+#             */
/*   Updated: 2023/06/19 15:09:25 by aaugu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <errno.h>
#include "parsing_input_state_machine.h"
#include "minishell.h"

/* Handles error in state machine : Delivers error message and set state of 
state machine to error */
void	parsing_error(t_fsm *fsm, char *s)
{
	if (s)
	{
		if (!ft_strncmp(s, "newline", 7))
			printf("minishell: syntax error near unexpected token `%s'\n", s);
		else
			printf("minishell: syntax error near unexpected token `%c'\n", s[0]);
		g_exit_code = 258;
		fsm->current_state = error;
	}
	else
	{
		printf("minishell: malloc() failed: %s\n", strerror(errno));
		g_exit_code = errno;
		fsm->current_state = malloc_err;
	}
}
