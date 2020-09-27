/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ljanette <ljanette@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/01 21:55:57 by ljanette          #+#    #+#             */
/*   Updated: 2020/09/27 13:10:59 by ljanette         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include <stdlib.h>
# include <math.h>
# include <stdio.h>

# define	PI			3.14159265359
# define	SQUARE_SIZE	30
# define	WIDTH		1080

# define	FOV			PI / 3
# define	HALF_FOV	FOV / 2
# define	NUM_RAYS	WIDTH
# define	MAX_DEPTH	5000
# define	DELTA_ANGLE	FOV / NUM_RAYS
# define	DIST		NUM_RAYS / (2 * tan(HALF_FOV))
# define	PROJ_COEFF	DIST * SQUARE_SIZE
# define	SCALE		WIDTH / NUM_RAYS

# define	TEX_WIDTH	256
# define	TEX_HEIGHT	256
# define	TEX_SCALE	TEX_WIDTH / SQUARE_SIZE

# define	KEY_W		13//119
# define	KEY_A		0//97
# define	KEY_S		1//115
# define	KEY_D		2//100
# define	KEY_CTRL	65507
# define	KEY_ALT	 	65513
# define	KEY_ESC		53//65307
# define	KEY_LEFT	123//65361
# define	KEY_RIGHT	124//65363

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
	double		x;
	double		y;
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

typedef	struct	s_raycast
{
	int			num_rays;
	double		delta_angle;
	double		dist;
	double		proj_coeff;
	int			scale;
}				t_raycast;


typedef	struct	s_player
{
	t_point		*pos;
	double		angle;
	int			speed;
}				t_player;

typedef struct	s_vars
{
	void		*mlx;
	void		*win;
	t_player	*player;
	t_settings	*settings;
	t_img		img;
}				t_vars;

t_settings		*settings_parser(char *file);
char			**map_parser(int fd);
int				**map_get(int fd);
int				map_checker(char **map);

int				abs(int x);
int				max(int a, int b);

void			draw_square(t_vars vars, t_point p1, t_point p2, int color);
void			brezenhem(t_vars vars, int x0, int y0, int x1, int y1, int color);

void			ray_casting(t_vars vars, t_point pos, double angle);

void			map_draw(t_vars vars, char **text_map);

t_player		*player_init(void);
void			player_contoller(int keycode, t_vars *vars);

#endif