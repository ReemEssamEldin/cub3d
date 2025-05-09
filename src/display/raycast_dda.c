/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast_dda.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: reldahli <reldahli@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/07 20:41:07 by hsetyamu          #+#    #+#             */
/*   Updated: 2025/05/09 14:55:24 by reldahli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3d.h"

void	dda_setup(t_data *cub3d);
void	dda_execute(t_data *cub3d);

void	dda_setup(t_data *cub3d)
{
	if (cub3d->calc.ray_dirx < 0)
	{
		cub3d->calc.step_x = -1;
		cub3d->calc.side_distx = (cub3d->calc.posx - cub3d->calc.map_x)
			* cub3d->calc.delta_distx;
	}
	else
	{
		cub3d->calc.step_x = 1;
		cub3d->calc.side_distx = (cub3d->calc.map_x + 1.0 - cub3d->calc.posx)
			* cub3d->calc.delta_distx;
	}
	if (cub3d->calc.ray_diry < 0)
	{
		cub3d->calc.step_y = -1;
		cub3d->calc.side_disty = (cub3d->calc.posy - cub3d->calc.map_y)
			* cub3d->calc.delta_disty;
	}
	else
	{
		cub3d->calc.step_y = 1;
		cub3d->calc.side_disty = (cub3d->calc.map_y + 1.0 - cub3d->calc.posy)
			* cub3d->calc.delta_disty;
	}
}

void	dda_execute(t_data *cub3d)
{
	int	hit_flag;

	hit_flag = 0;
	while (hit_flag == 0)
	{
		if (cub3d->calc.side_distx < cub3d->calc.side_disty)
		{
			cub3d->calc.side_distx += cub3d->calc.delta_distx;
			cub3d->calc.map_x += cub3d->calc.step_x;
			cub3d->calc.side = 0;
		}
		else
		{
			cub3d->calc.side_disty += cub3d->calc.delta_disty;
			cub3d->calc.map_y += cub3d->calc.step_y;
			cub3d->calc.side = 1;
		}
		if (cub3d->calc.map_y < 0 || cub3d->calc.map_x < 0
			|| cub3d->calc.map_y >= cub3d->map_info.map_rows
			|| cub3d->calc.map_x >= (int)ft_strlen
			(cub3d->map_info.map[cub3d->calc.map_y])
			|| cub3d->map_info.map[cub3d->calc.map_y][cub3d->calc.map_x] == '1')
			hit_flag = 1;
	}
}
