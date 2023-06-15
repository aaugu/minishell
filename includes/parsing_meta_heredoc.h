/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_meta_heredoc.h                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lvogt <marvin@42lausanne.ch>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/23 14:02:04 by aaugu             #+#    #+#             */
/*   Updated: 2023/06/15 10:25:51 by lvogt            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSING_META_HEREDOC_H
# define PARSING_META_HEREDOC_H

char	*parsing_meta(char *s, char **env, int env_size, int last_exit);
char	*parsing_heredoc(char *s, char **env, int env_size, int last_exit);

#endif
