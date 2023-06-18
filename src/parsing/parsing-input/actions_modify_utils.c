/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions_modify_utils.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaugu <aaugu@student.42lausanne.ch>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/18 16:03:34 by aaugu             #+#    #+#             */
/*   Updated: 2023/06/18 21:26:29 by aaugu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "parsing_input_state_machine.h"
#include "libft.h"

void	interpret_var(t_fsm *fsm);
char	*find_env_var_content(char *var_name, t_fsm *fsm);

void	interpret_var_join(t_fsm *fsm)
{
	char	*tmp;

	if (fsm->tmp_size > 1)
		interpret_var(fsm);
	if (!fsm->tmp)
		return ;
	tmp = ft_strjoin(fsm->buf, fsm->tmp);
	if (!tmp)
	{
		parsing_error(fsm, NULL);
		return ;
	}
	join_var_to_buf(fsm, tmp);
	free(tmp);
}

void	interpret_var(t_fsm *fsm)
{
	char	*var;
	char	*tmp;

	tmp = ft_strjoin(fsm->tmp + 1, "=");
	if (!tmp)
	{
		parsing_error(fsm, NULL);
		free(tmp);
		return ;
	}
	var = find_env_var_content(tmp, fsm);
	if (!var)
	{
		parsing_error(fsm, NULL);
		return ;
	}
	free(tmp);
	free(fsm->tmp);
	fsm->tmp = var;
	fsm->tmp_size = ft_strlen(var);
}

char	*find_env_var_content(char *var_name, t_fsm *fsm)
{
	int		i;
	char	*var_content;

	var_content = ft_strdup("");
	if (!var_content)
		return (NULL);
	i = -1;
	while (++i < fsm->env_size)
	{
		if (ft_strnstr(fsm->env[i], var_name, ft_strlen(var_name)))
		{
			free(var_content);
			var_content = ft_strdup(fsm->env[i] + ft_strlen(var_name));
			if (!var_content)
				return (NULL);
			break ;
		}
	}
	return (var_content);
}

void	join_var_to_buf(t_fsm *fsm, char *tmp)
{
	free(fsm->buf);
	fsm->buf = (char *)ft_calloc((ft_strlen(fsm->tmp) + fsm->input_size + 1),
			sizeof(char));
	if (!fsm->buf)
	{
		parsing_error(fsm, NULL);
		return ;
	}
	ft_strlcpy(fsm->buf, tmp, ft_strlen(tmp) + 1);
	fsm->buf_size = ft_strlen(fsm->buf);
	reset_tmp_buf(fsm);
}
