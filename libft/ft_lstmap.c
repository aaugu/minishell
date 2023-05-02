/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lvogt <marvin@42lausanne.ch>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/14 09:42:14 by lvogt             #+#    #+#             */
/*   Updated: 2022/10/17 15:14:08 by lvogt            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*lstnew;
	t_list	*lstfinal;

	if (!lst || !f || !del)
		return (NULL);
	lstfinal = NULL;
	while (lst)
	{
		lstnew = ft_lstnew(f(lst->content));
		if (!lstnew)
		{
			ft_lstclear(&lst, del);
			return (NULL);
		}
		ft_lstadd_back(&lstfinal, lstnew);
		lst = lst->next;
	}
	return (lstfinal);
}
