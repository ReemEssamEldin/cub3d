/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_map.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsetya <hsetya@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/13 13:20:57 by reldahli          #+#    #+#             */
/*   Updated: 2025/05/10 00:01:05 by hsetya           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3d.h"

void	key_hooks(t_data *cub3d);
int		key_press(int keysym, t_data *cub3d);
int		key_release(int keysym, t_data *cub3d);

/**
 * @brief Sets up key event hooks for the cub3d window
 *
 * Configures window event hooks for key press, key release and window destroy
 * events. Uses different event masks depending on whether code is running on
 * Apple or other platforms.
 *
 * @param cub3d Pointer to main program data structure containing window pointer
 *
 * For Apple systems:
 * - Key press: event 2 with mask 1L << 0
 * - Key release: event 3 with mask 1L << 1
 * - Destroy notify: event 17 with mask 0
 *
 * For other systems:
 * - Uses KeyPressMask, KeyReleaseMask and StructureNotifyMask
 */
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

/**
 * @brief Handles key press events for player movement and game control
 *
 * Maps keyboard inputs to player movement and rotation controls:
 * - ESC: Exits the game
 * - W/S: Forward/Backward movement
 * - A/D: Left/Right movement
 * - Left/Right arrows: Rotation control
 *
 * @param keysym The key code of the pressed key
 * @param cub3d Pointer to the main game data structure
 * @return Returns 0 after setting the appropriate movement flags
 */
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
