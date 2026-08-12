/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/23 23:19:09 by brechied          #+#    #+#             */
/*   Updated: 2026/08/12 04:18:25 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*ft_leftovers(char *stash)
{
	size_t	i;
	size_t	j;
	char	*new_stash;

	i = 0;
	while (stash[i] && stash[i] != '\n')
		i++;
	if (!stash[i])
	{
		free(stash);
		return (NULL);
	}
	new_stash = ft_calloc((ft_strlen(stash) - i), 1);
	if (!new_stash)
	{
		free(stash);
		return (NULL);
	}
	j = 0;
	while (stash[++i])
		new_stash[j++] = stash[i];
	new_stash[j] = '\0';
	free(stash);
	return (new_stash);
}

char	*ft_first_line(char *stash)
{
	size_t	i;
	char	*line;

	i = 0;
	if (!stash[i])
		return (NULL);
	while (stash[i] && stash[i] != '\n')
		i++;
	line = ft_calloc(i + 2, 1);
	if (!line)
		return (NULL);
	i = 0;
	while (stash[i] && stash[i] != '\n')
	{
		line[i] = stash[i];
		i++;
	}
	if (stash[i] && stash[i] == '\n')
		line[i] = '\n';
	line[++i] = '\0';
	return (line);
}

char	*ft_append(char *stash, char *buffer
		, size_t *len, size_t *capacity)
{
	char	*tmp;
	size_t	i;
	size_t	b_len;

	b_len = ft_strlen(buffer);
	i = 0;
	if (*len + b_len+ 1 > *capacity)
	{
		while (*len + b_len + 1 > *capacity)
			*capacity *= 2;
		tmp = malloc(*capacity);
		if (!tmp)
			return (NULL);
		while (stash[i])
		{
			tmp[i] = stash[i];
			i++;
		}
		free(stash);
		stash = tmp;
	}
	i = 0;
	while (i < b_len)
		stash[(*len)++] = buffer[i++];
	stash[*len] = '\0';
	return (stash);
}

char	*ft_check_stash(char *stash, size_t *len, size_t *capacity)
{
	char	*tmp;

	if (!stash)
		stash = ft_calloc(1,1);
	if (!stash)
		return (NULL);
	*len = ft_strlen(stash);
	*capacity = *len + BUFFER_SIZE + 1;
	tmp = ft_expand_stash(stash, *len, *capacity);
	if (!tmp)
		return(free(stash), NULL);
	return (tmp);
}

char	*ft_fill_stash(int fd, char *stash)
{
	ssize_t	bytes;
	size_t	len;
	size_t	capacity;
	char	*buffer;

	stash = ft_check_stash(stash, &len, &capacity);
	if (!stash)
		return (NULL);
	buffer = ft_calloc(BUFFER_SIZE + 1, 1);
	if (!buffer)
		return (free(stash), NULL);
	bytes = 1;
	while (bytes > 0)
	{
		bytes = read(fd, buffer, BUFFER_SIZE);
		if (bytes == -1)
			return (free(buffer), free(stash), NULL);
		buffer[bytes] = 0;
		stash = ft_append(stash, buffer, &len, &capacity);
		if (!stash || ft_strchr(buffer, '\n'))
			break ;
	}
	free(buffer);
	return (stash);
}

char	*get_next_line(int fd)
{
	static char	*stash;
	char		*line;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	stash = ft_fill_stash(fd, stash);
	if (!stash)
		return (NULL);
	line = ft_first_line(stash);
	stash = ft_leftovers(stash);
	return (line);
}
/*
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include "get_next_line.h"

int	main(void)
{
	int		fd;
	char	*line;

	fd = open("test.txt", O_RDONLY);
	if (fd == -1)
		return (1);

	while ((line = get_next_line(fd)) != NULL)
	{
		printf("LINE: [%s]\n", line);
		free(line);
	}

	close(fd);
	return (0);
}
*/
