/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgrangeo <tgrangeo@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/01 13:35:31 by tgrangeo          #+#    #+#             */
/*   Updated: 2020/10/01 13:35:33 by tgrangeo         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *haystack, const char *needle, size_t len)
{
	unsigned long int i;
	unsigned long int j;

	if (ft_strlen(needle) > ft_strlen(haystack))
		return (NULL);
	i = 0;
	if (needle[0] == '\0')
		return ((void*)haystack);
	if (len <= 0)
		return (0);
	while (haystack[i] != '\0')
	{
		j = 0;
		while (needle[j] == haystack[i + j] && (i + j) < len)
		{
			if (needle[j + 1] == '\0')
				return ((void*)haystack + i);
			else if (j == len - 1)
				return ((void*)haystack + i);
			j++;
		}
		i++;
	}
	return (0);
}
