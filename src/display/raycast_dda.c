/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast_dda.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsetyamu <hsetyamu@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/07 20:41:07 by hsetyamu          #+#    #+#             */
/*   Updated: 2025/05/07 20:41:39 by hsetyamu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3d.h"

void	dda_setup(t_data *cub3d);
void	dda_execute(t_data *cub3d);

void	dda_setup(t_data *cub3d)
{
	if (cub3d->calc.ray_dir_x < 0)
	{
		cub3d->calc.step_x = -1;
		cub3d->calc.side_dist_x = (cub3d->calc.pos_x - cub3d->calc.map_x)
			* cub3d->calc.delta_dist_x;
	}
	else
	{
		cub3d->calc.step_x = 1;
		cub3d->calc.side_dist_x = (cub3d->calc.map_x + 1.0 - cub3d->calc.pos_x)
			* cub3d->calc.delta_dist_x;
	}
	if (cub3d->calc.ray_dir_y < 0)
	{
		cub3d->calc.step_y = -1;
		cub3d->calc.side_dist_y = (cub3d->calc.pos_y - cub3d->calc.map_y)
			* cub3d->calc.delta_dist_y;
	}
	else
	{
		cub3d->calc.step_y = 1;
		cub3d->calc.side_dist_y = (cub3d->calc.map_y + 1.0 - cub3d->calc.pos_y)
			* cub3d->calc.delta_dist_y;
	}
}

void	dda_execute(t_data *cub3d)
{
	int	hit_flag;

	hit_flag = 0;
	while (hit_flag == 0)
	{
		if (cub3d->calc.side_dist_x < cub3d->calc.side_dist_y)
		{
			cub3d->calc.side_dist_x += cub3d->calc.delta_dist_x;
			cub3d->calc.map_x += cub3d->calc.step_x;
			cub3d->calc.side = 0;
		}
		else
		{
			cub3d->calc.side_dist_y += cub3d->calc.delta_dist_y;
			cub3d->calc.map_y += cub3d->calc.step_y;
			cub3d->calc.side = 1;
		}
		if (cub3d->calc.map_y < 0 || cub3d->calc.map_x < 0 || 
			cub3d->calc.map_y >= cub3d->map_info.map_rows || 
			cub3d->calc.map_x >= (int)ft_strlen(
				cub3d->map_info.map[cub3d->calc.map_y]) || 
			cub3d->map_info.map[cub3d->calc.map_y][cub3d->calc.map_x] == '1')
			hit_flag = 1;
	}
}
