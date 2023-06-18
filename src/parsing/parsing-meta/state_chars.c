/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   state_chars.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaugu <aaugu@student.42lausanne.ch>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/23 16:37:55 by aaugu             #+#    #+#             */
/*   Updated: 2023/06/19 00:42:46 by aaugu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"
#include "../../../includes/parsing_meta_state_machine.h"
#include "../../../libft/libft.h"

char	*find_var_content(char *var, t_m_fsm *fsm);

/* Will set current state according to char and decide which action to perform
if needed */
void	state_chars(t_m_fsm *fsm, t_meta **meta_strs, char c)
{
	if (c == '$')
	{
		add_to_buf_meta(fsm, c);
		fsm->current_state = dollar;
	}
	else if (c == '\0')
	{
		get_var_content(fsm);
		if (fsm->current_state == error)
			return ;
		finish_state_meta(fsm, meta_strs, idle);
	}
	else if (ft_isalnum(c) || c == '_')
		add_to_buf_meta(fsm, c);
	else
	{
		get_var_content(fsm);
		if (fsm->current_state == error)
			return ;
		finish_state_meta(fsm, meta_strs, idle);
		add_to_buf_meta(fsm, c);
	}
}

void	get_var_content(t_m_fsm *fsm)
{
	char	*buf;
	char	*var;

	var = ft_strjoin(fsm->buf + 1, "=");
	if (!var)
	{
		parsing_error_meta(&(fsm->current_state));
		free(var);
		return ;
	}
	buf = find_var_content(var, fsm);
	free(var);
	free(fsm->buf);
	if (buf)
	{
		fsm->buf = buf;
		fsm->buf_size = ft_strlen(buf);
	}
	else
	{
		fsm->buf = ft_strdup("");
		if (!fsm->buf)
			parsing_error_meta(&(fsm->current_state));
	}
}

char	*find_var_content(char *var, t_m_fsm *fsm)
{
	int		i;
	char	*buf;

	buf = NULL;
	i = 0;
	while (i < fsm->env_size)
	{
		if (ft_strnstr(fsm->env[i], var, ft_strlen(var)))
		{
			buf = ft_strdup(fsm->env[i] + ft_strlen(var));
			if (!buf)
			{
				parsing_error_meta(&(fsm->current_state));
				return (NULL);
			}
			break ;
		}
		i++;
	}
	return (buf);
}

/*
int	main(int ac, char **av, char **env)
{
	t_m_fsm	fsm;

	(void) ac;
	(void) av;
	fsm.buf = ft_strdup("PATH");
	fsm.buf_size = ft_strlen(fsm.buf);
	fsm.env = ft_strs_copy((const char **)env, ft_strs_len(env));
	fsm.env_size = ft_strs_len(env);

	printf("BUF BEFORE : %s\n", fsm.buf);
	get_var_content(&fsm);
	printf("BUFF AFTER : %s\n", fsm.buf);
	return (0);
}
*/
