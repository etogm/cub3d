/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_parser.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ljanette <ljanette@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/02 05:29:20 by ljanette          #+#    #+#             */
/*   Updated: 2020/09/27 13:07:59 by ljanette         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fcntl.h>
#include "libft.h"
#include "get_next_line.h"
#include "cub3d.h"

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
	if (!map_checker(map_arr))
		return (NULL);
	return (map_arr);
}
