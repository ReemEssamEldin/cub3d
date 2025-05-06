/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsetyamu <hsetyamu@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/06 17:20:06 by hsetyamu          #+#    #+#             */
/*   Updated: 2025/05/06 17:22:05 by hsetyamu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3d.h"

void	draw_square(int x, int y, int size, int color, t_data *cub3d);
void	blend_cols(t_calc *calc);

void	draw_square(int x, int y, int size, int color, t_data *cub3d)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (j < size)
	{
		while (i < size)
		{
			put_pixel(x + i, y + j, color, cub3d);
			i++;
		}
		i = 0;
		j++;
	}
}

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