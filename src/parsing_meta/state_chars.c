/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   state_chars.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaugu <aaugu@student.42lausanne.ch>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/23 16:37:55 by aaugu             #+#    #+#             */
/*   Updated: 2023/05/25 14:46:07 by aaugu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"
#include "../../includes/parsing_meta_state_machine.h"
#include "../../libft/libft.h"

void	find_var_content(t_m_fsm *fsm);

void	state_chars(t_m_fsm *fsm, t_meta **meta_strs, char c)
{
	if (c == '$')
	{
		find_var_content(fsm);
		if (fsm->current_state == error)
			return ;
		finish_buf_meta();
		add_to_buf_meta(fsm, c);
		fsm->current_state = dollar;
	}
	else if (c == ' ')
	{
		find_var_content(fsm);
		finish_buf_meta();
		fsm->current_state = idle;
	}
	else if (c == '\0')
		fsm->current_state = stop;
	else
		add_to_buf_meta(fsm, c);
}

void	find_var_content(t_m_fsm *fsm)
{
	int		i;
	char	*buf;
	char	*var;

	buf = NULL;
	var = ft_strjoin(fsm->buf + 1, "=");
	if (!var)
	{
		parsing_error(&fsm->current_state);
		return ;
	}
	i = 0;
	while (i++ < fsm->env_size)
	{
		if (ft_strnstr(fsm->env[i], "PATH=", 5))
		{
			buf = ft_strdup(fsm->env[i] + ft_strlen(var));
			if (!buf)
			{
				parsing_error(&fsm->current_state);
				return ;
			}
			return ;
		}
		i++;
	}
	if (buf)
	{
		free(fsm->buf);
		fsm->buf = buf;
		fsm->buf_size = ft_strlen(buf);
	}
}

/* Handles error in state machine : Delivers error message and set state of 
state machine to error */
void	parsing_error(t_m_state *current_state)
{
	printf("minishell: malloc() failed: %s\n", strerror(errno));
	g_exit_code = errno;
	current_state = error;
}
