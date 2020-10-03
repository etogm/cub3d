/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ljanette <ljanette@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/29 20:02:26 by ljanette          #+#    #+#             */
/*   Updated: 2020/10/03 17:12:46 by ljanette         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mlx.h"
#include "cub3d.h"

int				get_texture_color(t_img img, t_point pos)
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

void			draw_back(t_vars vars)
{
	int			i;
	int			j;

	i = 0;
	while (i < vars.settings->r_y / 3)
	{
		j = 0;
		while (j < vars.settings->r_x)
			mlx_pixel_put(vars.mlx, vars.win, j++, i, vars.settings->clr_floor);
		i++;
	}
	while (i < vars.settings->r_y)
	{
		j = 0;
		while (j < vars.settings->r_x)
			mlx_pixel_put(vars.mlx, vars.win, j++, i,
			vars.settings->clr_ceiling);
		i++;
	}
}
/*
void			draw_line(t_vars vars, t_point p1, int column_h, int x)
{
	int			y;
	t_point		hit;

	y = 0;
	//hit.x = x % SQUARE_SIZE * TEX_SCALE;
	while (p1.y < column_h)
	{
		//hit.y = (y++ * TEX_WIDTH / column_h) * TEX_SCALE;
		mlx_pixel_put(vars.mlx, vars.win, p1.x, p1.y++, 0xFFD700);
	}
}
*/