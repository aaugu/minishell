/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_heredoc.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaugu <aaugu@student.42lausanne.ch>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/02 15:30:28 by aaugu             #+#    #+#             */
/*   Updated: 2023/06/05 16:41:10 by aaugu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/parsing_meta_heredoc_state_machine.h"
#include "../../../libft/libft.h"

/*
Parsing of heredoc content :
Parsing to interpret env variable call ($), it will separate into element
strings (state machine will change string to variable content if found in
environment) in a chained list, and re-combine all as one string */
char	*parsing_meta_heredoc(char *s, char **env, int env_size)
{
	char	*interpreted_str;
	char	*tmp;
	t_meta	*meta_strs;
	t_meta	*next;

	meta_strs = heredoc_state_machine(s, env, env_size);
	interpreted_str = ft_strdup("");
	if (!interpreted_str)
		return (NULL);
	while (meta_strs != NULL)
	{
		next = meta_strs->next;
		tmp = ft_strjoin(interpreted_str, meta_strs->content);
		if (!tmp)
			return (NULL);
		free(interpreted_str);
		interpreted_str = tmp;
		if (meta_strs->content)
			free(meta_strs->content);
		free(meta_strs);
		meta_strs = next;
	}
	return (interpreted_str);
}

/*
#include <stdio.h>

int	main(int ac, char **av, char **env)
{
	char	*interpreted_str;

	(void) ac;
	(void) av;
	interpreted_str = parsing_meta_heredoc("$$bla'$PATH'\nNOPE bouh$LANG", \
	env, ft_strs_len(env));
	printf("%s\n%s\n", "$$bla'$PATH'\nNOPE bouh$LANG", interpreted_str);
	return (0);
}
*/
