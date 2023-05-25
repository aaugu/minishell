/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   state_machine_meta.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaugu <aaugu@student.42lausanne.ch>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/23 14:44:53 by aaugu             #+#    #+#             */
/*   Updated: 2023/05/25 14:06:37 by aaugu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <errno.h>
#include "../../includes/minishell.h"
#include "../../includes/parsing_meta.h"
#include "../../includes/parsing_meta_state_machine.h"
#include "../../libft/libft.h"

void	create_meta_state_machine(t_m_fsm *fsm, char **env, int env_size);
void	exe_meta_state_mach(t_m_fsm *fsm, t_meta **metas, char c);
void	clear_meta_state_machine(t_m_fsm *fsm);

t_meta	*meta_state_machine(char *str, char **env, int env_size)
{
	t_m_fsm	fsm;
	t_meta	*meta_strs;
	int		i;

	create_meta_state_machine(&fsm, env, env_size);
	if (!fsm.env)
		return (NULL);
	init_meta_state_machine(&fsm, ft_strlen(str));
	meta_strs = NULL;
	i = 0;
	while (i++ <= ft_strlen(str))
	{
		exe_meta_state_mach(&fsm, &meta_strs, str[i]);
		if (fsm.current_state == error)
			break ;
	}
	clear_meta_state_machine(&fsm);
	if (fsm.current_state == stop)
		return (meta_strs);
	return (NULL);
}

void	create_meta_state_machine(t_m_fsm *fsm, char **env, int env_size)
{
	fsm = (t_m_fsm *){0};
	fsm->current_state = idle;
	fsm->env_size = env_size;
	fsm->env = ft_strs_copy(env, env_size);
	if (!fsm->env)
		g_exit_code = print_err("minishell: malloc() failed: %s\n", errno);
}

void	exe_meta_state_mach(t_m_fsm *fsm, t_meta **metas, char c)
{
	if (fsm->current_state == idle)
		state_idle_meta(fsm, metas, c);
	else if (fsm->current_state == dollar)
		state_dollar(fsm, metas, c);
	else if (fsm->current_state == chars)
		state_chars(fsm, metas, c);
}

void	clear_meta_state_machine(t_m_fsm *fsm)
{
	if (fsm->buf)
		free(fsm->buf);
	if (fsm->env)
		ft_strs_free(fsm->env, fsm->env_size);
	fsm = (t_m_fsm *){0};
}
