/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_ins.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaugu <aaugu@student.42lausanne.ch>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/17 11:05:05 by aaugu             #+#    #+#             */
/*   Updated: 2023/06/16 10:28:18 by aaugu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILT_INS_H
# define BUILT_INS_H

# include "minishell.h"

int		cmd_exit(t_data *data);
int		cmd_env(char **env, int env_size, char **cmd_args);
int		cmd_unset(t_data *data);

#endif