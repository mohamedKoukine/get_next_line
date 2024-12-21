/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkaoukin <mkaoukin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/18 16:00:52 by mkaoukin          #+#    #+#             */
/*   Updated: 2023/12/19 11:05:03 by mkaoukin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

static char	*free_and_join(char *line, char *rest)
{
	char	*tmp;

	tmp = ft_strdup(line);
	free(line);
	if (!tmp && !rest)
		return (NULL);
	if (!rest)
		line = ft_strdup(tmp);
	else
		line = ft_strjo_or_cat(tmp, rest);
	free(tmp);
	return (line);
}

static char	*free_and_sub(char *rest)
{
	char	*tmp;

	if (ft_strchr(rest, '\n') == -1)
	{
		free(rest);
		rest = NULL;
	}
	else
	{
		tmp = ft_strdup(rest);
		free(rest);
		rest = ft_substr(tmp, ft_strchr(tmp, '\n') + 1, ft_strlen(tmp, 0));
		free(tmp);
	}
	return (rest);
}

static char	*ft_read(char *rest, int fd)
{
	int		i;
	char	*buff;

	buff = malloc(sizeof(char) * BUFFER_SIZE + 1);
	if (!buff)
		return (free(rest), NULL);
	i = 1;
	while (i != 0)
	{
		i = read(fd, buff, BUFFER_SIZE);
		if (i == -1)
			return (free(buff), free(rest), NULL);
		buff[i] = '\0';
		rest = ft_strjoin(rest, buff);
		if (ft_strchr(buff, '\n') > -1)
			break ;
	}
	free(buff);
	buff = NULL;
	return (rest);
}

int	ft_strchr(const char *s, int c)
{
	int	i;

	i = 0;
	if (!s || *s == '\0')
		return (-1);
	while (s[i] && s[i] != c)
		i++;
	if (s[i] == c)
		return (i);
	return (-1);
}

char	*get_next_line(int fd)
{
	static char	*rest[OPEN_MAX];
	char		*line;

	line = NULL;
	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	line = free_and_join(line, rest[fd]);
	if (ft_strchr(rest[fd], '\n') == -1 && rest[fd])
	{
		free(rest[fd]);
		rest[fd] = NULL;
	}
	if (ft_strchr(line, '\n') == -1)
	{
		rest[fd] = ft_read(rest[fd], fd);
		if (!rest[fd])
			return (free(line), NULL);
		line = free_and_join(line, rest[fd]);
	}
	rest[fd] = free_and_sub(rest[fd]);
	if (*line == '\0')
		return (free (line), free(rest[fd]), line = NULL, NULL);
	return (line);
}
