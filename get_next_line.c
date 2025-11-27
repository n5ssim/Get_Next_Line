/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: n5ssim <nchouaf@student.s19.be>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/26 16:02:10 by n5ssim            #+#    #+#             */
/*   Updated: 2025/11/27 16:58:48 by n5ssim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static char	*_extract_line(char *storage)
{
	char	*line;
	size_t	i;

	i = 0;
	if (!storage[0])
		return (NULL);
	while (storage[i] && storage[i] != '\n')
		i++;
	line = malloc(i + 2);
	if (!line)
		return (NULL);
	i = 0;
	while (storage[i] && storage[i] != '\n')
	{
		line [i] = storage[i];
		i++;
	}
	if (storage[i] == '\n')
		line[i++] = '\n';
	line[i] = '\0';
	return (line);
}

static char	*_update_storage(char *storage)
{
	char	*new_storage;
	size_t	i;
	size_t	j;

	i = 0;
	while (storage[i] && storage[i] != '\n')
		i++;
	if (!storage[i])
	{
		free(storage);
		return (NULL);
	}
	new_storage = malloc(ft_strlen(storage) - i + 1);
	if (!new_storage)
		return (NULL);
	i++;
	j = 0;
	while (storage[i])
		new_storage[j++] = storage[i++];
	new_storage[j] = '\0';
	free(storage);
	return (new_storage);
}

static char	*read_and_store(int fd, char *storage)
{
	char	*buffer;
	int		byread;

	buffer = malloc(BUFFER_SIZE + 1);
	if (!buffer)
		return (NULL);
	byread = 1;
	while (byread > 0 && !ft_strchr(storage, '\n'))
	{
		byread = read(fd, buffer, BUFFER_SIZE);
		if (byread == -1)
		{
			free(buffer);
			free(storage);
			return (NULL);
		}
		buffer[byread] = '\0';
		storage = ft_strjoin(storage, buffer);
	}
	free(buffer);
	return (storage);
}

char	*get_next_line(int fd)
{
	static char	*storage;
	char		*line;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	storage = read_and_store(fd, storage);
	if (!storage)
		return (NULL);
	line = _extract_line(storage);
	storage = _update_storage(storage);
	return (line);
}
