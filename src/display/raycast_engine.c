/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast_engine.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsetyamu <hsetyamu@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/07 20:36:04 by hsetyamu          #+#    #+#             */
/*   Updated: 2025/05/07 21:01:06 by hsetyamu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3d.h"

void	ray_casting(t_data *cub3d, float cam_x, float *ray_x, float *ray_y);
void	calc_deltadist(t_data *cub3d);
void	determine_hitpos(t_data *cub3d, float *ray_x, float *ray_y);
void	calc_drawparams(t_data *cub3d);
void	calc_textinfo(t_data *cub3d);

void	ray_casting(t_data *cub3d, float cam_x, float *ray_x, float *ray_y)
{
	define_raydir(cub3d, cam_x, &cub3d->calc.ray_dirx, &cub3d->calc.ray_diry);
	cub3d->calc.pos_x = cub3d->player.x / BLOCK;
	cub3d->calc.pos_y = cub3d->player.y / BLOCK;
	cub3d->calc.map_x = (int)(cub3d->calc.pos_x);
	cub3d->calc.map_y = (int)(cub3d->calc.pos_y);
	calc_deltadist(cub3d);
	dda_setup(cub3d);
	dda_execute(cub3d);
	determine_hitpos(cub3d, ray_x, ray_y);
	calc_drawparams(cub3d);
	calc_textinfo(cub3d);
}

void	calc_deltadist(t_data *cub3d)
{
	if (cub3d->calc.ray_dirx == 0)
		cub3d->calc.delta_distx = 1e30;
	else
		cub3d->calc.delta_distx = fabs(1 / cub3d->calc.ray_dirx);
	if (cub3d->calc.ray_diry == 0)
		cub3d->calc.delta_disty = 1e30;
	else
		cub3d->calc.delta_disty = fabs(1 / cub3d->calc.ray_diry);
}

void	determine_hitpos(t_data *cub3d, float *ray_x, float *ray_y)
{
	if (cub3d->calc.side == 0)
		cub3d->calc.wall_dist = cub3d->calc.side_distx - cub3d->calc.delta_distx;
	else
		cub3d->calc.wall_dist = cub3d->calc.side_disty - cub3d->calc.delta_disty;
	if (cub3d->calc.side == 0)
	{
		*ray_x = cub3d->calc.map_x * BLOCK;
		if (cub3d->calc.step_x > 0)
			*ray_x -= 0.001;
		*ray_y = (cub3d->calc.pos_y + cub3d->calc.wall_dist * 
				cub3d->calc.ray_diry) * BLOCK;
	}
	else
	{
		*ray_x = (cub3d->calc.pos_x + cub3d->calc.wall_dist * 
				cub3d->calc.ray_dirx) * BLOCK;
		*ray_y = cub3d->calc.map_y * BLOCK;
		if (cub3d->calc.step_y > 0)
			*ray_y -= 0.001;
	}
}

void	calc_drawparams(t_data *cub3d)
{
	cub3d->calc.line_height = (int)(HEI / cub3d->calc.wall_dist);
	cub3d->calc.draw_start = -cub3d->calc.line_height / 2 + HEI / 2;
	if (cub3d->calc.draw_start < 0)
		cub3d->calc.draw_start = 0;
	cub3d->calc.draw_end = cub3d->calc.line_height / 2 + HEI / 2;
	if (cub3d->calc.draw_end >= HEI)
		cub3d->calc.draw_end = HEI - 1;
}

void	calc_textinfo(t_data *cub3d)
{
	float	wall_x;
	int		tex_num;

	if (cub3d->calc.side == 0)
		wall_x = cub3d->calc.pos_y + cub3d->calc.wall_dist * cub3d->calc.ray_diry;
	else
		wall_x = cub3d->calc.pos_x + cub3d->calc.wall_dist * cub3d->calc.ray_dirx;
	wall_x -= floor(wall_x);
	tex_num = 0;
	if (cub3d->calc.side == 0)
	{
		if (cub3d->calc.step_x > 0)
			tex_num = 0;
		else
			tex_num = 1;
	}
	else
	{
		if (cub3d->calc.step_y > 0)
			tex_num = 2;
		else
			tex_num = 3;
	}
	cub3d->calc.wall_x = wall_x;
	cub3d->calc.tex_num = tex_num;
}
