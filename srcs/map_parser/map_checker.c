/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_checker.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ljanette <ljanette@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/27 13:05:57 by ljanette          #+#    #+#             */
/*   Updated: 2020/09/27 14:22:59 by ljanette         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static	int	map_checker_margin(char **map, int i)
{
	int		j;

	j = 0;
	if (map[i])
	{
		while (map[i][j])
			if (map[i][j++] != '1')
				return (0);
	}
	return (1);
}

static	int	map_checker_line(char **map, int i)
{

}

static  int map_checker_main(char **map, int *k)
{
	int		len;
	int		i;
	int		j;

	i = *k;
	j = 0;
	while (map[i])
	{
		if (map[i][0] != '1' || map[i][ft_strlen(map[i]) - 1] != '1')
			return (0);
		if ((len = ft_strlen(map[i - 1])) < ft_strlen(map[i]))
			while (map[i][len])
				if (map[i][len++] != '1')
					return (0);
		if (map[i + 1])
			if ((len = ft_strlen(map[i + 1])) < ft_strlen(map[i]))
				while (map[i][len])
					if (map[i][len++] != '1')
						return (0);
		i++;
	}
	*k = i;
	return (1);
}

int			map_checker(char **map)
{
	int		i;
	char	*map_line;

	i = 0;
	if (!(map_checker_margin(map, i)))
		return (0);
	i++;
	if (!(map_checker_main(map, &i)))
		return (0);
	i--;
	if (!(map_checker_margin(map, i)))
		return (0);
	return (1);
}
