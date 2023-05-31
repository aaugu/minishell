/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaugu <aaugu@student.42lausanne.ch>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/02 11:41:22 by lvogt             #+#    #+#             */
/*   Updated: 2023/05/31 11:36:37 by aaugu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	*ft_free_double(char **str)
{
	int	i;

	i = 0;
	if (str)
	{
		while (str[i])
			free(str[i++]);
		free(str);
	}
	str = NULL;
	return (NULL);
}

void	ft_ctrlc(int sig)
{
	(void)sig;
	printf("\n");
	rl_replace_line("", 0);
	rl_on_new_line();
	rl_redisplay();
	g_exit_code = 130;
}

void	ft_ctrld(t_data *data)
{
	printf("exit\n");
	g_exit_code = 0;
	clear_minishell(data);
}

void	ft_quit(int sig)
{
	(void)sig;
	rl_replace_line("", 0);
	rl_on_new_line();
	rl_redisplay();
	exit(3);
}

void	ft_sig_n_input(t_data *data)
{
	signal(SIGINT, ft_quit);
	data->heredoc.str = readline(">");
}
