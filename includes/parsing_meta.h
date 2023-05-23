/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_meta.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaugu <aaugu@student.42lausanne.ch>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/23 14:02:04 by aaugu             #+#    #+#             */
/*   Updated: 2023/05/23 14:57:06 by aaugu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSING_META_H
# define PARSING_META_H

typedef struct s_meta
{
	char	*content;
	t_meta	*next;
}			t_meta;

char	*meta_interpret(char *s);

#endif