/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ljanette <ljanette@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/06 16:50:10 by ljanette          #+#    #+#             */
/*   Updated: 2020/10/02 19:49:40 by ljanette         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "mlx.h"

int				wall_side(char **text_map, t_point pos)
{
	int			x;
	int			y;

	x = pos.x / SQUARE_SIZE;
	y = pos.y / SQUARE_SIZE;
	if (y * SQUARE_SIZE + SQUARE_SIZE - 1 == (int)pos.y)
		return (0xebffc0);
	else if (y * SQUARE_SIZE == (int)pos.y)
		return (0xb3e0ff);
	else if (x * SQUARE_SIZE == (int)pos.x)
		return (0x663399);
	else if (x * SQUARE_SIZE + SQUARE_SIZE == (int)pos.x + 1)
		return (0xf4e9e8);
	return (0);
}

int				wall_tex(t_vars vars, char **text_map, t_point pos)
{
	int			x;
	int			y;

	x = pos.x / SQUARE_SIZE;
	y = pos.y / SQUARE_SIZE;
	if (y * SQUARE_SIZE + SQUARE_SIZE - 1 == (int)pos.y)
		return (0xff7792);
	else if (y * SQUARE_SIZE == (int)pos.y)
		return (0xb3e0ff);
	else if (x * SQUARE_SIZE + SQUARE_SIZE == (int)pos.x + 1)
		return (0xf4e9e8);
	else if (x * SQUARE_SIZE == (int)pos.x)
		return (0x663399);
	return (0);
}

void			find_wall(t_vars vars, float cosa, float sina,
							int ray)
{
	float		depth;
	float		column_h;
	t_point		p2;
	t_point		p3;

	depth = 0;
	while (depth < MAX_DEPTH)
	{
		p2.x = vars.player->pos->x + depth * cosa;
		p2.y = vars.player->pos->y + depth * sina;
		if (vars.settings->text_map
		[(int)(p2.y / SQUARE_SIZE)][(int)(p2.x / SQUARE_SIZE)] == '1')
		{
			column_h = MAX((vars.settings->r_x / tan(HALF_FOV) * SQUARE_SIZE)
			/ (depth), 0.00001);
			p3.x = ray;
			p3.y = (vars.settings->r_y / 2) - (column_h / 2);
			draw_line(vars, p3, column_h, ray);
			break ;
		}
		depth += 0.1;
	}
}

void			ray_casting(t_vars vars, t_point pos, double angle)
{
	float		cur_angle;
	int			ray;

	ray = 0;
	cur_angle = angle - HALF_FOV;
	while (ray < vars.settings->r_x)
	{
		find_wall(vars, cos(cur_angle), sin(cur_angle), ray++);
		cur_angle += (FOV / vars.settings->r_x);
	}
}
