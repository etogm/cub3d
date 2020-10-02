/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   settings_parser.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ljanette <ljanette@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/01 18:47:07 by ljanette          #+#    #+#             */
/*   Updated: 2020/10/02 20:06:23 by ljanette         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fcntl.h>
#include "get_next_line.h"
#include "libft.h"
#include "cub3d.h"

void			settings_params_free(char **params)
{
	int			i;

	i = 0;
	while (params[i])
		i++;
	while (i >= 0)
		free(params[i--]);
	free(params);
}

t_settings		*settings_init(void)
{
	t_settings	*settings;

	settings = (t_settings*)malloc(sizeof(t_settings));
	settings->r_x = -1;
	settings->r_y = -1;
	settings->path_no = NULL;
	settings->path_so = NULL;
	settings->path_we = NULL;
	settings->path_ea = NULL;
	settings->path_s = NULL;
	settings->clr_floor = -1;
	settings->clr_ceiling = -1;
	settings->text_map = NULL;
	return (settings);
}

int				color_get_rgb(char **params)
{
	int			r;
	int			g;
	int			b;

	r = ft_atoi(params[0]);
	g = ft_atoi(params[1]);
	b = ft_atoi(params[2]);
	settings_params_free(params);
	if ((r < 0 || r > 255) || (g < 0 || g > 255) || (b < 0 || b > 255))
		return (-1);
	return(r << 16 | g << 8 | b);
}

int				settings_set(t_settings *s, char *line)
{
	char		**p;

	p = ft_split(line, ' ');
	if (!ft_strncmp(p[0], "R", ft_strlen(p[0])) && s->r_x == -1 && s->r_y == -1)
	{
		s->r_x = ft_atoi(p[1]);
		s->r_y = ft_atoi(p[2]);
	}
	else if (!ft_strncmp(p[0], "NO", ft_strlen(p[0])) && !s->path_no)
		s->path_no = ft_strdup(p[1]);
	else if (!ft_strncmp(p[0], "WE", ft_strlen(p[0])) && !s->path_we)
		s->path_we = ft_strdup(p[1]);
	else if (!ft_strncmp(p[0], "EA", ft_strlen(p[0])) && !s->path_ea)
		s->path_ea = ft_strdup(p[1]);
	else if (!ft_strncmp(p[0], "S", ft_strlen(p[0])) && !s->path_s)
		s->path_s = ft_strdup(p[1]);
	else if (!ft_strncmp(p[0], "SO", ft_strlen(p[0])) && !s->path_so)
		s->path_so = ft_strdup(p[1]);
	else if (!ft_strncmp(p[0], "F", ft_strlen(p[0])) && s->clr_floor == -1)
		s->clr_floor = color_get_rgb(ft_split(p[1], ','));
	else if (!ft_strncmp(p[0], "C", ft_strlen(p[0])) && s->clr_ceiling == -1)
		s->clr_ceiling = color_get_rgb(ft_split(p[1], ','));
	else
		return (0);
	settings_params_free(p);
	return (1);
}

t_settings		*settings_parser(char *file)
{
	int			fd;
	int			i;
	char		*line;
	t_settings	*settings;

	if (!(fd = open(file, O_RDONLY)))
		return (NULL);
	settings = settings_init();
	line = NULL;
	i = 0;
	while (get_next_line(fd, &line) > 0)
	{
		if (*line != '\0')
			if (!(i += settings_set(settings, line)))
				return (NULL);
		free(line);
		if (i == 8)
			break ;
	}
	if (!(settings->text_map = map_parser(fd)))
		return (NULL);
	free(line);
	close(fd);
	/*if (!(settings_checker(settings)))
		return (NULL);*/
	return (settings);
}
