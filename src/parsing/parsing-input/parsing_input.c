/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_input.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaugu <aaugu@student.42lausanne.ch>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/02 11:18:11 by aaugu             #+#    #+#             */
/*   Updated: 2023/06/20 13:38:09 by aaugu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "parsing_input.h"
#include "parsing_input_state_machine.h"
#include "libft.h"
#include "minishell.h"

void	check_end_syntax_error(t_token **tokens);

/* Parsing to retrieve each separate elements (tokens) of user input as an
element of the command and store them in a chained list. */
t_token	*parsing_input(char *input, char **env, int env_size, int last_exit)
{
	t_token	*tokens;

	tokens = state_machine(input, env, env_size, last_exit);
	if (tokens && tokens->content != NULL)
	{
		check_end_syntax_error(&tokens);
		if (!tokens)
		{
			printf("minishell: malloc() failed: %s\n", strerror(errno));
			g_exit_code = errno;
		}
	}
	return (tokens);
}

void	check_end_syntax_error(t_token **tokens)
{
	t_token	*tmp;

	if (tokens)
	{
		tmp = lst_last(*tokens);
		if (!ft_strcmp(tmp->content, "|"))
			printf("minishell: syntax error near unexpected token `|'\n");
		else if (!ft_strcmp(tmp->content, "<") || !ft_strcmp(tmp->content, ">")
			|| !ft_strcmp(tmp->content, "<<") || !ft_strcmp(tmp->content, ">>"))
			printf("minishell: syntax error near unexpected token `newline'\n");
		if (!ft_strcmp(tmp->content, "|") || !ft_strcmp(tmp->content, "<")
			|| !ft_strcmp(tmp->content, ">") || !ft_strcmp(tmp->content, "<<")
			|| !ft_strcmp(tmp->content, ">>"))
		{
			clear_tokens(tokens);
			*tokens = (t_token *)malloc(sizeof(t_token));
			(*tokens)->content = NULL;
			(*tokens)->next = NULL;
			g_exit_code = 258;
		}
	}
}

/* Pour afficher chaque élément séparé avec son type
	printf("0-command\n1-option\n2-redir_in\n3-infile\n4-heredoc\n5-limiter\n\
	6-redir_out\n7-redir_out_ap\n8-outfile\n9-t_pipe\n\n");
	// if (tokens)
	// {
	// 	while (tokens)
	// 	{
	// 		printf("%d : %s\n", tokens->type, tokens->content);
	// 		tokens = tokens->next;
	// 	}
	// }
*/
