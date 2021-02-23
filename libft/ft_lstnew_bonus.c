/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgrangeo <tgrangeo@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/30 10:51:06 by thomasgrang       #+#    #+#             */
/*   Updated: 2020/10/01 13:30:00 by tgrangeo         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstnew(void *content)
{
	t_list *lst;

	lst = malloc(sizeof(t_list));
	if (lst)
	{
		lst->content = content;
		lst->next = NULL;
	}
	else
		return (NULL);
	return (lst);
}
