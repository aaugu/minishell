/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_ins.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaugu <aaugu@student.42lausanne.ch>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/17 11:05:05 by aaugu             #+#    #+#             */
/*   Updated: 2023/05/30 12:47:40 by aaugu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILT_INS_H
# define BUILT_INS_H

# include "minishell.h"

void	cmd_exit(t_data *data, char **cmd_args, int cmd_nbr);
void	cmd_env(char **env, int env_size, char **cmd_args);
void	cmd_unset(char **env, int env_size, char **cmd_args);

#endif