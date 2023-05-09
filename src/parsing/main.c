/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaugu <aaugu@student.42lausanne.ch>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/05 10:42:28 by aaugu             #+#    #+#             */
/*   Updated: 2023/05/09 11:34:03 by aaugu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/parsing.h"
#include "../../includes/state_machine.h"
#include "../../libft/libft.h"
#include <unistd.h>
#include <limits.h>
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
#include <readline/readline.h>
#include <readline/history.h>
#include <signal.h>
#include <limits.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/wait.h>


int	main(void)
{
	char	*input = "<<EOF cat|ls>outfile";
	t_token	*tokens;

	tokens = parsing(input);
	while (tokens->next)
	{
		printf("ici\n");
		printf("%s\n", tokens->content);
		tokens = tokens->next;
	}
	return (0);
}
