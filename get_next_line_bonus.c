/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/23 23:19:09 by brechied          #+#    #+#             */
/*   Updated: 2026/08/12 04:49:25 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

char	*leftovers(char *stash)
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

char	*first_line(char *stash)
{
	size_t	i;
	char	*line;

	i = 0;
	if (!stash[i])
		return (NULL);
	while (stash[i] && stash[i] != '\n')
		i++;
	line = ft_calloc(i + 2, 1);
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

char	*strjoin_free(char *stash, char *buffer, ssize_t bytes, size_t len)
{
	char	*tmp;

	tmp = ft_strjoin(stash, buffer, bytes, len);
	free(stash);
	return (tmp);
}

char	*fill_stash(int fd, char *stash)
{
	ssize_t	bytes;
	size_t	len;
	char	*buffer;

	bytes = 1;
	if (!stash)
	{
		stash = ft_calloc(1, 1);
		if (!stash)
			return (NULL);
	}
	buffer = ft_calloc(BUFFER_SIZE + 1, 1);
	len = ft_strlen(stash);
	if (!buffer)
		return (free(stash), NULL);
	while (bytes > 0)
	{
		bytes = read(fd, buffer, BUFFER_SIZE);
		if (bytes == -1)
			return (free(buffer), free(stash), NULL);
		buffer[bytes] = '\0';
		stash = strjoin_free(stash, buffer, bytes, len);
		len += bytes;
		if (!stash || ft_strchr(buffer, '\n'))
			break ;
	}
	free(buffer);
	return (stash);
}

char	*get_next_line(int fd)
{
	static char	*stash[FD_MAX];
	char		*line;

	if (fd < 0 || fd >= FD_MAX || BUFFER_SIZE <= 0)
		return (NULL);
	stash[fd] = fill_stash(fd, stash[fd]);
	if (!stash[fd])
		return (NULL);
	line = first_line(stash[fd]);
	stash[fd] = leftovers(stash[fd]);
	return (line);
}
/*
#include <stdio.h>
int	main(void)
{
	int	fd[FD_MAX];
    char    *s;

    s = "SEND\nHELP";
	fd = open("test.txt"), 0_RDONLY);
	if (fd == -1)
		return (1);
	//fd = open("test.txt", O_RDWR | O_CREAT, 0777);

	while (s = get_next_line(fd) != NULL)
	{
		printf("LINE: [%s]\n", s);
		free(s);
	}
	close(fd);
	return (0);
}
*/
