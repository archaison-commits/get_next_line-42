
#include "get_next_line.h"

size_t	ft_strlen(const char *s)
{
	size_t	i;

	i = 0;
	while (*s)
	{
		s++;
		i++;
	}
	return (i);
}

char	*ft_strchr(const char *s, int c)
{
	while (*s)
	{
		if (*s == (char )c)
			break ;
		s++;
	}
	if (*s == (char )c)
		return ((char *)s);
	return (NULL);
}

void	*ft_calloc(size_t nmemb, size_t size)
{
	void			*res;
	unsigned char	*ptr;
	size_t			i;

	i = 0;
	if (size != 0 && nmemb > ((size_t)-1) / size)
	{
		ptr = NULL;
		return (ptr);
	}
	res = malloc(nmemb * size);
	if (!res)
		return (NULL);
	ptr = (unsigned char *)res;
	while (i < (nmemb * size))
		ptr[i++] = 0;
	return (res);
}

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*new_s;
	size_t	len;
	size_t	i;
	size_t	j;

	if (!s1 || !s2)
		return (NULL);
	len = ft_strlen(s1) + ft_strlen(s2);
	new_s = malloc(len + 1);
	if (!new_s)
		return (NULL);
	i = 0;
	while (s1[i] != '\0')
	{
		new_s[i] = s1[i];
		i++;
	}
	j = 0;
	while (s2[j] != '\0')
	{
		new_s[i + j] = s2[j];
		j++;
	}
	new_s[i + j] = '\0';
	return (new_s);
}
