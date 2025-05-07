/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap_rays.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsetyamu <hsetyamu@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/07 18:11:49 by hsetyamu          #+#    #+#             */
/*   Updated: 2025/05/07 19:43:15 by hsetyamu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3d.h"

void	draw_mmcone(t_data *cub3d);
void	trace_mmray(t_data *cub3d, float ray_dir_x, float ray_dir_y);

void	draw_mmcone(t_data *cub3d)
{
	int		i;
	float	camera_x;
	float	ray_dir_x;
	float	ray_dir_y;

	i = 0;
	while (i < WID)
	{
		camera_x = 2.0 * i / (float)WID - 1.0;
		define_raydir(cub3d, camera_x, &ray_dir_x, &ray_dir_y);
		trace_mmray(cub3d, ray_dir_x, ray_dir_y);
		i++;
	}
}

void	trace_mmray(t_data *cub3d, float ray_dir_x, float ray_dir_y)
{
	cub3d->calc.ray_x = cub3d->player.x;
	cub3d->calc.ray_y = cub3d->player.y;
	cub3d->calc.cur_len = 0;
	while (!touch(cub3d->calc.ray_x, cub3d->calc.ray_y, cub3d) && 
		cub3d->calc.cur_len < cub3d->calc.mm_raylen)
	{
		cub3d->calc.ins = 1.0 - (cub3d->calc.cur_len / cub3d->calc.mm_raylen);
		if (cub3d->calc.ins < 0)
			cub3d->calc.ins = 0;
		blend_cols(&cub3d->calc);
		put_pixel(cub3d->calc.ray_x, cub3d->calc.ray_y, 
			cub3d->calc.blended_col, cub3d);
		cub3d->calc.ray_x += ray_dir_x;
		cub3d->calc.ray_y += ray_dir_y;
		cub3d->calc.cur_len += 1;
	}
}
