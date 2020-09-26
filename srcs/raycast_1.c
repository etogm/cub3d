/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ljanette <ljanette@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/06 16:50:10 by ljanette          #+#    #+#             */
/*   Updated: 2020/09/26 20:10:23 by ljanette         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "mlx.h"

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
		color = get_texture_color(vars.img, p3);
		//color = *(vars.img.img_data + 4 * y * vars.img.width + 4 * x);
		//color = *(vars.img.img_data + (y * vars.img.size_line) / proj_height + (x * (vars.img.bpp / 8)) / proj_height);
		//color = 0xFFFFFF;
		mlx_pixel_put(vars.mlx, vars.win, x, y, color);
		y++;
	}
}

void			find_wall(t_vars vars, double cosa, double sina, int ray, double cur_angle)
{
	int			depth;
	int			proj_height;
	t_point		p2;
	t_point		p3;
	t_point		p4;
	int			offset;

	depth = 1;
	while (depth < MAX_DEPTH)
	{
		p2.x = vars.player->pos->x + depth * cosa;
		p2.y = vars.player->pos->y + depth * sina;
		if (vars.settings->text_map[(int)p2.y / SQUARE_SIZE][(int)p2.x / SQUARE_SIZE] == '1')
		{
			offset = depth % SQUARE_SIZE;
			proj_height = PROJ_COEFF / (depth * cos(vars.player->angle - cur_angle));
			p3.x = ray * SCALE;
			p3.y = (vars.settings->r_y / 2) - (proj_height / 2);
			p4.x = SCALE;
			p4.y = proj_height;
			draw_line(vars, p3, p4);
			break;
		}
		depth++;
	}
}

void			ray_casting(t_vars vars, t_point pos, double angle)
{
	double		cur_angle;
	int			ray;
	int			depth;
	int			proj_height;
	t_point		p2;

	cur_angle = angle - HALF_FOV;
	ray = 0;
	while (ray < NUM_RAYS)
	{
		find_wall(vars, cos(cur_angle), sin(cur_angle), ray++, cur_angle);
		cur_angle += DELTA_ANGLE;
	}
}
