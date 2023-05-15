/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaugu <aaugu@student.42lausanne.ch>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/05 10:42:28 by aaugu             #+#    #+#             */
/*   Updated: 2023/05/15 13:51:44 by aaugu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/parsing.h"
#include "../../includes/state_machine.h"
#include "../../libft/libft.h"
#include <unistd.h>
#include <stdlib.h>
#include <stdint.h>
#include <sys/types.h>
#include <stdarg.h>
#include <unistd.h>
#include <errno.h>
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>

int	main(int ac, char **av)
{
	// char	*input = "ls >>|a | cat >|b";
	t_token	**tokens;

	(void) ac;
	tokens = NULL;
	printf("0-cmd\n1-option\n2-redir_in\n3-infile\n4-heredoc\n5-limiter\n6-redir_out\n7-redir_out_ap\n8-outfile\n9-t_pipe\n\n");
	printf("Input : '%s'\n", av[1]);
	tokens = parsing(av[1]);
	if (tokens)
	{
		while ((*tokens))
		{
			printf("%d : '%s'\n", (*tokens)->type, (*tokens)->content);
			(*tokens) = (*tokens)->next;
		}
	}
	return (0);
}
