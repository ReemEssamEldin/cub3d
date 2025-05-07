/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsetyamu <hsetyamu@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/06 16:41:00 by hsetyamu          #+#    #+#             */
/*   Updated: 2025/05/07 17:47:59 by hsetyamu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3d.h"

void	mini_map(t_data *cub3d);
void	draw_mm(t_data *cub3d);
void	mm_bg(t_data *cub3d);
void	mm_walls(t_data *cub3d);
void	draw_mmrays(t_data *cub3d);

void	mini_map(t_data *cub3d)
{
	draw_mm(cub3d);
	draw_mmrays(cub3d);
	draw_square(cub3d->player.x - (BLOCK / 4), 
		cub3d->player.y - (BLOCK / 4), BLOCK / 2, BLU, cub3d);
}

void	draw_mm(t_data *cub3d)
{
	cub3d->calc.bg_col = BLA;
	cub3d->calc.mm_wall_col = BRO;
	cub3d->calc.mm_space_col = BLA;
	cub3d->calc.mm_padding = 0;
	mm_bg(cub3d);
	mm_walls(cub3d);
}

void	mm_bg(t_data *cub3d)
{
	int x;
	int y;

	y = 0;
	while (y < cub3d->map_info.map_rows * BLOCK)
	{
		x = 0;
		while (x < cub3d->map_info.map_cols * BLOCK)
		{
			put_pixel(x, y, cub3d->calc.bg_col, cub3d);
			x++;
		}
		y++;
	}
}

void	mm_walls(t_data *cub3d)
{
	int		x;
	int		y;
	char	cell;

	y = 0;
	while (cub3d->map_info.map[y])
	{
		x = 0;
		while (cub3d->map_info.map[y][x])
		{
			cell = cub3d->map_info.map[y][x];
			if (cell == '1')
				draw_square(x * BLOCK, y * BLOCK, BLOCK,
					cub3d->calc.mm_wall_col, cub3d);
			else if (cell == '0')
				draw_square(x * BLOCK, y * BLOCK, BLOCK,
					cub3d->calc.mm_space_col, cub3d);
			x++;
		}
		y++;
	}
}

/* void	draw_mmrays(t_data *cub3d)
{
	int	i;

	i = 0;
	while (i < WID)
	{
		// cub3d->calc.cos_angle = cos(cub3d->calc.ray_angles[i]);
		// cub3d->calc.sin_angle = sin(cub3d->calc.ray_angles[i]);
		// cub3d->calc.ray_x = cub3d->player.x;
		// cub3d->calc.ray_y = cub3d->player.y;
		float ray_dir_x, ray_dir_y;
		float camera_x;
		camera_x = 2.0 * i / (float)WID - 1.0;
		calculate_ray_dir(cub3d, camera_x, &ray_dir_x, &ray_dir_y);
		cub3d->calc.cur_len = 0;
		while (!touch(cub3d->calc.ray_x, cub3d->calc.ray_y, cub3d) && 
			cub3d->calc.cur_len < cub3d->calc.mm_rl)
		{
			cub3d->calc.ins = 1.0 - (cub3d->calc.cur_len / cub3d->calc.mm_rl);
			if (cub3d->calc.ins < 0)
				cub3d->calc.ins = 0;
			blend_cols(&cub3d->calc);
			put_pixel(cub3d->calc.ray_x, cub3d->calc.ray_y, 
				cub3d->calc.blended_col, cub3d);
			cub3d->calc.ray_x += ray_dir_x;
			cub3d->calc.ray_y += ray_dir_x;
			cub3d->calc.cur_len += 1;
		}
		i++;
	}
} */

/* void draw_mmrays(t_data *cub3d)
{
	int i;
	float camera_x;

	i = 0;
	while (i < WID)
	{
		// Use every Nth ray for better performance (e.g., every 8th ray)
		if (i % 2 == 0)
		{
			camera_x = 2.0 * i / (float)WID - 1.0;
			// Calculate ray direction using camera plane
			// float dir_x = cos(cub3d->player.angle);
			// float dir_y = sin(cub3d->player.angle);
			// float plane_x = -dir_y * 0.66;
			// float plane_y = dir_x * 0.66;
			// float ray_dir_x = dir_x + plane_x * camera_x;
			// float ray_dir_y = dir_y + plane_y * camera_x;
			float ray_dir_x, ray_dir_y;
			calculate_ray_dir(cub3d, camera_x, &ray_dir_x, &ray_dir_y);
			// Draw the ray
			cub3d->calc.ray_x = cub3d->player.x;
			cub3d->calc.ray_y = cub3d->player.y;
			cub3d->calc.cur_len = 0;
			while (!touch(cub3d->calc.ray_x, cub3d->calc.ray_y, cub3d) && 
				cub3d->calc.cur_len < cub3d->calc.mm_rl)
			{
				cub3d->calc.ins = 1.0 - (cub3d->calc.cur_len / cub3d->calc.mm_rl);
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
		i++;
	}
} */

void draw_mmrays(t_data *cub3d)
{
	int i;
	float camera_x;

	i = 0;
	while (i < WID)
	{
		camera_x = 2.0 * i / (float)WID - 1.0;
		float ray_dir_x, ray_dir_y;
		calculate_ray_dir(cub3d, camera_x, &ray_dir_x, &ray_dir_y);
		cub3d->calc.ray_x = cub3d->player.x;
		cub3d->calc.ray_y = cub3d->player.y;
		cub3d->calc.cur_len = 0;
		while (!touch(cub3d->calc.ray_x, cub3d->calc.ray_y, cub3d) && 
			cub3d->calc.cur_len < cub3d->calc.mm_rl)
		{
			cub3d->calc.ins = 1.0 - (cub3d->calc.cur_len / cub3d->calc.mm_rl);
			if (cub3d->calc.ins < 0)
				cub3d->calc.ins = 0;
			blend_cols(&cub3d->calc);
			put_pixel(cub3d->calc.ray_x, cub3d->calc.ray_y, 
				cub3d->calc.blended_col, cub3d);
			cub3d->calc.ray_x += ray_dir_x;
			cub3d->calc.ray_y += ray_dir_y;
			cub3d->calc.cur_len += 1;
		}
		i++;
	}
}

