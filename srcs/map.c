/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ljanette <ljanette@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/05 23:53:18 by ljanette          #+#    #+#             */
/*   Updated: 2020/09/19 12:16:32 by ljanette         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mlx.h"
#include "cub3d.h"

void		map_draw(t_vars vars, char **text_map)
{
	int		i;
	int		j;
	t_point	pt1;
	t_point pt2;

	i = 0;
	while (text_map[i])
	{
		j = 0;
		while (text_map[i][j])
		{
			if (text_map[i][j] == '1')
			{
				pt1.x = j * SQUARE_SIZE;
				pt1.y = i * SQUARE_SIZE;
				pt2.x = pt1.x + SQUARE_SIZE;
				pt2.y = pt1.y + SQUARE_SIZE;
				draw_square(vars, pt1, pt2, 0xFFD700);
			}
			j++;
		}
		i++;
	}
}	
