/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   state_dollar.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaugu <aaugu@student.42lausanne.ch>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/17 21:05:24 by aaugu             #+#    #+#             */
/*   Updated: 2023/06/18 15:54:24 by aaugu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdbool.h>
#include "../../../includes/parsing_input_state_machine.h"
#include "../../../libft/libft.h"

void	state_dollar_idle(t_fsm *fsm, t_token **tokens, char c)
{
	if (fsm->tmp_size == 1)
	{
		if (c == '-' || c == '\'' || c == '\"' || c == '$' || c == '/'
			|| c == '?' || c == ' ' || c == '<' || c == '>' || c == '|'
			|| c == '\0')
			tmp_empty_stop_char(fsm, tokens, c);
		else
			add_to_tmp_buf(fsm, c);
	}
	else if ((fsm->tmp_size > 1))
	{
		if (c == '-' || c == '\'' || c == '\"' || c == '$' || c == '/'
			|| c == '?' || c == ' ' || c == '<' || c == '>' || c == '|'
			|| c == '\0')
			tmp_filled_stop_char(fsm, tokens, c);
		else
			add_to_tmp_buf(fsm, c);
	}
}

void	tmp_empty_stop_char(t_fsm *fsm, t_token **tokens, char c)
{
	if (c == '-' || c == '\'' || c == '\"' || c == '$' || c == ' ' || c == '<'
		|| c == '>' || c == '|' || c == '\0')
		fsm->tmp[fsm->tmp_size - 1] = '\0';
	if (c == '/' || c == '?')
		add_to_tmp_buf(fsm, c);
	if (c == ' ' || c == '<' || c == '>' || c == '|' || c == '\0')
		add_to_buf(fsm, '$');
	if (c == '<' || c == '>' || c == '|')
		finish_add(fsm, tokens, c);
	if (c == '-' || c == '$' || c == ' ' || c == '/' || c == '?')
		fsm->current_state = idle;
	if (c == '?')
		get_var_join(fsm, tokens);
	else if (c == '\'')
		change_state_quotes(fsm, quote_s);
	else if (c == '\"')
		change_state_quotes(fsm, quote_d);
	else if (c == '<')
		change_state_and_type(fsm, less_than, redir_in);
	else if (c == '>')
		change_state_and_type(fsm, greater_than, redir_out);
	else if (c == '|')
		change_state_and_type(fsm, s_pipe, t_pipe);
	else if (c == '\0')
		finish_stop(fsm, tokens, c);
}

void	tmp_filled_stop_char(t_fsm *fsm, t_token **tokens, char c)
{
	get_var_join(fsm, tokens);
	if (c == '-' || c == '/' || c == '?')
		add_to_buf(fsm, c);
	if (c == '<' || c == '>' || c == '|')
		finish_add(fsm, tokens, c);
	if (c == '-' || c == ' ' || c == '/' || c == '?')
		fsm->current_state = idle;
	if (c == '$')
		add_to_tmp_buf(fsm, c);
	else if (c == '\'')
		change_state_quotes(fsm, quote_s);
	else if (c == '\"')
		change_state_quotes(fsm, quote_d);
	else if (c == '<')
		change_state_and_type(fsm, less_than, redir_in);
	else if (c == '>')
		change_state_and_type(fsm, greater_than, redir_out);
	else if (c == '|')
		change_state_and_type(fsm, s_pipe, t_pipe);
	else if (c == '\0')
		finish_stop(fsm, tokens, c);
}

/*
void	get_var_join(t_fsm *fsm, t_token **tokens);
{
	char	*var;
	char	*tmp;

	var = get_var_content(fsm);
	if (!var)
	{
		parsing_error(fsm, NULL);
		return ;
	}
	free(fsm->tmp);
	fsm->tmp = NULL;
	tmp = (char *)ft_calloc((ft_strlen(var) + fsm->input_size + 1), sizeof(char));
	if (!tmp)
	{
		parsing_error(fsm, NULL);
		free(var);
		return ;
	}
	ft_strlcpy(fsm->tmp, meta_str, ft_strlen(meta_str) + 1);
	free(meta_str);
	fsm->tmp_size = ft_strlen(fsm->tmp);
}

char	*get_var_content(t_fsm *fsm)
{
	char	*buf;
	char	*var;

	var = ft_strjoin(fsm->tmp + 1, "=");
	if (!var)
	{
		parsing_error(fsm, NULL);
		free(var);
		return (NULL);
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
	return (buf);
}

char	*find_var_content(char *var, t_fsm *fsm)
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
				parsing_error_(fsm, NULL);
				return (NULL);
			}
			break ;
		}
		i++;
	}
	return (buf);
}



void	change_buf_to_var_content(t_fsm *fsm, int last_exit)
{
	char	*meta_str;

	meta_str = parsing_meta(fsm->tmp, fsm->env, fsm->env_size, last_exit);
	if (!meta_str)
		parsing_error(fsm, NULL);
	free(fsm->tmp);
	fsm->tmp = NULL;
	fsm->tmp = (char *)ft_calloc((ft_strlen(meta_str) + fsm->input_size \
	+ 1), sizeof(char));
	if (!fsm->tmp)
		parsing_error(fsm, NULL);
	ft_strlcpy(fsm->tmp, meta_str, ft_strlen(meta_str) + 1);
	free(meta_str);
	fsm->tmp_size = ft_strlen(fsm->tmp);
}
*/
