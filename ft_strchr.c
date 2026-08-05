/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brechied <brechied@student.42warsaw.pl>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/17 22:50:05 by brechied          #+#    #+#             */
/*   Updated: 2026/06/22 16:46:40 by brechied         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

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
/*
int	main(void)
{
	char *s;
	char c;

	s = "Send help";
	c = 'e';
	printf("original Function:%s\n", strchr(s, c));
	printf("mimic:%s\n", ft_strchr(s, c));
	return (0);
}*/
