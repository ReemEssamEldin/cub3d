/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_map.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: reldahli <reldahli@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/13 13:20:57 by reldahli          #+#    #+#             */
/*   Updated: 2025/05/08 22:29:27 by reldahli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3d.h"

//experiment with mac key mappings
//keysym represents the key that was pressed
//cub3d is a pointer to the main game structure, which stores player data and game state
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

//experiment with mac key mappings
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

/* void	move_player(t_player *player)
{
	int		speed;
	float	angle_speed;
	float	cos_angle;
	float	sin_angle;

	speed = 1;
	angle_speed = 0.03;
	cos_angle = cos(player->angle);
	sin_angle = sin(player->angle);
	if (player->left_rotate)
		player->angle -= angle_speed;
	if (player->right_rotate)
		player->angle += angle_speed;
	if (player->angle > 2 * PI)
		player->angle = 0;
	if (player->angle < 0)
		player->angle = 2 * PI;
	if (player->key_down)
	{
		player->x += cos_angle * speed;
		player->y += sin_angle * speed;
	}
	if (player->key_up)
	{
		player->x -= cos_angle * speed;
		player->y -= sin_angle * speed;
	}
	if (player->key_right)
	{
		player->x += sin_angle * speed;
		player->y -= cos_angle * speed;
	}
	if (player->key_left)
	{
		player->x -= sin_angle * speed;
		player->y += cos_angle * speed;
	}
} */

void	handle_rotation(t_player *player, float angle_speed)
{
	if (player->left_rotate)
		player->angle -= angle_speed;
	if (player->right_rotate)
		player->angle += angle_speed;
	if (player->angle > 2 * PI)
		player->angle = 0;
	if (player->angle < 0)
		player->angle = 2 * PI;
}

// Try to move player in a direction with collision detection
void	try_move(t_player *player, float dx, float dy, float dir_x, float dir_y,
	float collision_buffer, t_data *cub3d)
{
	float	new_x;
	float	new_y;

	new_x = player->x + dx;
	new_y = player->y + dy;
	if (!touch(new_x + collision_buffer * dir_x,
			new_y + collision_buffer * dir_y, cub3d))
	{
		player->x = new_x;
		player->y = new_y;
	}
}

void	move_player(t_player *player, t_data *cub3d)
{
	float	speed;
	float	angle_speed;
	float	collision_buffer;
	float	dir_x;
	float	dir_y;
	float	cos_angle;
	float	sin_angle;

	speed = 0.7;
	angle_speed = 0.03;
	collision_buffer = BLOCK * 0.1;
	handle_rotation(player, angle_speed);
	cos_angle = cos(player->angle);
	sin_angle = sin(player->angle);
	if (player->key_down)
	{
		if (cos_angle > 0)
			dir_x = 1;
		else
			dir_x = -1;
		if (sin_angle > 0)
			dir_y = 1;
		else
			dir_y = -1;
		try_move(player, cos_angle * speed, sin_angle * speed,
			dir_x, dir_y, collision_buffer, cub3d);
	}
	if (player->key_up)
	{
		if (cos_angle < 0)
			dir_x = 1;
		else
			dir_x = -1;
		if (sin_angle < 0)
			dir_y = 1;
		else
			dir_y = -1;
		try_move(player, -cos_angle * speed, -sin_angle * speed,
			dir_x, dir_y, collision_buffer, cub3d);
	}
	if (player->key_right)
	{
		if (sin_angle > 0)
			dir_x = 1;
		else
			dir_x = -1;
		if (cos_angle < 0)
			dir_y = 1;
		else
			dir_y = -1;
		try_move(player, sin_angle * speed, -cos_angle * speed,
			dir_x, dir_y, collision_buffer, cub3d);
	}
	if (player->key_left)
	{
		if (sin_angle < 0)
			dir_x = 1;
		else
			dir_x = -1;
		if (cos_angle > 0)
			dir_y = 1;
		else
			dir_y = -1;
		try_move(player, -sin_angle * speed, cos_angle * speed,
			dir_x, dir_y, collision_buffer, cub3d);
	}
}

/* void	mouse_wrap(t_data *cub3d, int x, int y)
{
	if (x > WID - DIST_EDGE_MOUSE_WRAP)
	{
		x = DIST_EDGE_MOUSE_WRAP;
		mlx_mouse_move(cub3d->mlx_ptr, cub3d->win_ptr, x, y);
	}
	if (x < DIST_EDGE_MOUSE_WRAP)
	{
		x = WID - DIST_EDGE_MOUSE_WRAP;
		mlx_mouse_move(cub3d->mlx_ptr, cub3d->win_ptr, x, y);
	}
}

int	mouse_use(int x, int y, t_data *cub3d)
{
	int	old_x = WID / 2;

	wrap_mouse_position(data, x, y);
	if (x == old_x)
		return (0);
	else if (x < old_x)
		cub3d->player.left_rotate += handle_rotation(&cub3d->player, 0.03);
	else if (x > old_x)
		cub3d->player.right_rotate += handle_rotation(&cub3d->player, 0.03);
	old_x = x;
	return (0);
} */

void	key_hooks(t_data *cub3d)
{
	#ifdef __APPLE__
	mlx_hook(cub3d->win_ptr, KeyPress, 1L << 0, key_press, cub3d);
	mlx_hook(cub3d->win_ptr, KeyRelease, 1L << 1, key_release, cub3d);
	mlx_hook(cub3d->win_ptr, DestroyNotify, 0, destroy, cub3d);
	#else
	mlx_hook(cub3d->win_ptr, KeyPress, KeyPressMask, key_press, cub3d);
	mlx_hook(cub3d->win_ptr, KeyRelease, KeyReleaseMask, key_release, cub3d);
	mlx_hook(cub3d->win_ptr, DestroyNotify, StructureNotifyMask,
		destroy, cub3d);
	//mlx_hook(cub3d->win_ptr, MotionNotify, PointerMotionMask, mouse_use, cub3d);
	#endif
}
