/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgrangeo <tgrangeo@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/01 13:35:36 by tgrangeo          #+#    #+#             */
/*   Updated: 2021/01/04 15:41:17 by tgrangeo         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	int		i;
	char	*str;

	str = (char *)s;
	i = ft_strlen(str);
	while (!(str[i] == c))
	{
		if (i == 0)
			return (0);
		i--;
	}
	return (&str[i]);
}

int		ft_strrchr_int(const char *s, int c)
{
	int		i;
	char	*str;

	str = (char *)s;
	i = ft_strlen(str);
	while (!(str[i] == c))
	{
		if (i == 0)
			return (0);
		i--;
	}
	return (i);
}
