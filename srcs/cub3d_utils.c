/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ljanette <ljanette@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/04 20:34:51 by ljanette          #+#    #+#             */
/*   Updated: 2020/10/02 16:52:11 by ljanette         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int		abs(int x)
{
	if (x < 0)
		return (-x);
	return (x);
}

int		max(int a, int b)
{
	if (a < b)
		return (b);
	return (a);
}

int		is_map_side(char c)
{
	if (c == 'N' || c == 'W' || c == 'E' || c == 'S')
		return (1);
	return (0);
}

int		is_map_char(char c)
{
	if (c == 'N' || c == 'W' || c == 'E' || c == 'S'
	|| c == '0' || c == '1' || c == '2')
		return (1);
	return (0);
}
