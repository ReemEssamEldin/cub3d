/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap_rays.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: reldahli <reldahli@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/07 18:11:49 by hsetyamu          #+#    #+#             */
/*   Updated: 2025/05/09 14:25:39 by reldahli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3d.h"

void	draw_mmcone(t_data *cub3d);
void	draw_mmray(t_data *cub3d, float ray_dirx, float ray_diry);

void	draw_mmcone(t_data *cub3d)
{
	int		i;
	float	cam_x;
	float	ray_dirx;
	float	ray_diry;

	i = 0;
	while (i < WID)
	{
		cam_x = 2.0 * i / (float)WID - 1.0;
		define_raydir(cub3d, cam_x, &ray_dirx, &ray_diry);
		draw_mmray(cub3d, ray_dirx, ray_diry);
		i++;
	}
}

void	draw_mmray(t_data *cub3d, float ray_dirx, float ray_diry)
{
	cub3d->calc.ray_x = cub3d->player.x;
	cub3d->calc.ray_y = cub3d->player.y;
	cub3d->calc.cur_len = 0;
	while (!touch(cub3d->calc.ray_x, cub3d->calc.ray_y, cub3d)
		&& cub3d->calc.cur_len < cub3d->calc.mm_raylen)
	{
		cub3d->calc.ins = 1.0 - (cub3d->calc.cur_len / cub3d->calc.mm_raylen);
		if (cub3d->calc.ins < 0)
			cub3d->calc.ins = 0;
		blend_cols(&cub3d->calc);
		put_pixel(cub3d->calc.ray_x, cub3d->calc.ray_y,
			cub3d->calc.blended_col, cub3d);
		cub3d->calc.ray_x += ray_dirx;
		cub3d->calc.ray_y += ray_diry;
		cub3d->calc.cur_len += 1;
	}
}
