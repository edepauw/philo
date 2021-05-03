/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memccpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgrangeo <tgrangeo@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/11 12:22:16 by tgrangeo          #+#    #+#             */
/*   Updated: 2020/10/01 13:30:08 by tgrangeo         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memccpy(void *dst, const void *src, int c, size_t n)
{
	size_t					i;
	unsigned char			*dst1;
	unsigned const char		*src1;

	if (!(dst || src))
		return (0);
	i = 0;
	dst1 = (unsigned char *)dst;
	src1 = (unsigned char *)src;
	while (i < n)
	{
		if (src1[i] == (unsigned char)c)
		{
			dst1[i] = src1[i];
			return (dst1 + i + 1);
		}
		dst1[i] = src1[i];
		i++;
	}
	return (0);
}
