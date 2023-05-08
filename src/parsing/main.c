/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaugu <aaugu@student.42lausanne.ch>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/05 10:42:28 by aaugu             #+#    #+#             */
/*   Updated: 2023/05/08 14:58:27 by aaugu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/parsing.h"

int	main(void)
{
	char	*input = "<<EOF cat|ls>outfile";
	t_token	*tokens;

	tokens = parsing(input);
	printf("%s\n", tokens->content);
}
