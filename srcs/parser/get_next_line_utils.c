/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ljanette <ljanette@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/17 13:12:30 by ljanette          #+#    #+#             */
/*   Updated: 2020/07/20 22:58:42 by ljanette         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

size_t		ft_strlen(const char *s)
{
	size_t	i;

	i = 0;
	while (s[i])
		i++;
	return (i);
}

char		*ft_strjoin(char const *s1, char const *s2)
{
	char	*output;
	int		i;

	if (!(output = (char*)malloc((ft_strlen(s1) + ft_strlen(s2) + 1)
	* sizeof(char))))
		return (0);
	i = 0;
	while (*s1)
		output[i++] = *s1++;
	while (*s2)
		output[i++] = *s2++;
	output[i] = '\0';
	return (output);
}

char		*ft_strchr(const char *s, int c)
{
	while (*s != c)
		if (*s++ == '\0')
			return (0);
	return ((char*)s);
}

void		ft_strclr(char *s)
{
	if (s)
		while (*s)
			*s++ = '\0';
}

char		*ft_strcpy(char *dest, char *src)
{
	int		i;

	i = 0;
	while (src[i] != '\0')
	{
		dest[i] = src[i];
		i++;
	}
	dest[i] = '\0';
	return (dest);
}
