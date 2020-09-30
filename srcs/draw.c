/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ljanette <ljanette@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/29 20:02:26 by ljanette          #+#    #+#             */
/*   Updated: 2020/09/29 20:25:28 by ljanette         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mlx.h"
#include "cub3d.h"

void        draw_back(t_vars vars)
{
	int     i;
	int     j;

	i = 0;
	while (i < vars.settings->r_y / 2)
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
			mlx_pixel_put(vars.mlx, vars.win, j++, i, vars.settings->clr_ceiling);
		i++;
	}
}
