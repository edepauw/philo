/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgrangeo <tgrangeo@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/04 10:23:35 by tgrangeo          #+#    #+#             */
/*   Updated: 2020/10/01 13:29:02 by tgrangeo         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstclear(t_list **lst, void (*del)(void*))
{
	t_list	*to_del_next;
	t_list	*to_del;

	if (!lst || !*lst || !del)
		return ;
	to_del = (*lst)->next;
	ft_lstdelone((*lst), del);
	while (to_del->next)
	{
		to_del_next = to_del->next;
		ft_lstdelone((*lst), del);
		to_del = to_del_next;
	}
	ft_lstdelone(to_del, del);
	*lst = NULL;
}
