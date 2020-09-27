/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   settings_parser.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ljanette <ljanette@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/01 18:47:07 by ljanette          #+#    #+#             */
/*   Updated: 2020/09/27 12:33:15 by ljanette         ###   ########.fr       */
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
	return(r << 16 | g << 8 | b);
}

int				settings_set(t_settings *settings, char *line)
{
	char		**params;

	params = ft_split(line, ' ');
	if (!ft_strncmp(params[0], "R", ft_strlen(params[0])) && settings->r_x == -1 && settings->r_y == -1)
	{
		settings->r_x = ft_atoi(params[1]);
		settings->r_y = ft_atoi(params[2]);
	}
	else if (!ft_strncmp(params[0], "NO", ft_strlen(params[0])) && !settings->path_no)
		settings->path_no = ft_strdup(params[1]);
	else if (!ft_strncmp(params[0], "WE", ft_strlen(params[0])) && !settings->path_we)
		settings->path_we = ft_strdup(params[1]);
	else if (!ft_strncmp(params[0], "EA", ft_strlen(params[0])) && !settings->path_ea)
		settings->path_ea = ft_strdup(params[1]);
	else if (!ft_strncmp(params[0], "S", ft_strlen(params[0]))  && !settings->path_s)
		settings->path_s = ft_strdup(params[1]);
	else if (!ft_strncmp(params[0], "SO", ft_strlen(params[0])) && !settings->path_so)
		settings->path_so = ft_strdup(params[1]);
	else if (!ft_strncmp(params[0], "F", ft_strlen(params[0]))  && settings->clr_floor == -1)
		settings->clr_floor = color_get_rgb(ft_split(params[1], ','));
	else if (!ft_strncmp(params[0], "C", ft_strlen(params[0]))  && settings->clr_ceiling == -1)
		settings->clr_ceiling = color_get_rgb(ft_split(params[1], ','));
	else
		return (0);
	settings_params_free(params);
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
			break;
	}
	if (!(settings->text_map = map_parser(fd)))
		return (NULL);
	free(line);
	close(fd);
	return (settings);
}
