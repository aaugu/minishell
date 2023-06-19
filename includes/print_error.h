/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_error.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lvogt <marvin@42lausanne.ch>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/23 15:22:01 by aaugu             #+#    #+#             */
/*   Updated: 2023/06/19 18:41:35 by lvogt            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PRINT_ERROR_H
# define PRINT_ERROR_H

#include "minishell.h"

int		print_err(char *message, int errnum);
void	exit_print_error(t_data *d, int errnum);

#endif