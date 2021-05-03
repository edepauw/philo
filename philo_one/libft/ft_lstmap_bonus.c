/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgrangeo <tgrangeo@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/01 13:18:15 by thomasgrang       #+#    #+#             */
/*   Updated: 2020/10/01 13:29:55 by tgrangeo         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*f_list;
	t_list	*f_elem;

	f_list = NULL;
	if (!lst || !f)
		return (NULL);
	while (lst->next)
	{
		if (!(f_elem = ft_lstnew(f(lst->content))))
			ft_lstclear(&f_list, del);
		ft_lstadd_back(&f_list, f_elem);
		lst = lst->next;
	}
	if (!(f_elem = ft_lstnew(f(lst->content))))
		ft_lstclear(&f_list, del);
	ft_lstadd_back(&f_list, f_elem);
	return (f_list);
}
