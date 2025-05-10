/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsetya <hsetya@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/06 16:41:00 by hsetyamu          #+#    #+#             */
/*   Updated: 2025/05/09 23:35:46 by hsetya           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3d.h"

void	mini_map(t_data *cub3d);
void	draw_mm(t_data *cub3d);
void	mm_bg(t_data *cub3d);
void	mm_walls(t_data *cub3d);
void	draw_cellsquares(t_data *cub3d, int x, int y, char cell);

/**
 * Renders a minimap display for the game view
 * This function handles the rendering of minimap elements including:
 * - Drawing the base minimap
 * - Drawing the player's cone of vision
 * - Drawing the player position as a blue square
 *
 * @param cub3d Pointer to the main game data structure
 * @return void
 */
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

/**
 * @brief Handles the minimap drawing process
 *
 * Sets up colors and padding for the minimap and calls necessary functions
 * to draw the minimap background and walls. The minimap represents a simplified
 * top-down view of the map where:
 * - Background is black (BLA)
 * - Walls are brown (BRO)
 * - Empty spaces are black (BLA)
 *
 * @param cub3d Pointer to the main data structure containing game information
 */
void	draw_mm(t_data *cub3d)
{
	cub3d->calc.bg_col = BLA;
	cub3d->calc.mm_wall_col = BRO;
	cub3d->calc.mm_space_col = BLA;
	cub3d->calc.mm_padding = 0;
	mm_bg(cub3d);
	mm_walls(cub3d);
}

/**
 * Draw the background of the minimap
 * Fills the entire minimap area with a background color
 * by iterating through each pixel within the map dimensions
 *
 * @param cub3d Pointer to the main data structure containing
 *              map information and calculation data
 */
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

/**
 * Renders walls on the minimap by iterating through the map data
 * and drawing cell squares for each position
 *
 * @param cub3d Pointer to the main data structure containing map information
 *              and rendering details
 *
 * The function loops through each position in the 2D map array and calls
 * draw_cellsquares() to render individual cells based on the map content
 */
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

/**
 * @brief Draws squares on minimap based on cell type
 *
 * This function draws squares on the minimap for each cell in the map.
 * The squares are drawn based on the cell type ('1' for walls, '0' for spaces).
 * The position is calculated by multiplying grid coordinates by BLOCK size.
 *
 * @param cub3d Pointer to main program structure
 * @param x X-coordinate in grid
 * @param y Y-coordinate in grid
 * @param cell Character representing cell type ('1' for wall, '0' for space)
 *
 * @return void
 */
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
