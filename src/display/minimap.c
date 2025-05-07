/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsetyamu <hsetyamu@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/06 16:41:00 by hsetyamu          #+#    #+#             */
/*   Updated: 2025/05/07 18:12:29 by hsetyamu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3d.h"

void	mini_map(t_data *cub3d);
void	draw_mm(t_data *cub3d);
void	mm_bg(t_data *cub3d);
void	mm_walls(t_data *cub3d);

void	mini_map(t_data *cub3d)
{
	draw_mm(cub3d);
	draw_mmcone(cub3d);
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
