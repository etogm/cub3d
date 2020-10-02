/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   settings_checker.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ljanette <ljanette@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/02 18:58:17 by ljanette          #+#    #+#             */
/*   Updated: 2020/10/02 19:37:36 by ljanette         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "cub3d.h"

int				settings_checker(t_settings *settings)
{
	if ((settings->clr_ceiling == -1 || settings->clr_floor == -1))
		return (0);
	if (ft_strncmp(&settings->path_ea[ft_strlen(settings->path_ea) - 4], ".xpm", 4) != 0)
		return (0);
	if (ft_strncmp(&settings->path_no[ft_strlen(settings->path_ea) - 4], ".xpm", 4) != 0)
		return (0);
	if (ft_strncmp(&settings->path_we[ft_strlen(settings->path_ea) - 4], ".xpm", 4) != 0)
		return (0);
	if (ft_strncmp(&settings->path_so[ft_strlen(settings->path_ea) - 4], ".xpm", 4) != 0)
		return (0);
	if (ft_strncmp(&settings->path_s[ft_strlen(settings->path_ea) - 4], ".xpm", 4) != 0)
		return (0);
	return (1);
}
