/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brechied <brechied@student.42warsaw.pl>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/23 23:19:09 by brechied          #+#    #+#             */
/*   Updated: 2026/07/23 23:19:11 by brechied         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fcntl.h>
#include <unistd.h>

char	*ft_leftovers(char *stash)
{
	size_t	i;
	size_t	j;
	char	*new_stash;

	i = 0;
	while (stash[i] && stash[i] != '\n')
		i++;
	if (stash[i] != '\n')
	{
		free(stash);
		return (NULL);
	}
	new_stash = malloc(ft_strlen(stash) - i);
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
	while (stash[i] && stash[i] != '\n')
		i++;
	line = malloc(i + 2);
	if (!line)
		return (NULL);
	i = 0;
	while (stash[i] && stash[i] != '\n')
	{
		line[i] = stash[i];
		i++;
	}
	if (stash[i] == '\n')
		line[i] = '\n';
	line[++i] = '\0';
	return (line);
}

char	*ft_strjoin_free(char *stash, char *buffer)
{
	char	*tmp;

	tmp = ft_strjoin(stash, buffer);
	if (!tmp)
	{
		free(stash);
		return (NULL);
	}
	free(stash);
	return (tmp);
}

char	*ft_fill_stash(int fd, char *stash)
{
	ssize_t	bytes;
	char	*buffer;

	bytes = 1;
	if (!stash)
		stash = ft_calloc(1, 1);
	buffer = malloc(BUFFER_SIZE + 1);
	if (!buffer)
		return (NULL);
	while (bytes > 0)
	{
		bytes = read(fd, buffer, BUFFER_SIZE);
		if (bytes == -1)
		{
			free(stash);
			free(buffer);
			return (NULL);
		}
		buffer[bytes] = 0;
		stash = ft_strjoin_free(stash, buffer);
		if (ft_strchr(stash, '\n'))
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
int	main(void)
{
	int		fd;
	char	buf[256];

	int char_
}*/
