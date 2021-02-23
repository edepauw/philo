/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgrangeo <tgrangeo@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/11 12:40:23 by tgrangeo          #+#    #+#             */
/*   Updated: 2021/01/13 16:16:50 by tgrangeo         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *src)
{
	int		i;
	char	*dest;

	dest = NULL;
	i = 0;
	if (!(dest = malloc(sizeof(char) * (ft_strlen(src) + 1))))
		return (0);
	while (src[i] != '\0')
	{
		dest[i] = src[i];
		i++;
	}
	dest[i] = '\0';
	return (dest);
}

char	*ft_strndup(const char *s, int len)
{
	int			i;
	char		*dup;

	i = 0;
	if (!(dup = (char*)malloc(sizeof(char) * (len + 1))))
		return (NULL);
	while (s[i] && i < len)
	{
		dup[i] = s[i];
		i++;
	}
	dup[i] = '\0';
	return (dup);
}
