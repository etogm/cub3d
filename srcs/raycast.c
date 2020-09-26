/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ljanette <ljanette@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/26 20:31:25 by ljanette          #+#    #+#             */
/*   Updated: 2020/09/26 21:12:44 by ljanette         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "mlx.h"

t_point			*mapping(t_point pos)
{
	t_point     *m;

	m = (t_point*)malloc(sizeof(t_point));
	m->x = (pos.x / SQUARE_SIZE) * SQUARE_SIZE;
	m->y = (pos.y / SQUARE_SIZE) * SQUARE_SIZE;
	return (m);
}

int				get_texture_color (t_img img, t_point pos)
{
    int			offset;
    int			a;
    int			r;
    int			g;
    int			b;

    offset = pos.y * img.size_line
    + pos.x * (img.bpp / 8);
    a = img.img_data[offset + 0];
    r = img.img_data[offset + 1];
    g = img.img_data[offset + 2];
    b = img.img_data[offset + 3];
    return (b << 24 | g << 16 | r << 8 | a);
}

void			draw_line(t_vars vars, t_point p1, t_point p2)
{
	int			x;
	int			y;
	int			color;
	t_point		p3;

	y = p1.y; 
	while (y < p2.y)
	{
		x = p1.x;
		p3.y = (vars.img.height * (y % (int)255)) / 255;
		p3.x = x % 255;
		//color = get_texture_color(vars.img, p3);
		color = *(vars.img.img_data + 4 * y * vars.img.width + 4 * x);
		//color = *(vars.img.img_data + (y * vars.img.size_line) / proj_height + (x * (vars.img.bpp / 8)) / proj_height);
		//color = 0xFFFFFF;
		mlx_pixel_put(vars.mlx, vars.win, x, y, color);
		y++;
	}
}

void			find_wall(t_vars vars, double cosa, double sina, int ray, t_point m)
{
	int			x;
	int			y;
	int			dx;
	int			dy;
	int			i;
	int			depth_v;
	int			depth_h;

	int			depth;
	int			proj_height;
	t_point		p2;
	t_point		p3;
	t_point		p4;
	int			offset;

	if (cos >= 0)
	{
		x = m.x + SQUARE_SIZE;
		dx = 1;
	}
	else
	{
		x = m.x;
		dx = -1;
	}
	i = 0;
	while (i < vars.settings->r_x)
	{
		depth_v = (x - vars.player->pos->x) / cosa;
		y = vars.player->pos->x + depth_v * sina;
		printf("%d %d\n", y, x + dx);
		if (vars.settings->text_map[y][x + dx] == '1')
			break;
		x += dx * SQUARE_SIZE;
	}
	if (sina >= 0)
	{
		y = m.y + SQUARE_SIZE;
		dy = 1;
	}
	else
	{
		y = m.y;
		dy = -1;
	}

	printf("test2\n");
	i = 0;
	while (i < vars.settings->r_y)
	{
		depth_h = (x - vars.player->pos->y) / sina;
		x = vars.player->pos->x + depth_h * cosa;
		if (vars.settings->text_map[y + dy][x] == '1')
			break;
		y += dy + SQUARE_SIZE;
	}
	depth = (depth_v < depth_h) ? depth_v : depth_h;
	//proj_height = PROJ_COEFF / (depth * cos(vars.player->angle - cur_angle));
	proj_height = PROJ_COEFF / depth;
	p3.x = ray * SCALE;
	p3.y = (vars.settings->r_y / 2) - (proj_height / 2);
	p4.x = SCALE;
	p4.y = proj_height;
	draw_line(vars, p3, p4);
}

void			ray_casting(t_vars vars, t_point player_pos, double player_angle)
{
	t_point		*m;
	double		cur_angle;
	int			ray;

	m = mapping(player_pos);
	cur_angle = player_angle - HALF_FOV;
	ray = 0;
	while (ray < NUM_RAYS)
	{
		find_wall(vars, cos(cur_angle), sin(cur_angle), ray++, *m);
		cur_angle += DELTA_ANGLE;
	}
}