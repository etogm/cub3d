/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ljanette <ljanette@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/06 16:50:10 by ljanette          #+#    #+#             */
/*   Updated: 2020/09/30 19:07:26 by ljanette         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "mlx.h"

t_raycast		*raycast_init(t_vars vars)
{
	t_raycast	*raycast_settings;

	raycast_settings->num_rays = vars.settings->r_x;
	raycast_settings->delta_angle = FOV / raycast_settings->num_rays;
	raycast_settings->dist = raycast_settings->num_rays / (2 * tan(HALF_FOV));
	raycast_settings->proj_coeff = raycast_settings->dist * SQUARE_SIZE;
	return (raycast_settings);
}



int				get_texture_color (t_img img, t_point pos)
{
    int			offset;
    int			a;
    int			r;
    int			g;
    int			b;

    offset = pos.y * img.size_line + pos.x * (img.bpp / 8);
    a = img.img_data[offset + 0];
    r = img.img_data[offset + 1];
    g = img.img_data[offset + 2];
    b = img.img_data[offset + 3];
    return (b << 24 | g << 16 | r << 8 | a);
}

void			draw_line(t_vars vars, t_point p1, int column_h, unsigned int c)
{
	while (p1.y < column_h)
		mlx_pixel_put(vars.mlx, vars.win, p1.x, p1.y++, c);
}

int				wall_side(char **text_map, t_point pos)
{
	int			x;
	int			y;

	x = pos.x / SQUARE_SIZE;
	y = pos.y / SQUARE_SIZE;
	printf("%d %f\n", y, pos.y);
	if (y * SQUARE_SIZE + SQUARE_SIZE - 1 == (int)pos.y) //north
		return (0xebffc0);
	else if (y * SQUARE_SIZE == (int)pos.y) //south
		return (0xb3e0ff);
	else if (x * SQUARE_SIZE == (int)pos.x) //east
		return (0x663399);
	else if (x * SQUARE_SIZE + SQUARE_SIZE == (int)pos.x + 1) //west
		return (0xf4e9e8);
	return (0);
}

int				wall_tex(t_vars vars, char **text_map, t_point pos)
{
	int			x;
	int			y;

	x = pos.x / SQUARE_SIZE;
	y = pos.y / SQUARE_SIZE;
	printf("%d %f\n", y, pos.y);
	if (y * SQUARE_SIZE + SQUARE_SIZE - 1 == (int)pos.y) //north
		return (0xff7792);
	else if (y * SQUARE_SIZE == (int)pos.y) //south
		return (0xb3e0ff);
	else if (x * SQUARE_SIZE + SQUARE_SIZE == (int)pos.x + 1) //west
		return (0xf4e9e8);
	else if (x * SQUARE_SIZE == (int)pos.x) //east
		return (0x663399);
	return (0);
}

void			find_wall(t_vars vars, float cosa, float sina, int ray, float cur_angle)
{
	float		depth;
	float		proj_height;
	t_point		p2;
	t_point		p3;
	int			offset;

	depth = 0;
	while (1)
	{
		p2.x = vars.player->pos->x + depth * cosa;
		p2.y = vars.player->pos->y + depth * sina;
		if (vars.settings->text_map[(int)(p2.y / SQUARE_SIZE)][(int)(p2.x / SQUARE_SIZE)] == '1')
		{
			//printf("x: %f\ty: %f\n", p2.x, p2.y);
			proj_height = MAX(PROJ_COEFF / (depth * cos(vars.player->angle - cur_angle)), 0.00001);
			//proj_height = vars.settings->r_y / depth;
			p3.x = ray;
			p3.y = (vars.settings->r_y / 2) - (proj_height / 2);
			draw_line(vars, p3, proj_height, wall_tex(vars, vars.settings->text_map, p2));
			break;
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
	while (ray < NUM_RAYS)
	{
		find_wall(vars, cos(cur_angle), sin(cur_angle), ray++, cur_angle);
		cur_angle += DELTA_ANGLE;
	}
}
