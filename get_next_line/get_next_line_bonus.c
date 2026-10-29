/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lucaroma <lucaroma@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/22 08:16:45 by lucaroma          #+#    #+#             */
/*   Updated: 2026/10/27 15:49:46 by lucaroma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

static char	*ft_read_line(int fd, char *storage)
{
	int		x;
	char	*block;
	char	*tmp;

	block = malloc(BUFFER_SIZE + 1);
	if (!block)
		return (free(storage), NULL);
	x = 1;
	while ((!storage || !ft_strchr(storage, '\n')) && x > 0)
	{
		x = read(fd, block, BUFFER_SIZE);
		if (x == -1)
			return (free(block), free(storage), NULL);
		if (x == 0)
			break ;
		block[x] = '\0';
		if (!storage)
			storage = ft_strdup ("");
		tmp = storage;
		storage = ft_strjoin(storage, block);
		free(tmp);
		if (!storage)
			return (free(block), NULL);
	}
	return (free(block), storage);
}
/*static char	*ft_read_line(int fd, char	*storage)
{
	int		x;
	char	*block;
	char	*tmp;

	block = malloc(BUFFER_SIZE + 1);
	if (!block)
	{
		free(storage);
		return (NULL);
	}
	x = 1;
	while ((!storage || !ft_strchr(storage, '\n')) && x > 0)
	{
		x = read(fd, block, BUFFER_SIZE);
		if (x == -1)
		{
			free(block);
			free(storage);
			return (NULL);
		}
		if (x == 0)
			break ;
		block[x] = '\0';
		if (!storage)
			storage = ft_strdup("");
		tmp = storage;
		storage = ft_strjoin(tmp, block);
		free(tmp);
	}
	return (storage);
}*/

static char	*ft_get_line(char *storage)
{
	int	i;

	i = 0;
	if (!storage || !*storage)
		return (NULL);
	while (storage[i] && storage[i] != '\n')
		i++;
	if (storage[i] == '\n')
		i++;
	return (ft_substr(storage, 0, i));
}

static char	*clean(char *storage)
{
	int		i;
	char	*new_storage;

	i = 0;
	while (storage[i] && storage[i] != '\n')
		i++;
	if (storage[i] == '\0')
	{
		free(storage);
		return (NULL);
	}
	new_storage = ft_substr(storage, i + 1, ft_strlen(storage) - i);
	free(storage);
	return (new_storage);
}

char	*get_next_line(int fd)
{
	static char	*storage[1024];
	char		*line;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	storage[fd] = ft_read_line(fd, storage[fd]);
	if (!storage[fd])
		return (NULL);
	line = ft_get_line(storage[fd]);
	if (!line)
	{
		free(storage[fd]);
		storage[fd] = NULL;
		return (NULL);
	}
	storage[fd] = clean(storage[fd]);
	return (line);
}
