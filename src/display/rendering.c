/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rendering.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsetya <hsetya@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/06 13:57:15 by hsetyamu          #+#    #+#             */
/*   Updated: 2025/05/09 23:46:11 by hsetya           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3d.h"

int		render(t_data *cub3d);
void	init_render(t_data *cub3d);

/**
 * @brief Renders the game frame to the window
 *
 * This function handles the main rendering process by:
 * 1. Initializing the render data
 * 2. Displaying the main game view
 * 3. Drawing the mini map (if BONUS is enabled)
 * 4. Putting the rendered image to the window
 *
 * @param cub3d Pointer to the main game data structure
 * @return int Returns 0 on successful rendering
 */
int	render(t_data *cub3d)
{
	init_render(cub3d);
	main_display(cub3d);
	if (BONUS)
		mini_map(cub3d);
	mlx_put_image_to_window(cub3d->mlx_ptr, cub3d->win_ptr,
		cub3d->img_ptr, 0, 0);
	return (0);
}

/**
 * @brief Initialize rendering parameters for the game
 *
 * This function sets up initial rendering conditions by:
 * - Moving player to their position
 * - Clearing the display image
 * - Setting minimap ray length to 3 blocks
 * - Setting base color to white
 * - Setting background color to black
 *
 * @param cub3d Pointer to main game data structure containing all game info
 */
void	init_render(t_data *cub3d)
{
	move_player(&cub3d->player, cub3d);
	clear_image(cub3d);
	cub3d->calc.mm_raylen = BLOCK * 3;
	cub3d->calc.base_col = WHI;
	cub3d->calc.bg_col = BLA;
}
