/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgrangeo <tgrangeo@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/11 12:35:58 by tgrangeo          #+#    #+#             */
/*   Updated: 2020/10/01 13:32:55 by tgrangeo         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memset(void *b, int c, size_t len)
{
	size_t			i;
	unsigned char	x;
	char			*str;

	x = (unsigned char)c;
	str = (char *)b;
	i = 0;
	while (i < len)
	{
		str[i] = (char)x;
		i++;
	}
	return (b);
}
