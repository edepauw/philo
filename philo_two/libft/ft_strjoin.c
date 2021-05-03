/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgrangeo <tgrangeo@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/01 13:20:02 by thomasgrang       #+#    #+#             */
/*   Updated: 2020/10/01 13:40:54 by tgrangeo         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	int		i;
	int		j;
	char	*new;

	if (!(s1))
		return (NULL);
	if (!(s2))
		return (NULL);
	j = 0;
	i = 0;
	if (!(new = malloc(ft_strlen(s1) + ft_strlen(s2) + 1 * sizeof(char))))
		return (NULL);
	if (s1[j] != '\0')
	{
		while (s1[j])
			new[i++] = s1[j++];
	}
	j = 0;
	if (s2[j] != '\0')
	{
		while (s2[j])
			new[i++] = s2[j++];
	}
	new[i] = '\0';
	return (new);
}

char	*ft_strjoin_free(char *s1, char *s2)
{
	char		*str;
	int			i;
	int			j;

	if (s1 && s2)
	{
		if (!(str = (char *)malloc(sizeof(char)
		* (ft_strlen(s1)) + (ft_strlen(s2) + 1))))
			return (NULL);
		i = 0;
		j = 0;
		while (s1[i])
			str[j++] = s1[i++];
		i = 0;
		while (s2[i])
			str[j++] = s2[i++];
		str[j] = '\0';
		free(s1);
		free(s2);
		return (str);
	}
	return (0);
}

char	*ft_strjoin_free_s1(char *s1, char const *s2)
{
	char		*str;
	int			i;
	int			j;

	if (s1 && s2)
	{
		if (!(str = (char *)malloc(sizeof(char)
		* (ft_strlen(s1)) + (ft_strlen(s2) + 1))))
			return (NULL);
		i = 0;
		j = 0;
		while (s1[i])
		{
			str[j++] = s1[i++];
		}
		i = 0;
		while (s2[i])
		{
			str[j++] = s2[i++];
		}
		str[j] = '\0';
		free(s1);
		return (str);
	}
	return (0);
}
