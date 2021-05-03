/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgrangeo <tgrangeo@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/01 13:19:01 by thomasgrang       #+#    #+#             */
/*   Updated: 2020/10/01 13:32:46 by tgrangeo         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	size_t	i;
	char	*srce;
	char	*dest;

	if (!(dst || src))
		return (NULL);
	srce = (char *)src;
	dest = (char *)dst;
	i = 0;
	while (i < n)
	{
		dest[i] = srce[i];
		i++;
	}
	return (dst);
}
