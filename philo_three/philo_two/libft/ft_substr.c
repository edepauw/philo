/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edepauw <edepauw@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/01 13:35:50 by tgrangeo          #+#    #+#             */
/*   Updated: 2021/01/20 12:24:13 by edepauw          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	size_t	i;
	char	*dest;

	if (!(s))
		return (NULL);
	if (!(dest = malloc((len + 1) * sizeof(char))))
		return (NULL);
	i = 0;
	if ((int)start > ft_strlen(s))
	{
		dest[i] = '\0';
		return (dest);
	}
	while (i < len && s[start])
	{
		dest[i] = s[start];
		i++;
		start++;
	}
	dest[i] = '\0';
	return (dest);
}

char	*ft_substr_free(char *s, int start, int len)
{
	int		i;
	char	*dest;

	if (!(s))
		return (NULL);
	if (!(dest = malloc((len + 1) * sizeof(char))))
		return (NULL);
	i = 0;
	if (start > ft_strlen(s))
	{
		dest[i] = '\0';
		return (dest);
	}
	while (i < len && s[start])
	{
		dest[i] = s[start];
		i++;
		start++;
	}
	dest[i] = '\0';
	free(s);
	return (dest);
}
