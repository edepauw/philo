/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgrangeo <tgrangeo@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/15 10:06:41 by tgrangeo          #+#    #+#             */
/*   Updated: 2020/10/01 13:34:45 by tgrangeo         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char		**ft_free(char **res, int i)
{
	while (i >= 0)
	{
		free(res[i]);
		i--;
	}
	free(res);
	return (NULL);
}

static int		ft_count(char const *s, char c)
{
	int i;
	int count;

	i = 0;
	count = 0;
	while (s[i])
	{
		while (s[i] && s[i] == c)
			i++;
		if (s[i] && s[i] != c)
		{
			count++;
			while (s[i] && s[i] != c)
				s++;
		}
	}
	return (count);
}

static char		*ft_malloccpy(char const *s, char c)
{
	char	*str;
	int		i;

	i = 0;
	while (s[i] && s[i] != c)
		i++;
	if (!(str = (char*)malloc(sizeof(char) * (i + 1))))
		return (NULL);
	i = 0;
	while (s[i] && s[i] != c)
	{
		str[i] = s[i];
		i++;
	}
	str[i] = '\0';
	return (str);
}

char			**ft_split(char const *s, char c)
{
	int		words;
	int		i;
	char	**res;

	i = 0;
	if (!(s))
		return (NULL);
	words = ft_count(s, c);
	if (!(res = (char **)malloc(sizeof(char *) * (words + 1))))
		return (NULL);
	while (*s)
	{
		while (*s && *s == c)
			s++;
		if (*s && *s != c)
		{
			if (!(res[i] = ft_malloccpy(s, c)))
				return (ft_free(res, i - 1));
			i++;
			while (*s && *s != c)
				s++;
		}
	}
	res[i] = NULL;
	return (res);
}
