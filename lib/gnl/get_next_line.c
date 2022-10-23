/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tnuyten <tnuyten@student.codam.nl>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/28 19:07:55 by tnuyten           #+#    #+#             */
/*   Updated: 2021/11/28 16:23:41 by tnuyten          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*do_read(int fd, char *buf, char *storage, ssize_t *stored)
{
	ssize_t	stored_temp;

	stored_temp = 1;
	if (ft_strlen(buf))
		storage = ft_strjoin_free(storage, take_line_from_buffer(buf));
	while (ft_strchr(storage, '\n') == NULL && stored_temp > 0)
	{
		stored_temp = read(fd, buf, BUFFER_SIZE);
		if (stored_temp == -1)
		{
			free(storage);
			return (NULL);
		}
		if (stored_temp == 0)
			break ;
		*stored += stored_temp;
		storage = ft_strjoin_free(storage, take_line_from_buffer(buf));
	}
	return (storage);
}

char	*get_next_line(int fd)
{
	static char	buf[BUFFER_SIZE + 1];
	char		*storage;
	ssize_t		stored;

	if (ft_strchr(buf, '\n'))
		return (take_line_from_buffer(buf));
	storage = ft_substr("", 0, 0);
	stored = 0;
	if (ft_strlen(buf))
		return (do_read(fd, buf, storage, &stored));
	storage = do_read(fd, buf, storage, &stored);
	if (stored == -1 || stored == 0)
	{
		free(storage);
		return (NULL);
	}
	return (storage);
}

char	*take_line_from_buffer(char *buf)
{
	char	*line;
	char	*newline;
	size_t	len;

	newline = ft_strchr(buf, '\n');
	if (newline)
	{
		len = ft_strlen(newline + 1);
		line = ft_substr(buf, 0, newline - buf + 1);
		ft_memmove(buf, newline + 1, len);
		ft_bzero(buf + len, ft_strlen(buf) - len);
	}
	else
	{
		len = ft_strlen(buf);
		line = ft_substr(buf, 0, len);
		ft_bzero(buf, len);
	}
	return (line);
}
