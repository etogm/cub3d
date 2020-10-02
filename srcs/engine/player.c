/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ljanette <ljanette@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/04 19:09:50 by ljanette          #+#    #+#             */
/*   Updated: 2020/10/02 20:47:02 by ljanette         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

t_player		*player_init(t_vars vars)
{
	t_player	*player;
	int			i;
	int			j;

	player = (t_player*)malloc(sizeof(t_player));
	player->pos = (t_point*)malloc(sizeof(t_point));
	i = 0;
	while (vars.settings->text_map[i])
	{
		j = 0;
		while (vars.settings->text_map[i][j])
		{
			if (is_map_side(vars.settings->text_map[i][j]))
			{
				player->pos->x = j * SQUARE_SIZE;
				player->pos->y = i * SQUARE_SIZE;
				player->angle = 0;
			}
			j++;
		}
		i++;
	}
	player->speed = 50;
	return (player);
}

void			player_contoller(int keycode, t_vars *vars)
{
	t_point		oldpos;

	oldpos.x = vars->player->pos->x;
	oldpos.y = vars->player->pos->y;
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
	if (vars->settings->text_map
		[(int)(vars->player->pos->y / SQUARE_SIZE)]
		[(int)(vars->player->pos->x / SQUARE_SIZE)] == '1')
	{
		vars->player->pos->x = oldpos.x;
		vars->player->pos->y = oldpos.y;		
	}
}
