/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lvogt <marvin@42lausanne.ch>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/25 08:37:28 by lvogt             #+#    #+#             */
/*   Updated: 2023/03/14 11:06:49 by lvogt            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 402
# endif

# include <stdlib.h>
# include <sys/types.h>
# include <sys/uio.h>
# include <unistd.h>

typedef struct s_buffer	t_buffer;
typedef t_buffer		t_read;
typedef t_buffer		t_line;

struct					s_buffer
{
	char				*buf;
	int					pos;
	int					size;
};

char					*get_next_line(int fd);
void					*ft_memcpy(void *dst, const void *src, size_t n);

#endif
