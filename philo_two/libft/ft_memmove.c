/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgrangeo <tgrangeo@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/01 13:19:08 by thomasgrang       #+#    #+#             */
/*   Updated: 2020/10/01 13:32:50 by tgrangeo         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	unsigned char	*tmp_dst;
	unsigned char	*tmp_src;
	size_t			i;
	int				size;

	size = len;
	i = 0;
	tmp_dst = (unsigned char*)dst;
	tmp_src = (unsigned char*)src;
	if (!(dst || src))
		return (NULL);
	if (src < dst)
		while (size > 0)
		{
			size--;
			*(tmp_dst + size) = *(tmp_src + size);
		}
	else
		while (i < len)
		{
			*(tmp_dst + i) = *(tmp_src + i);
			i++;
		}
	dst = tmp_dst;
	return (dst);
}
