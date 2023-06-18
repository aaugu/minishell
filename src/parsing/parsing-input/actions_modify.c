/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions_modify.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaugu <aaugu@student.42lausanne.ch>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/12 10:03:33 by aaugu             #+#    #+#             */
/*   Updated: 2023/06/18 16:52:27 by aaugu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "parsing_input_state_machine.h"
#include "libft.h"

void	interpret_var(t_fsm *fsm);
char	*find_env_var_content(char *var_name, t_fsm *fsm);

/* Add char to current buffer */
void	add_to_buf(t_fsm *fsm, char c)
{
	fsm->buf[fsm->buf_size] = c;
	fsm->buf_size++;
}

/* Add char to temporary buffer (used after a $ is encountered until a
finishing char of interpretation) */
void	add_to_tmp_buf(t_fsm *fsm, char c)
{
	fsm->buf[fsm->buf_size] = c;
	fsm->buf_size++;
}

void	reset_tmp_buf(t_fsm *fsm)
{
	if (fsm->tmp)
		free(fsm->tmp);
	fsm->tmp = (char *)ft_calloc(fsm->input_size + 1, sizeof(char));
	if (!fsm->tmp)
		parsing_error(fsm, 0);
	fsm->tmp_size = 0;
}

void	interpret_var_join(t_fsm *fsm)
{
	char	*tmp;

	interpret_var(fsm);
	if (!fsm->tmp)
		return ;
	tmp = ft_strjoin(fsm->buf, fsm->tmp);
	if (!tmp)
	{
		parsing_error(fsm, NULL);
		return ;
	}
	free(fsm->buf);
	fsm->buf = (char *)ft_calloc((ft_strlen(fsm->tmp) + fsm->input_size + 1), sizeof(char));
	if (!fsm->buf)
	{
		parsing_error(fsm, NULL);
		return ;
	}
	ft_strlcpy(fsm->buf, tmp, ft_strlen(tmp));
	free(tmp);
	fsm->buf_size = ft_strlen(fsm->buf);
	reset_tmp_buf(fsm);
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
