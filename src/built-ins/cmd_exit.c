/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_exit.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaugu <aaugu@student.42lausanne.ch>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/17 11:02:15 by aaugu             #+#    #+#             */
/*   Updated: 2023/05/17 12:12:04 by aaugu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	cmd_exit(t_data *data, int cmd_nbr)
{
	if (cmd_nbr == 1)
	{
		printf("exit\n");
		clear_minishell(data);
	}
}
