/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaugu <aaugu@student.42lausanne.ch>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/05 10:42:28 by aaugu             #+#    #+#             */
/*   Updated: 2023/05/11 14:38:24 by aaugu            ###   ########.fr       */
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

int	main(void)
{
	char	*input = "<<EOF \'$PATH\' cat|ls>outfile";
	t_token	**tokens;

	tokens = NULL;
	tokens = parsing(input);
	while ((*tokens))
	{
		printf("%s\n", (*tokens)->content);
		(*tokens) = (*tokens)->next;
	}
	return (0);
}
