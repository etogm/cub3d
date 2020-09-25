/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ljanette <ljanette@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/04 19:09:50 by ljanette          #+#    #+#             */
/*   Updated: 2020/09/25 14:52:55 by ljanette         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

t_player		*player_init(void)
{
	t_player	*player;
	t_point		*pos;

	player = (t_player*)malloc(sizeof(t_player));
	pos = (t_point*)malloc(sizeof(t_point));
	pos->x = 50;
	pos->y = 50;
	player->pos = pos;
	player->angle = 0;
	player->speed = 2;
	return (player);
}

void			player_contoller(int keycode, t_vars *vars)
{
	t_point 	p2;

	if (keycode == KEY_LEFT)
		vars->player->angle -= 0.1;
	else if (keycode == KEY_RIGHT)
		vars->player->angle += 0.1;
	else if (keycode == KEY_W)
	{
		vars->player->pos->x += vars->player->speed * cos(vars->player->angle); 
		vars->player->pos->y += vars->player->speed * sin(vars->player->angle);
	}
	else if (keycode == KEY_A)
	{
		vars->player->pos->x += vars->player->speed * sin(vars->player->angle); 
		vars->player->pos->y += -vars->player->speed * cos(vars->player->angle);
	}
	else if (keycode == KEY_S)
	{
		vars->player->pos->x += -vars->player->speed * cos(vars->player->angle); 
		vars->player->pos->y += -vars->player->speed * sin(vars->player->angle);
	}
	else if (keycode == KEY_D)
	{
		vars->player->pos->x += -vars->player->speed * sin(vars->player->angle); 
		vars->player->pos->y += vars->player->speed * cos(vars->player->angle);
	}
}
