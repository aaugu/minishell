/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_fd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaugu <aaugu@student.42lausanne.ch>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/08 12:57:53 by lvogt             #+#    #+#             */
/*   Updated: 2023/06/19 15:09:32 by aaugu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* ft_err_open_less:
 *	Ecrit le message d'erreur 
 */
void	ft_err_open_less(t_token *token, t_data *d)
{
	if (ft_strlen(token->next->content) != 0)
	{
		write(2, "minishell: ", 11);
		write(2, token->next->content, ft_strlen(token->next->content));
		write(2, ": No such file or directory\n", 28);
	}
	ft_free_child(token, d);
	exit(1);
}

void	ft_err_open_great(t_token *token, t_data *d)
{
	if (ft_strlen(token->next->content) != 0)
	{
		write(2, token->next->content, ft_strlen(token->next->content));
		write(2, ": Permission denied\n", 20);
	}
	ft_free_child(token, d);
	exit(4);
}

/* ft_fd_error:
 *	Ecrit les messages d'erreur pour les cas :
 *	ERR_OPEN_LESS, ERR_OPEN_GREAT ou ERR_DUP2
 */
void	ft_fd_error(t_token *token, t_data *d, int flag)
{
	if (flag == ERR_OPEN_LESS)
		ft_err_open_less(token, d);
	else if (flag == ERR_OPEN_GREAT)
		ft_err_open_great(token, d);
	else if (flag == ERR_DUP2)
	{
		write(2, "Dup2, error\n", 12);
		ft_free_child(token, d);
		exit(EXIT_SUCCESS);
	}
}
