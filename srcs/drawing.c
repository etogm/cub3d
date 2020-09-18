/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   drawing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ljanette <ljanette@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/04 19:56:37 by ljanette          #+#    #+#             */
/*   Updated: 2020/09/18 17:29:13 by ljanette         ###   ########.fr       */
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

void		brezenhem(t_vars vars, int x0, int y0, int x1, int y1, int color)
{
  int A, B, sign;
  A = y1 - y0;
  B = x0 - x1;
  if (abs(A) > abs(B)) sign = 1;
  else sign = -1;
  int signa, signb;
  if (A < 0) signa = -1;
  else signa = 1;
  if (B < 0) signb = -1;
  else signb = 1;
  int f = 0;
  mlx_pixel_put(vars.mlx, vars.win, x0, y0, color);
  int x = x0, y = y0;
  if (x0 == x1 && y0 && y1)
    return;
  if (sign == -1) 
  {
    do {
      f += A*signa;
      if (f > 0)
      {
        f -= B*signb;
        y += signa;
      }
      x -= signb;
  		mlx_pixel_put(vars.mlx, vars.win, x, y, color);
    } while (x != x1 || y != y1);
  }
  else
  {
    do {
      f += B*signb;
      if (f > 0) {
        f -= A*signa;
        x -= signb;
      }
      y += signa;
      
  mlx_pixel_put(vars.mlx, vars.win, x, y, color);
    } while (x != x1 || y != y1);
  }
}
