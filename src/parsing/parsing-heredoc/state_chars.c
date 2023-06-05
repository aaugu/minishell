/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   state_chars.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaugu <aaugu@student.42lausanne.ch>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/02 15:30:35 by aaugu             #+#    #+#             */
/*   Updated: 2023/06/05 15:10:26 by aaugu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"
#include "../../../includes/parsing_meta_state_machine.h"
#include "../../../libft/libft.h"

void	get_var_content(t_m_fsm *fsm);
char	*find_var_content(char *var, t_m_fsm *fsm);

void	state_chars(t_m_fsm *fsm, t_meta **meta_strs, char c)
{
	if (c == '$' || c == ' ' || c == '\0')
	{
		fsm->buf[fsm->buf_size] = '\0';
		get_var_content(fsm);
		if (fsm->current_state == error)
			return ;
		finish_buf_meta(fsm, meta_strs);
	}
	if (c == '$')
	{
		add_to_buf_meta(fsm, c);
		fsm->current_state = dollar;
	}
	else if (c == ' ')
	{
		add_to_buf_meta(fsm, c);
		fsm->current_state = idle;
	}
	else if (c == '\0')
		fsm->current_state = stop;
	else
		add_to_buf_meta(fsm, c);
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
