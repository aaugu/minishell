/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_heredoc.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaugu <aaugu@student.42lausanne.ch>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/02 15:30:28 by aaugu             #+#    #+#             */
/*   Updated: 2023/06/02 15:46:12 by aaugu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// #include "../../../includes/parsing_meta.h"
// #include "../../../includes/parsing_meta_state_machine.h"
// #include "../../../libft/libft.h"


// char	*parsing_meta(char *s, char **env, int env_size)
// {
// 	char	*interpreted_str;
// 	char	*tmp;
// 	t_meta	*meta_strs;
// 	t_meta	*next;

// 	meta_strs = meta_state_machine(s, env, env_size);
// 	interpreted_str = ft_strdup("");
// 	if (!interpreted_str)
// 		return (NULL);
// 	while (meta_strs != NULL)
// 	{
// 		next = meta_strs->next;
// 		tmp = ft_strjoin(interpreted_str, meta_strs->content);
// 		if (!tmp)
// 			return (NULL);
// 		free(interpreted_str);
// 		interpreted_str = tmp;
// 		if (meta_strs->content)
// 			free(meta_strs->content);
// 		free(meta_strs);
// 		meta_strs = meta_strs->next;
// 	}
// 	return (interpreted_str);
// }

// /*
// #include <stdio.h>

// int	main(int ac, char **av, char **env)
// {
// 	char	*interpreted_str;

// 	(void) ac;
// 	(void) av;
// 	interpreted_str = parsing_meta("qwertyuiop", env, 34);
// 	printf("%s\n%s\n", "qwertyuiop", interpreted_str);
// 	// interpreted_str = parsing_meta("$$bla$PATH$NOPE bouh$LANG", env, 34);
// 	// printf("%s\n%s\n", "$$bla$PATH$NOPE bouh$LANG", interpreted_str);
// 	return (0);
// }
// */