/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rendering.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsetyamu <hsetyamu@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/06 13:57:15 by hsetyamu          #+#    #+#             */
/*   Updated: 2025/05/06 19:27:21 by hsetyamu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3d.h"

int		render(t_data *cub3d);
void	init_render(t_data *cub3d);

int	render(t_data *cub3d)
{
	init_render(cub3d);
	main_display(cub3d);
	mini_map(cub3d);
	mlx_put_image_to_window(cub3d->mlx_ptr, cub3d->win_ptr,
							cub3d->img_ptr, 0, 0);
	return (0);
}

void	init_render(t_data *cub3d)
{
	// Handle player movement
	move_player(&cub3d->player, cub3d);
	// Clear the screen for new frame
	clear_image(cub3d);
	// Set up constants
	cub3d->calc.fraction = PI / 3 / WID;
	cub3d->calc.start_x = cub3d->player.angle - PI / 6;
	cub3d->calc.mm_rl = BLOCK * 3;
	cub3d->calc.base_col = WHI;
	cub3d->calc.bg_col = BLA;
}
