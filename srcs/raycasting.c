/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ljanette <ljanette@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/06 16:50:10 by ljanette          #+#    #+#             */
/*   Updated: 2020/09/18 17:13:57 by ljanette         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "mlx.h"

void			ray_casting(t_vars vars, t_point pos, double angle, int color)
{
	double		cur_angle;
	int			ray;
	int			depth;
	t_point		p2;

	cur_angle = angle - HALF_FOV;
	ray = 0;
	while (ray < NUM_RAYS)
	{
		depth = 1;
		double cosa = cos(cur_angle);
		double sina = sin(cur_angle);
		while (depth < MAX_DEPTH)
		{
			p2.x = pos.x + depth * cosa;
			p2.y = pos.y + depth * sina;
			//brezenhem(vars, pos.x, pos.y, p2.x, p2.y, color);
			depth++;
			if (vars.settings->text_map[p2.y / SQUARE_SIZE][p2.x / SQUARE_SIZE] == '1')
			{
				t_point p3;
				t_point p4;
				int		proj_height;

				proj_height = PROJ_COEFF / (depth * cos(angle - cur_angle));
				p3.x = ray * SCALE;
				p3.y = (vars.settings->r_y / 2) - (proj_height / 2);
				p4.x = SCALE;
				p4.y = proj_height;
				draw_square(vars, p3, p4, color);
				break;
			}
		}
		ray++;
		cur_angle += DELTA_ANGLE;
	}
}
