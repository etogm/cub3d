/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ljanette <ljanette@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/04 19:02:10 by ljanette          #+#    #+#             */
/*   Updated: 2020/09/30 18:52:22 by ljanette         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "mlx.h"
#include "libft.h"
/*
int				img_init(t_vars *vars)
{
	vars->img->img_ptr = mlx_xpm_file_to_image(vars->mlx, "leavesop.xpm", vars->img->width, vars->img->height);
	vars->img->img_data = (int *)mlx_get_data_addr(vars->img->img_ptr, &vars->img->bpp, &vars->img->size_line, &vars->img->endian);
}*/

int 			game_launch(t_vars *vars, char *file)
{
	t_player	player;
	t_point		pos;

	if (!(vars->settings = settings_parser(file)))
	{
		ft_putstr_fd("Error\n", 1);
		return (0);
	}
	vars->mlx = mlx_init();
	vars->win = mlx_new_window(vars->mlx, vars->settings->r_x, vars->settings->r_y, "Cub3d");
	vars->player = player_init(*vars);
	return (1);
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
	return (1);
}

int				retry(t_vars *vars)
{
	mlx_clear_window(vars->mlx, vars->win);
	draw_back(*vars);
	ray_casting(*vars, *vars->player->pos, vars->player->angle);
	return (1);
}

int				main(int argc, char **argv)
{
	t_vars		vars;

	if (!(game_launch(&vars, argv[1])))
		return (0);
	vars.img.img_ptr = mlx_xpm_file_to_image(vars.mlx, "texture.xpm", &vars.img.width, &vars.img.height);
	vars.img.img_data = (int *)mlx_get_data_addr(vars.img.img_ptr, &vars.img.bpp, &vars.img.size_line, &vars.img.endian);
	mlx_key_hook(vars.win, game_controller, &vars);
	mlx_loop_hook(vars.mlx, retry, &vars);
	mlx_loop(vars.mlx);
	return (0);
}
