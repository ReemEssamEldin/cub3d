/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsetya <hsetya@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/13 13:20:45 by reldahli          #+#    #+#             */
/*   Updated: 2025/05/09 21:52:56 by hsetya           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3d.h"

void	init_cub3d(t_data *cub3d);
void	init_mlx(t_data *cub3d);
void	init_player(t_data *cub3d);

void	init_cub3d(t_data *cub3d)
{
	cub3d->mlx_ptr = NULL;
	cub3d->win_ptr = NULL;
	cub3d->img_ptr = NULL;
}

void	init_mlx(t_data *cub3d)
{
	cub3d->mlx_ptr = mlx_init();
	if (!cub3d->mlx_ptr)
		terminate(cub3d, "Error\nMLX init failed.");
	cub3d->win_ptr = mlx_new_window(cub3d->mlx_ptr, WID, HEI, "Cub3D");
	if (!cub3d->win_ptr)
		terminate(cub3d, "Error\nWindow creation failed.");
	cub3d->img_ptr = mlx_new_image(cub3d->mlx_ptr, WID, HEI);
	cub3d->addr = mlx_get_data_addr(cub3d->img_ptr, &cub3d->bpp,
			&cub3d->line_len, &cub3d->endian);
	load_multitexs(cub3d);
}

void	init_player(t_data *cub3d)
{
	if (!put_player(cub3d))
		terminate(cub3d, "Error\nPlayer position (missing/duplicate)");
	cub3d->player.key_up = false;
	cub3d->player.key_down = false;
	cub3d->player.key_right = false;
	cub3d->player.key_left = false;
	cub3d->player.left_rotate = false;
	cub3d->player.right_rotate = false;
}
