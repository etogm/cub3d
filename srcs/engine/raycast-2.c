/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast-2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ljanette <ljanette@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/26 20:31:25 by ljanette          #+#    #+#             */
/*   Updated: 2020/10/03 15:48:46 by ljanette         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "mlx.h"

int			verticals(t_vars vars, t_point p, t_point m, t_point d, float cos_a, float sin_a)
{
	float	depth_v;
	int		i;

	p.x = cos_a >= 0 ? (m.x + TILE) : m.x;
	d.x = cos_a >= 0 ? 1 : -1;
	i = 0;
	while (i < vars.settings->r_x)
	{
		depth_v = (p.x - vars.player->pos->x) / cos_a;
		p.y = vars.player->pos->y + depth_v * sin_a;
		if (vars.settings->text_map[(int)p.y / TILE][((int)p.x + (int)d.x) / TILE] == '1')
			break ;
		p.x += d.x * TILE;
		i += TILE;
	}
	return (depth_v);
}

int			horizontals(t_vars vars, t_point p, t_point m, t_point d, float cos_a, float sin_a)
{
	float	depth_h;
	int		i;

	p.y = sin_a >= 0 ? (m.y + TILE) : m.y;
	d.y = sin_a >= 0 ? 1 : -1;
	i = 0;
	while (i < vars.settings->r_y)
	{
		depth_h = (p.y - vars.player->pos->y) / sin_a;
		p.x = vars.player->pos->x + depth_h * cos_a;
		printf("%f %f\n", (floor(p.y + d.y) / TILE), floor(p.x) / TILE);
		if (vars.settings->text_map[((int)p.y + (int)d.y) / TILE][(int)(p.x) / TILE] == '1')
			break ;
		p.y += d.y * TILE;
		i += TILE;
	}
	return (depth_h);
}

void		ray_cast(t_vars vars)
{
	t_point	m;
	float	cur_angle;
	int		ray;
	t_point	p;
	t_point d;
	float depth_v;
	float depth_h;
	int 	i;

	m.x = vars.player->pos->x;
	m.y = vars.player->pos->y;
	cur_angle = vars.player->angle - HALF_FOV;
	ray = 0;
	while (ray < NUM_RAYS)
	{
		float sin_a = sin(cur_angle);
		float cos_a = cos(cur_angle);
		depth_v = verticals(vars, p, m, d, cos_a, sin_a);
		depth_h = horizontals(vars, p, m, d, cos_a, sin_a);

		float depth = depth_v < depth_h ? depth_v : depth_h;
		depth *= cos(vars.player->angle - cur_angle);

		float proj_height = MIN((int)(PROJ_COEFF / depth), 2 * vars.settings->r_y);
		t_point		p_line;

		p_line.x = ray * SCALE;
		p_line.y = (vars.settings->r_y / 2) - (int)(proj_height / 2);
		draw_line(vars, p_line, proj_height, 1);
		ray++;
		cur_angle += DELTA_ANGLE;
	}
}
