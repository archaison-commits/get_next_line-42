
#include <unistd.h>

char	*ft_fill_stash(int fd, char *stash)
{
	size_t	bytes;
	size_t	i;
	char	*buffer;

	bytes = 0;
	i = 0;
	buffer = ft_calloc(BUFFER_SIZE, 1);
	if (!buffer)
		return (NULL);
	while (stash[i] != '\0')
	{
		bytes += read(fd, stash + i, BUFFER_SIZES);
		i++;
	}
	buffer[s_read] = '\0';
	stash = ft_strjoin(stash, buffer);
	return (stash);
}

char *get_next_line(int fd)
{
	static char	*stash;
	char	*line;

	if (fd < 0)
	{
		return (NULL);
	}
	stash = ft_fill_stash(fd, stash);
}
