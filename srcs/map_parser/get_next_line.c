/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ljanette <ljanette@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/17 11:33:15 by ljanette          #+#    #+#             */
/*   Updated: 2020/07/22 01:13:03 by ljanette         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

int					ft_strjoin_free(char **str, char *join1,
									char *join2)
{
	char *last_line;

	last_line = *str;
	if (*join2 != '\0')
	{
		if (!(*str = ft_strjoin(join1, join2)))
		{
			free(last_line);
			return (0);
		}
		free(last_line);
	}
	return (1);
}

int					check_back(char **ptr_n, char **line, char *back)
{
	if (back)
	{
		if ((*ptr_n = ft_strchr(back, '\n')))
		{
			**ptr_n = '\0';
			if (!(*line = ft_strjoin(back, "")))
				return (0);
			ft_strcpy(back, ++*ptr_n);
		}
		else
		{
			if (!(*line = ft_strjoin(back, "")))
				return (0);
			ft_strclr(back);
		}
	}
	else
	{
		if (!(*line = ft_strjoin("", "")))
			return (0);
	}
	return (1);
}

int					cleaner(int flag, char **buf, char **back)
{
	free(*buf);
	if (flag == 0)
	{
		if (*back)
		{
			free(*back);
			*back = NULL;
		}
	}
	return (flag);
}

int					get_next_line(int fd, char **line)
{
	char			*buf;
	char			*ptr_n;
	int				buf_end;
	static	char	*back = NULL;

	ptr_n = NULL;
	if (!line || BUFFER_SIZE < 1)
		return (-1);
	if (!check_back(&ptr_n, line, back) || read(fd, NULL, 0) < 0 || fd < 0)
		return (-1);
	if (!(buf = (char*)malloc((BUFFER_SIZE + 1) * sizeof(char))))
		return (-1);
	while (!ptr_n && (buf_end = read(fd, buf, BUFFER_SIZE)))
	{
		buf[buf_end] = '\0';
		if ((ptr_n = ft_strchr(buf, '\n')))
		{
			*ptr_n = '\0';
			if (!ft_strjoin_free(&back, "", ++ptr_n))
				return (-1);
		}
		if (!ft_strjoin_free(line, *line, buf))
			return (-1);
	}
	return (cleaner(buf_end || ptr_n ? 1 : 0, &buf, &back));
}
