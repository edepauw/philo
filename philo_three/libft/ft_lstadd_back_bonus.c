/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_back_bonus.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgrangeo <tgrangeo@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/04 10:38:33 by tgrangeo          #+#    #+#             */
/*   Updated: 2020/10/01 13:28:54 by tgrangeo         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstadd_back(t_list **alst, t_list *new)
{
	t_list *last;

	last = NULL;
	if (*alst == NULL)
		*alst = new;
	else
	{
		last = ft_lstlast(*alst);
		last->next = new;
		new->next = NULL;
	}
}
