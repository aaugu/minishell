/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaugu <aaugu@student.42lausanne.ch>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/14 09:44:02 by lvogt             #+#    #+#             */
/*   Updated: 2023/05/17 10:52:45 by aaugu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H

# include <unistd.h>
# include <limits.h>
# include <stdlib.h>
# include <stdint.h>
# include <sys/types.h>
# include <stdarg.h>

# include "ft_printf.h"
# include "get_next_line.h"

typedef struct s_split	t_split;

struct					s_split
{
	char				k;
	int					i;
	int					j;
	int					wordlen;
	char				next_stop_char;
	char				*next_stop;
	char				**str;
	char				*start;
};

/* ************************************************************************** */
/*                                                                            */
/*                                 PART 1                                     */
/*                                                                            */
/* ************************************************************************** */

/* is... */
int				ft_isalpha(int c);
int				ft_isdigit(int c);
int				ft_isalnum(int c);
int				ft_isascii(int c);
int				ft_isprint(int c);

/* str... */
size_t			ft_strlen(const char *s);
char			*ft_strdup(const char *s);
size_t			ft_strlcpy(char *dst, const char *src, size_t size);
size_t			ft_strlcat(char *dst, const char *src, size_t size);
char			*ft_strchr(const char *s, int c);
char			*ft_strrchr(const char *s, int c);
int				ft_strncmp(const char *s1, const char *s2, size_t n);
char			*ft_strnstr(const char *big, const char *little, size_t len);

/* mem... */
void			*ft_memset(void *s, int c, size_t n);
void			*ft_memcpy(void *dest, const void *src, size_t n);
void			*ft_memmove(void *dest, const void *src, size_t n);
void			*ft_memchr(const void *s, int c, size_t n);
int				ft_memcmp(const void *s1, const void *s2, size_t n);
void			ft_bzero(void *s, size_t n);

/* to... */
int				ft_toupper(int c);
int				ft_tolower(int c);

/* Atoi */
int				ft_atoi(const char *nptr);

/* calloc */
void			*ft_calloc(size_t nmemb, size_t size);

/* ************************************************************************** */
/*                                                                            */
/*                                 PART 2                                     */
/*                                                                            */
/* ************************************************************************** */

char			*ft_substr(char const *s, unsigned int start, size_t len);
char			*ft_strjoin(char const *s1, char const *s2);
char			*ft_strtrim(char const *s1, char const *set);
char			**ft_split(char *s, char c);
char			*ft_itoa(int n);
char			*ft_strmapi(char const *s, char (*f)(unsigned int, char));
void			ft_striteri(char *s, void (*f)(unsigned int, char *));
void			ft_putchar_fd(char c, int fd);
void			ft_putstr_fd(char *s, int fd);
void			ft_putendl_fd(char *s, int fd);
void			ft_putnbr_fd(int n, int fd);

/* ************************************************************************** */
/*                                                                            */
/*                                 PART 3                                     */
/*                                                                            */
/* ************************************************************************** */

typedef struct s_list
{
	void			*content;
	struct s_list	*next;
}	t_list;

t_list			*ft_lstnew(void *content);
void			ft_lstadd_front(t_list **lst, t_list *new);
int				ft_lstsize(t_list *lst);
t_list			*ft_lstlast(t_list *lst);
void			ft_lstadd_back(t_list **lst, t_list *new);
void			ft_lstdelone(t_list *lst, void (*del)(void *));
void			ft_lstclear(t_list **lst, void (*del)(void *));
void			ft_lstiter(t_list *lst, void (*f)(void *));
t_list			*ft_lstmap(t_list *lst, void *(*f)(void *),
					void (*del)(void *));

/* ************************************************************************** */
/*                                                                            */
/*                                 PART 4                                     */
/*                                                                            */
/* ************************************************************************** */

u_long			ft_abs(long nb);
int				ft_sqrt(int nb);
int				ft_iterative_factorial(int nb);
int				ft_iterative_power(int nb, int power);
int				ft_recursive_factorial(int nb);
int				ft_recursive_power(int nb, int power);
int				ft_get_numlen(long n);
int				ft_get_numlen_base(long n, u_int base);
int				ft_get_unumlen(u_long nb);
int				ft_get_unumlen_base(u_long n, u_int base);
long			ft_atol(const char *nptr);
double			ft_atod(const char *nptr);
int				ft_fibonacci(int index);
int				ft_is_prime(int nb);
int				ft_find_next_prime(int nb);
char			*ft_ltoa(long n);
int				ft_putnbr_base_fd(long num, char *base, int fd);
char			*ft_strrev(char *str);

int				ft_strs_len(char **strs);
void			ft_strs_free(char **strs, int size);
char			**ft_strs_copy(const char **src, int size);

#endif
