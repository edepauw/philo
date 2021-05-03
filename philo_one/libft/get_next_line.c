/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgrangeo <tgrangeo@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/01 13:36:06 by tgrangeo          #+#    #+#             */
/*   Updated: 2020/10/01 13:38:38 by tgrangeo         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

#define BUFFER_SIZE 5

static int		ft_error(char **mem)
{
	free(*mem);
	*mem = NULL;
	return (-1);
}

static int		ft_error_line(char **mem, char **line)
{
	free(*mem);
	free(*line);
	*mem = NULL;
	*line = NULL;
	return (-1);
}

static int		ft_scan(char **mem, char **line)
{
	int n;
	int size;

	n = ft_strchr_int(*mem, '\n');
	size = ft_strlen(*mem) - n - 1;
	if (n == 0)
	{
		if ((*line = ft_strndup("", 0)) == NULL)
			return (ft_error(mem));
		if ((*mem = ft_substr_free(*mem, 1, size)) == NULL)
			return (ft_error_line(mem, line));
		return (1);
	}
	else if (n > 0)
	{
		if ((*line = ft_strndup(*mem, n)) == NULL)
			return (ft_error(mem));
		if ((*mem = ft_substr_free(*mem, n + 1, size)) == NULL)
			return (ft_error_line(mem, line));
		return (1);
	}
	return (ft_error(mem));
}

int				get_next_line(int fd, char **line)
{
	char		buf[BUFFER_SIZE + 1];
	int			ret;
	static char *mem;

	if (!mem)
		mem = ft_strndup("", 0);
	else if ((ft_strchr_int(mem, '\n') >= 0))
		return (ft_scan(&mem, line));
	while ((ret = read(fd, buf, BUFFER_SIZE)) > 0)
	{
		buf[ret] = '\0';
		mem = ft_strjoin_free_s1(mem, buf);
		if ((ft_strchr_int(mem, '\n') >= 0))
			return (ft_scan(&mem, line));
	}
	if (ret == -1)
		return (-1);
	if (ret == 0)
		if ((*line = ft_strndup(mem, ft_strlen(mem))) == NULL)
			return (ft_error(&mem));
	free(mem);
	mem = NULL;
	return (0);
}
