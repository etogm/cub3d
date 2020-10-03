/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ljanette <ljanette@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/01 21:55:57 by ljanette          #+#    #+#             */
/*   Updated: 2020/10/03 18:27:51 by ljanette         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include <stdlib.h>
# include <math.h>
# include <stdio.h>

# define	PI			3.14
# define	SQUARE_SIZE	100
# define	TILE		100
# define	WIDTH		640

# define	FOV			PI / 4
# define	HALF_FOV	FOV / 2
# define	NUM_RAYS	640
# define	MAX_DEPTH	800
# define	DELTA_ANGLE	FOV / NUM_RAYS
# define	DIST		NUM_RAYS / (2 * tan(HALF_FOV))
# define	PROJ_COEFF	DIST * TILE
# define	SCALE		WIDTH / NUM_RAYS

# define	TEX_WIDTH	256
# define	TEX_HEIGHT	256
# define	TEX_SCALE	SQUARE_SIZE / TEX_WIDTH

# define	KEY_W		13//119
# define	KEY_A		0//97
# define	KEY_S		1//115
# define	KEY_D		2//100
# define	KEY_CTRL	65507
# define	KEY_ALT	 	65513
# define	KEY_ESC		53//65307
# define	KEY_LEFT	123//65361
# define	KEY_RIGHT	124//65363

# define	MAX(a, b)	((a < b) ? b : a)
# define	MIN(a, b)	((a < b) ? a : b)

typedef	struct	s_img
{
	int			bpp;
	int			size_line;
	int			endian;
	int			width;
	int			height;
	void		*img_ptr;
	int			*img_data;
}				t_img;

typedef	struct	s_point
{
	float		x;
	float		y;
}				t_point;

typedef struct	s_settings
{
	int			r_x;
	int			r_y;
	char		*path_no;
	char		*path_so;
	char		*path_we;
	char		*path_ea;
	char		*path_s;
	int			clr_floor;
	int			clr_ceiling;
	char		**text_map;
}				t_settings;

typedef	struct	s_player
{
	t_point		*pos;
	float		angle;
	int			speed;
}				t_player;

typedef struct	s_vars
{
	void		*mlx;
	void		*win;
	t_player	*player;
	t_settings	*settings;
	t_img		*img;
}				t_vars;

int				settings_checker(t_settings *settings);
t_settings		*settings_parser(char *file);
char			**map_parser(int fd);
int				**map_get(int fd);
int				map_checker(char **map);

int				abs(int x);
int				max(int a, int b);
int				is_map_side(char c);
int				is_map_char(char c);

void			draw_back(t_vars vars);
//void			draw_line(t_vars vars, t_point p1, int column_h, int x);
void			ray_casting(t_vars vars, t_point pos, double angle);
void			ray_cast(t_vars vars);

void			map_draw(t_vars vars, char **text_map);

t_player		*player_init(t_vars vars);
void			player_contoller(int keycode, t_vars *vars);

#endif