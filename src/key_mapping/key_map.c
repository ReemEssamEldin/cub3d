#include "../cub3d.h"

//----------------------------------------------------------------------
// int		key_press(int keysym, t_data *cub3d);
// int		key_release(int keysym, t_data *cub3d);
// void		move_player(t_player *player);
// void		key_hooks(t_data *cub3d);
// ----------------------------------------------------------------------

//experiment with mac key mappings
int	key_press(int keysym, t_data *cub3d)
{
	if (keysym == XK_Escape || keysym == ESC)
		destroy(cub3d);
	if (keysym == XK_W || keysym == XK_w || keysym == W)
		cub3d->player.key_down = true;
	if (keysym == XK_S || keysym == XK_s || keysym == S)
		cub3d->player.key_up = true;
	if (keysym == XK_A || keysym == XK_a || keysym == A)
		cub3d->player.key_right = true;
	if (keysym == XK_D || keysym == XK_d || keysym == D)
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
	if (keysym == XK_W || keysym == XK_w || keysym == W)
		cub3d->player.key_down = false;
	if (keysym == XK_S || keysym == XK_s || keysym == S)
		cub3d->player.key_up = false;
	if (keysym == XK_A || keysym == XK_a || keysym == A)
		cub3d->player.key_right = false;
	if (keysym == XK_D || keysym == XK_d || keysym == D)
		cub3d->player.key_left = false;
	if (keysym == XK_Left || keysym == LEFT)
		cub3d->player.left_rotate = false;
	if (keysym == XK_Right || keysym == RIGHT)
		cub3d->player.right_rotate = false;
	return (0);
}

void	move_player(t_player *player)
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
}

void	key_hooks(t_data *cub3d)
{
	#ifdef __APPLE__

	mlx_hook(cub3d->win_ptr, KEYPRESS, 1L << 0, key_press, cub3d);
	mlx_hook(cub3d->win_ptr, KEYRELEASE, 1L << 1, key_release, cub3d);
	mlx_hook(cub3d->win_ptr, DESTROY, 0, destroy, cub3d);
	#else

	mlx_hook(cub3d->win_ptr, KeyPress, KeyPressMask, key_press, cub3d);
	mlx_hook(cub3d->win_ptr, KeyRelease, KeyReleaseMask, key_release, cub3d);
	mlx_hook(cub3d->win_ptr, DestroyNotify, StructureNotifyMask, destroy, cub3d);
	#endif
}
