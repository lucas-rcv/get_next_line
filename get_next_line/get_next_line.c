/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lucaroma <lucaroma@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/22 08:16:45 by lucaroma          #+#    #+#             */
/*   Updated: 2026/10/29 08:38:44 by lucaroma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

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
	char	block[BUFFER_SIZE + 1];
	char	*tmp;

	x = 1;
	while ((!storage || !ft_strchr(storage, '\n')) && x > 0)
	{
		x = read(fd, block, BUFFER_SIZE);
		if (x == -1)
		{
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
	static char	*storage;
	char		*line;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	storage = ft_read_line(fd, storage);
	if (!storage)
		return (NULL);
	line = ft_get_line(storage);
	if (!line)
	{
		free(storage);
		storage = NULL;
		return (NULL);
	}
	storage = clean(storage);
	return (line);
}
/*char	*get_next_line(int fd)
{
	static char	*storage;
	char		*line;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	storage = ft_read_line(fd, storage);
	if (!storage)
		return (NULL);
	line = ft_get_line(storage);
	storage = clean(storage);
	return (line);
}*/
