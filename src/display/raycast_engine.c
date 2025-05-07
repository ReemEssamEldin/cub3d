/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsetyamu <hsetyamu@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/07 20:36:04 by hsetyamu          #+#    #+#             */
/*   Updated: 2025/05/07 20:41:35 by hsetyamu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3d.h"

void	ray_casting(t_data *cub3d, float camera_x, float *ray_x, float *ray_y);
void	calc_deltadist(t_data *cub3d);
void	determine_hitpos(t_data *cub3d, float *ray_x, float *ray_y);
void	calc_drawparams(t_data *cub3d);
void	calc_textinfo(t_data *cub3d);

void	ray_casting(t_data *cub3d, float camera_x, float *ray_x, float *ray_y)
{
	define_raydir(cub3d, camera_x, &cub3d->calc.ray_dir_x, &cub3d->calc.ray_dir_y);
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
	if (cub3d->calc.ray_dir_x == 0)
		cub3d->calc.delta_dist_x = 1e30;
	else
		cub3d->calc.delta_dist_x = fabs(1 / cub3d->calc.ray_dir_x);
	
	if (cub3d->calc.ray_dir_y == 0)
		cub3d->calc.delta_dist_y = 1e30;
	else
		cub3d->calc.delta_dist_y = fabs(1 / cub3d->calc.ray_dir_y);
}

void	determine_hitpos(t_data *cub3d, float *ray_x, float *ray_y)
{
	if (cub3d->calc.side == 0)
		cub3d->calc.wall_dist = cub3d->calc.side_dist_x - cub3d->calc.delta_dist_x;
	else
		cub3d->calc.wall_dist = cub3d->calc.side_dist_y - cub3d->calc.delta_dist_y;
	if (cub3d->calc.side == 0)
	{
		*ray_x = cub3d->calc.map_x * BLOCK;
		if (cub3d->calc.step_x > 0)
			*ray_x -= 0.001;
		*ray_y = (cub3d->calc.pos_y + cub3d->calc.wall_dist * 
			cub3d->calc.ray_dir_y) * BLOCK;
	}
	else
	{
		*ray_x = (cub3d->calc.pos_x + cub3d->calc.wall_dist * 
			cub3d->calc.ray_dir_x) * BLOCK;
		*ray_y = cub3d->calc.map_y * BLOCK;
		if (cub3d->calc.step_y > 0)
			*ray_y -= 0.001;
	}
}

void	calc_drawparams(t_data *cub3d)
{
	int	line_height;
	int	draw_start;
	int	draw_end;

	line_height = (int)(HEI / cub3d->calc.wall_dist);
	draw_start = -line_height / 2 + HEI / 2;
	if (draw_start < 0)
		draw_start = 0;
	draw_end = line_height / 2 + HEI / 2;
	if (draw_end >= HEI)
		draw_end = HEI - 1;
	
	cub3d->calc.line_height = line_height;
	cub3d->calc.draw_start = draw_start;
	cub3d->calc.draw_end = draw_end;
}

void	calc_textinfo(t_data *cub3d)
{
	float	wall_x;
	int		tex_num;
	
	if (cub3d->calc.side == 0)
		wall_x = cub3d->calc.pos_y + cub3d->calc.wall_dist * cub3d->calc.ray_dir_y;
	else
		wall_x = cub3d->calc.pos_x + cub3d->calc.wall_dist * cub3d->calc.ray_dir_x;
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
