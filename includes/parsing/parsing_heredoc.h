/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_heredoc.h                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaugu <aaugu@student.42lausanne.ch>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/23 14:02:04 by aaugu             #+#    #+#             */
/*   Updated: 2023/06/17 22:48:43 by aaugu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSING_HEREDOC_H
# define PARSING_HEREDOC_H

char	*parsing_heredoc(char *s, char **env, int env_size, int last_exit);

#endif
