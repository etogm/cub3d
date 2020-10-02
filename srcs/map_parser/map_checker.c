/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_checker.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ljanette <ljanette@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/27 13:05:57 by ljanette          #+#    #+#             */
/*   Updated: 2020/10/02 18:53:04 by ljanette         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "cub3d.h"

int			map_checker_margin(char **map, int i)
{
	int		j;

	j = 0;
	while (map[i][j] == ' ')
		j++;
	while (map[i][j])
	{
		if (map[i][j] != '1')
			return (0);
		j++;
	}
	return (1);
}

int			map_checker_empty(char **map, int i, int j)
{
	if (0 < i - 1)
	{
		if (map[i - 1][j - 1] != '1' && map[i - 1][j - 1] != ' ')
			return (0);
		if (map[i - 1][j] != '1' && map[i - 1][j] != ' ')
			return (0);
		if (map[i - 1][j + 1] != '1' && map[i - 1][j + 1] != ' ')
			return (0);
	}
	if (map[i + 1])
	{
		if (map[i + 1][j] != '1' && map[i + 1][j] != ' ')
			return (0);
		if (map[i + 1][j + 1] != '1' && map[i + 1][j + 1] != ' ')
			return (0);
		if (map[i + 1][j - 1] != '1' && map[i + 1][j - 1] != ' ')
			return (0);
	}
	if (map[i][j + 1] != '1' && map[i][j + 1] != ' ')
		return (0);
	if (map[i][j - 1] != '1' && map[i][j - 1] != ' ')
		return (0);
	return (1);
}

int			map_checker_line(char **map, int i)
{
	int		j;

	j = 0;
	while (map[i][j] == ' ')
		j++;
	if (map[i][j++] != '1')
		return (0);
	while (map[i][j])
	{
		if (!is_map_char(map[i][j]))
		{
			if (map[i][j] == ' ')
			{
				if (!map_checker_empty(map, i, j))
					return (0);
			}
			else
				return (0);
		}
		j++;
	}
	if (map[i][--j] != '1')
		return (0);
	return (1);
}

int			map_checker_main(char **map, int *k)
{
	int		i;

	i = *k;
	while (map[i])
	{
		if (!(map_checker_line(map, i++)))
			return (0);
	}
	*k = i;
	return (1);
}

int			map_checker(char **map)
{
	int		flag_player;
	int		i;
	char	*map_line;

	flag_player = 0;
	i = 0;
	/*if (!(map_checker_margin(map, i)))
		return (0);
	i++;*/
	if (!(map_checker_main(map, &i)))
		return (0);
	/*i--;
	if (!(map_checker_margin(map, i)))
		return (0);*/
	return (1);
}
