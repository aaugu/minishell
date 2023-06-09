/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_meta_heredoc.h                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaugu <aaugu@student.42lausanne.ch>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/23 14:02:04 by aaugu             #+#    #+#             */
/*   Updated: 2023/06/08 11:33:30 by aaugu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSING_META_HEREDOC_H
# define PARSING_META_HEREDOC_H

char	*parsing_meta(char *s, char **env, int env_size);
char	*parsing_heredoc(char *s, char **env, int env_size);

#endif
