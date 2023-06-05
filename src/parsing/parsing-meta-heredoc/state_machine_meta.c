/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   state_machine_meta.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaugu <aaugu@student.42lausanne.ch>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/23 14:44:53 by aaugu             #+#    #+#             */
/*   Updated: 2023/06/05 15:47:10 by aaugu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <errno.h>
#include <stdlib.h>
#include "../../../includes/minishell.h"
#include "../../../includes/parsing_meta_heredoc.h"
#include "../../../includes/parsing_meta_heredoc_state_machine.h"
#include "../../../libft/libft.h"

void	execute_meta_state_machine(t_m_fsm *fsm, t_meta **metas, char c);

t_meta	*meta_state_machine(char *str, char **env, int env_size)
{
	t_m_fsm	fsm;
	t_meta	*meta_strs;
	int		i;

	create_meta_fsm(&fsm, env, env_size, str);
	if (!fsm.env)
		return (NULL);
	init_meta_state_machine(&fsm);
	meta_strs = NULL;
	i = 0;
	while (i <= (int)ft_strlen(str))
	{
		execute_meta_state_machine(&fsm, &meta_strs, str[i]);
		if (fsm.current_state == error)
			break ;
		i++;
	}
	clear_meta_state_machine(&fsm);
	if (fsm.current_state == stop)
		return (meta_strs);
	return (NULL);
}

void	create_meta_fsm(t_m_fsm *fsm, char **env, int env_size, char *str)
{
	fsm->buf = NULL;
	fsm->buf_size = 0;
	fsm->current_state = idle;
	fsm->env_size = env_size;
	fsm->env = ft_strs_copy((const char **)env, env_size);
	if (!fsm->env)
	{
		printf("minishell: malloc() failed: %s\n", strerror(errno));
		g_exit_code = errno;
	}
	fsm->len = ft_strlen(str);
}

void	init_meta_state_machine(t_m_fsm *fsm)
{
	if (fsm->buf)
		free(fsm->buf);
	fsm->buf = (char *)ft_calloc(fsm->len, sizeof(char));
	if (!fsm->buf)
		parsing_error_meta(&(fsm->current_state));
	fsm->buf_size = 0;
}

void	execute_meta_state_machine(t_m_fsm *fsm, t_meta **metas, char c)
{
	if (fsm->current_state == idle)
		state_idle_meta(fsm, metas, c);
	else if (fsm->current_state == dollar)
		state_dollar(fsm, metas, c);
	else if (fsm->current_state == chars)
		state_chars(fsm, metas, c);
	else if (fsm->current_state == stop)
		return ;
}

void	clear_meta_state_machine(t_m_fsm *fsm)
{
	if (fsm->buf)
		free(fsm->buf);
	if (fsm->env)
		ft_strs_free(fsm->env, fsm->env_size);
}
