/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgrangeo <tgrangeo@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/14 17:36:04 by tgrangeo          #+#    #+#             */
/*   Updated: 2020/10/01 13:35:47 by tgrangeo         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		ft_firstindex(const char *s1, const char *set)
{
	int i;
	int j;

	i = 0;
	j = 0;
	while (set[j] && s1[i])
	{
		if (s1[i] == set[j])
		{
			i++;
			j = 0;
		}
		else
			j++;
	}
	if (s1[i] == '\0')
		return (0);
	return (i);
}

int		ft_lastindex(const char *s1, const char *set)
{
	int i;
	int j;

	i = ft_strlen(s1) - 1;
	j = 0;
	while (set[j] && s1[i] && i >= 0)
	{
		if (s1[i] == set[j])
		{
			i--;
			j = 0;
		}
		else
			j++;
	}
	if (i == 0)
		return (0);
	return (i + 1);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	char	*dest;
	int		first;
	int		last;

	if (!(s1))
		return (NULL);
	if (!set || s1[0] == '\0' || set[0] == '\0')
		return (ft_strdup(s1));
	dest = NULL;
	first = ft_firstindex(s1, set);
	last = ft_lastindex(s1, set);
	if (!(dest = malloc((last - first + 1) * sizeof(char))))
		return (NULL);
	ft_memcpy(dest, s1 + first, last - first);
	last = last - first;
	dest[last] = '\0';
	return (dest);
}
