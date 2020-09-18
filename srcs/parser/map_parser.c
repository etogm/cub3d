/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_parser.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ljanette <ljanette@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/02 05:29:20 by ljanette          #+#    #+#             */
/*   Updated: 2020/08/06 16:32:13 by ljanette         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fcntl.h>
#include "libft.h"
#include "get_next_line.h"
#include "cub3d.h"

int			map_check_line(char *line)
{
	
}

int			map_add_line(char **map, char *line)
{
	char	*tmp;

	tmp = *map;
	if (!(*map = ft_strjoin(*map, line)))
		return (0);
	if (!(*map = ft_strjoin(*map, "\n")))
		return (0);
	return (1);
}

char		**map_parser(int fd)
{
	char	*map;
	char	*line;
	char	**map_arr;

	line = NULL;
	map = ft_strdup("");
	while (get_next_line(fd, &line) > 0)
	{
		if (*line != '\0')
			map_add_line(&map, line);
		free(line);
	}
	map_arr = ft_split(map, '\n');
	free(map);
	return (map_arr);
}
/*
int			*map_get(int fd)
{
	char	*line;
	int		map_arr[100][2];
	int		i;
	int		j;
	int		k;

	line = NULL;
	i = 0;
	k = 0;
	while (get_next_line(fd, &line) > 0)
	{
		if (*line != '\0')
		{
			j = 0;
			while (line[j])
			{
				if (line[j] == '1')
				{
					map_arr[k][0] = i;
					map_arr[k][1] = j;
					k++;
				}
				j++;
			}
			i++;
		}
		free(line);
	}
	return (map_arr);
}*/