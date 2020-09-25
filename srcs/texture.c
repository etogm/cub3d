/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ljanette <ljanette@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/19 12:30:25 by ljanette          #+#    #+#             */
/*   Updated: 2020/09/19 13:26:32 by ljanette         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mlx.h"
#include "cub3d.h"

void    texture(t_vars vars)
{
	int		bpp = 32;
	int		size_line = 256;
	int		endian = 1;
	void	*img_ptr;
	char	*img_data;
	void	*texture;
	int		size = 64;

	img_ptr = mlx_new_image(vars.mlx, 64, 64);
	img_data = mlx_get_data_addr(img_ptr, &bpp, &size_line, &endian);
	texture = mlx_xpm_file_to_image(vars.mlx, "leavesop.xpm", &size, &size);
}
