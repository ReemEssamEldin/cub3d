/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsetyamu <hsetyamu@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/06 16:41:00 by hsetyamu          #+#    #+#             */
/*   Updated: 2025/05/07 21:32:41 by hsetyamu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3d.h"

void	mini_map(t_data *cub3d);
void	draw_mm(t_data *cub3d);
void	mm_bg(t_data *cub3d);
void	mm_walls(t_data *cub3d);
void	draw_cellsquares(t_data *cub3d, int x, int y, char cell);

void	mini_map(t_data *cub3d)
{
	draw_mm(cub3d);
	draw_mmcone(cub3d);
	cub3d->draw.x = cub3d->player.x - (BLOCK / 4);
	cub3d->draw.y = cub3d->player.y - (BLOCK / 4);
	cub3d->draw.size = BLOCK / 2;
	cub3d->draw.col = BLU;
	draw_square(cub3d);
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
	int	x;
	int	y;

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
	int	x;
	int	y;

	y = 0;
	while (cub3d->map_info.map[y])
	{
		x = 0;
		while (cub3d->map_info.map[y][x])
		{
			draw_cellsquares(cub3d, x, y, cub3d->map_info.map[y][x]);
			x++;
		}
		y++;
	}
}

void	draw_cellsquares(t_data *cub3d, int x, int y, char cell)
{
	cub3d->draw.x = x * BLOCK;
	cub3d->draw.y = y * BLOCK;
	cub3d->draw.size = BLOCK;
	if (cell == '1')
		cub3d->draw.col = cub3d->calc.mm_wall_col;
	else if (cell == '0')
		cub3d->draw.col = cub3d->calc.mm_space_col;
	else
		return ;
	draw_square(cub3d);
}
