/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_map.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: reldahli <reldahli@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/13 13:20:57 by reldahli          #+#    #+#             */
/*   Updated: 2025/05/09 14:51:26 by reldahli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3d.h"

void	key_hooks(t_data *cub3d);
int		key_press(int keysym, t_data *cub3d);
int		key_release(int keysym, t_data *cub3d);

void	key_hooks(t_data *cub3d)
{
	if (APPLE)
	{
		mlx_hook(cub3d->win_ptr, KeyPress, 1L << 0, key_press, cub3d);
		mlx_hook(cub3d->win_ptr, KeyRelease, 1L << 1, key_release, cub3d);
		mlx_hook(cub3d->win_ptr, DestroyNotify, 0, destroy, cub3d);
	}
	else
	{
		mlx_hook(cub3d->win_ptr, KeyPress, KeyPressMask, key_press, cub3d);
		mlx_hook(cub3d->win_ptr, KeyRelease, KeyReleaseMask,
			key_release, cub3d);
		mlx_hook(cub3d->win_ptr, DestroyNotify, StructureNotifyMask,
			destroy, cub3d);
	}
}

int	key_press(int keysym, t_data *cub3d)
{
	if (keysym == XK_Escape || keysym == ESC)
		destroy(cub3d);
	if (keysym == XK_W || keysym == XK_w)
		cub3d->player.key_down = true;
	if (keysym == XK_S || keysym == XK_s)
		cub3d->player.key_up = true;
	if (keysym == XK_A || keysym == XK_a)
		cub3d->player.key_right = true;
	if (keysym == XK_D || keysym == XK_d)
		cub3d->player.key_left = true;
	if (keysym == XK_Left || keysym == LEFT)
		cub3d->player.left_rotate = true;
	if (keysym == XK_Right || keysym == RIGHT)
		cub3d->player.right_rotate = true;
	return (0);
}

int	key_release(int keysym, t_data *cub3d)
{
	if (keysym == XK_W || keysym == XK_w)
		cub3d->player.key_down = false;
	if (keysym == XK_S || keysym == XK_s)
		cub3d->player.key_up = false;
	if (keysym == XK_A || keysym == XK_a)
		cub3d->player.key_right = false;
	if (keysym == XK_D || keysym == XK_d)
		cub3d->player.key_left = false;
	if (keysym == XK_Left || keysym == LEFT)
		cub3d->player.left_rotate = false;
	if (keysym == XK_Right || keysym == RIGHT)
		cub3d->player.right_rotate = false;
	return (0);
}
