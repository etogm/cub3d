/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ljanette <ljanette@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/04 19:02:10 by ljanette          #+#    #+#             */
/*   Updated: 2020/09/18 13:51:49 by ljanette         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "mlx.h"

void			game_launch(t_vars *vars, char *file)
{
	t_player	player;
	t_point		pos;

	vars->settings = settings_parser(file);
	vars->mlx = mlx_init();
	vars->win = mlx_new_window(vars->mlx, vars->settings->r_x, vars->settings->r_y, "cub3d");
	vars->player = player_init();
}

int				game_controller(int keycode, t_vars *vars)
{
	player_contoller(keycode, vars);
	if (keycode == KEY_ESC)
	{
		mlx_destroy_window(vars->mlx, vars->win);
		exit(0);
	}
	printf("keycode: %d\n", keycode);
}

int				retry(t_vars *vars)
{
	//map_draw(*vars, vars->settings->text_map);
	ray_casting(*vars, *vars->player->pos, vars->player->angle, 0xFFFFFF);
}

int				main(int argc, char **argv)
{
	t_vars		vars;
	t_point		p2;
	int			**world_map;
	
	p2.x = 100;
	p2.y = 100;
	game_launch(&vars, argv[1]);
	mlx_key_hook(vars.win, game_controller, &vars);
	mlx_loop_hook(vars.mlx, retry, &vars);
	mlx_loop(vars.mlx);
	return 0;
}
