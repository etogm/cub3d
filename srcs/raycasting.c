/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ljanette <ljanette@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/06 16:50:10 by ljanette          #+#    #+#             */
/*   Updated: 2020/09/25 15:23:29 by ljanette         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "mlx.h"

void		draw_line(t_vars vars, t_point p1, t_point p2)
{
	int		x;
	int		y;
	int		color;

	y = p1.y;
	while (y < p2.y)
	{
		x = p1.x;
		color = *(vars.img.img_data + 4 * p1.y * vars.img.width + 4 * p1.x);
		mlx_pixel_put(vars.mlx, vars.win, x, y, color);
		y++;
	}
}


void			ray_casting(t_vars vars, t_point pos, double angle)
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
				draw_line(vars, p3, p4);
				break;
			}
			depth++;
		}
		ray++;
		cur_angle += DELTA_ANGLE;
	}
}
