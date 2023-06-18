/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_meta.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaugu <aaugu@student.42lausanne.ch>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/23 14:02:29 by aaugu             #+#    #+#             */
/*   Updated: 2023/06/18 23:04:01 by aaugu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/parsing_meta.h"
#include "../../../includes/parsing_meta_state_machine.h"
#include "../../../libft/libft.h"

/*
After parsing input
Parsing to interpret env variable call ($), it will separate into element
strings (state machine will change string to variable content if found in
environment) in a chained list, and re-combine all as one string */
char	*parsing_meta(char *s, char **env, int env_size, int last_exit)
{
	char	*interpreted_str;
	char	*tmp;
	t_meta	*meta_strs;
	t_meta	*next;

	meta_strs = meta_state_machine(s, env, env_size, last_exit);
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
	interpreted_str = parsing_meta("qwertyuiop", env, 34);
	printf("%s\n%s\n", "qwertyuiop", interpreted_str);
	// interpreted_str = parsing_meta("$$bla$PATH$NOPE bouh$LANG", env, 34);
	// printf("%s\n%s\n", "$$bla$PATH$NOPE bouh$LANG", interpreted_str);
	return (0);
}
*/
