/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rendering.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsetyamu <hsetyamu@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/06 13:57:15 by hsetyamu          #+#    #+#             */
/*   Updated: 2025/05/07 21:03:33 by hsetyamu         ###   ########.fr       */
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
	move_player(&cub3d->player, cub3d);
	clear_image(cub3d);
	cub3d->calc.mm_raylen = BLOCK * 3;
	cub3d->calc.base_col = WHI;
	cub3d->calc.bg_col = BLA;
}
