/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsetya <hsetya@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/06 17:20:06 by hsetyamu          #+#    #+#             */
/*   Updated: 2025/05/09 23:39:37 by hsetya           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3d.h"

void	draw_square(t_data *cub3d);
void	blend_cols(t_calc *calc);

/**
 * Draws a filled square on the screen using the provided data
 *
 * @param cub3d Pointer to the main data structure containing:
 *              - draw.size: Size of the square in pixels
 *              - draw.x: X coordinate of the top-left corner
 *              - draw.y: Y coordinate of the top-left corner
 *              - draw.col: Color to fill the square with
 *
 * The function fills a square pixel by pixel starting from the top-left corner
 * specified by (draw.x, draw.y) with the dimensions of draw.size x draw.size
 * using the color specified in draw.col
 */
void	draw_square(t_data *cub3d)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (j < cub3d->draw.size)
	{
		while (i < cub3d->draw.size)
		{
			put_pixel(cub3d->draw.x + i, cub3d->draw.y + j,
				cub3d->draw.col, cub3d);
			i++;
		}
		i = 0;
		j++;
	}
}

/*
** Blends two colors based on an intensity value.
**
** @param calc Pointer to t_calc struct containing:
**             - bg_col: Background color in RGB format (0xRRGGBB)
**             - base_col: Base color in RGB format (0xRRGGBB)
**             - ins: Intensity value between 0.0 and 1.0
**             - blended_col: Output blended color in RGB format
**
** The function performs linear interpolation between each RGB component
** of the background color and base color using the intensity value.
** Result is stored in calc->blended_col.
*/
void	blend_cols(t_calc *calc)
{
	int	r;
	int	g;
	int	b;

	r = ((calc->bg_col >> 16) & 0xFF) * (1.0 - calc->ins)
		+ ((calc->base_col >> 16) & 0xFF) * calc->ins;
	g = ((calc->bg_col >> 8) & 0xFF) * (1.0 - calc->ins)
		+ ((calc->base_col >> 8) & 0xFF) * calc->ins;
	b = (calc->bg_col & 0xFF) * (1.0 - calc->ins)
		+ (calc->base_col & 0xFF) * calc->ins;
	calc->blended_col = (r << 16) | (g << 8) | b;
}
