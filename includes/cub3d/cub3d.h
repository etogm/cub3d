/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ljanette <ljanette@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/01 21:55:57 by ljanette          #+#    #+#             */
/*   Updated: 2020/09/18 17:31:52 by ljanette         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include <stdlib.h>
# include <math.h>
# include <stdio.h>

# define	PI			3.14159265359
# define	SQUARE_SIZE	15
# define	WIDTH		640

# define	FOV			PI / 3
# define	HALF_FOV	FOV / 2
# define	NUM_RAYS	480
# define	MAX_DEPTH	800
# define	DELTA_ANGLE	FOV / NUM_RAYS
# define	DIST		NUM_RAYS / (2 * tan(HALF_FOV))
# define	PROJ_COEFF	4 * DIST * SQUARE_SIZE
# define	SCALE		WIDTH / NUM_RAYS

# define	KEY_W		119
# define	KEY_A		97
# define	KEY_S		115
# define	KEY_D		100
# define	KEY_CTRL	65507
# define	KEY_ALT	 	65513
# define	KEY_ESC		65307
# define	KEY_LEFT	65361
# define	KEY_RIGHT	65363

typedef	struct	s_texture
{
	void		*no;
	void		*so;
	void		*we;
	void		*ea;
	void		*s;
}				t_texture;

typedef	struct	s_point
{
	int			x;
	int			y;
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
	double		angle;
	int			speed;
}				t_player;

typedef struct	s_vars
{
	void		*mlx;
	void		*win;
	t_player	*player;
	t_settings	*settings;
	t_texture	*texture;
}				t_vars;

t_settings		*settings_parser(char *file);
char			**map_parser(int fd);
int				**map_get(int fd);

int				abs(int x);
int				max(int a, int b);

void			draw_square(t_vars vars, t_point p1, t_point p2, int color);
void			brezenhem(t_vars vars, int x0, int y0, int x1, int y1, int color);

void			ray_casting(t_vars vars, t_point pos, double angle, int color);


void			map_draw(t_vars vars, char **text_map);


t_player		*player_init(void);
void			player_contoller(int keycode, t_vars *vars);

#endif