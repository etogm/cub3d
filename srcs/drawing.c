/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   drawing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ljanette <ljanette@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/04 19:56:37 by ljanette          #+#    #+#             */
/*   Updated: 2020/09/25 12:00:34 by ljanette         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mlx.h"
#include "cub3d.h"

void		draw_square(t_vars vars, t_point p1, t_point p2, int color)
{
	int		x;
	int		y;
	
	y = p1.y;
	while (y < p2.y)
	{
		x = p1.x;

		mlx_pixel_put(vars.mlx, vars.win, x, y, color);
		y++;
	}
}
