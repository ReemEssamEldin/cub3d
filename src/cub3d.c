#include "cub3d.h"

void	init_cub3d(t_data *cub3d);
void	init_mlx(t_data *cub3d);
int		key_press(int keysym, t_data *cub3d);
int		key_release(int keysym, t_data *cub3d);
int		destroy(t_data *cub3d);
void	put_pixel(int x, int y, int color, t_data *cub3d);
void	draw_square(int x, int y, int size, int color, t_data *cub3d);
void	init_player(t_player *player);
void	move_player(t_player *player);
int		draw_loop(t_data *cub3d);
void	clear_image(t_data *cub3d);

int	main(int argc, char *argv[])
{
	t_data	cub3d;

	//check_args(argc, argv);
	(void) argc;
	(void) argv;
	init_cub3d(&cub3d);
	init_player(&cub3d.player);
	init_mlx(&cub3d);
	mlx_hook(cub3d.win_ptr, KeyPress, KeyPressMask, key_press, &cub3d);
	mlx_hook(cub3d.win_ptr, KeyRelease, KeyReleaseMask, key_release, &cub3d);
	//mlx_hook(cub3d.win_ptr, 2, 1L<<0, key_press, &cub3d);
	//mlx_hook(cub3d.win_ptr, 3, 1L<<1, key_release, &cub3d);
	mlx_hook(cub3d.win_ptr, DestroyNotify, StructureNotifyMask, destroy, &cub3d);
	mlx_loop_hook(cub3d.mlx_ptr, draw_loop, &cub3d);
	mlx_loop(cub3d.mlx_ptr);
	return (0);
}

void	init_cub3d(t_data *cub3d)
{
	cub3d->mlx_ptr = NULL;
	cub3d->win_ptr = NULL;
	cub3d->img_ptr = NULL;
}

void	init_mlx(t_data *cub3d)
{

	cub3d->mlx_ptr = mlx_init();
	cub3d->win_ptr = mlx_new_window(cub3d->mlx_ptr, WID, HEI, "Prototype");
	cub3d->img_ptr = mlx_new_image(cub3d->mlx_ptr, WID, HEI);
	cub3d->addr = mlx_get_data_addr(cub3d->img_ptr, &cub3d->bpp, &cub3d->line_len, &cub3d->endian);
	mlx_put_image_to_window(cub3d->mlx_ptr, cub3d->win_ptr, cub3d->img_ptr, 0, 0);
}

int	key_press(int keysym, t_data *cub3d)
{
	if (keysym == XK_Escape)
		destroy(cub3d);
	if (keysym == XK_W || keysym == XK_w)
		cub3d->player.key_up = true;
	if (keysym == XK_S || keysym == XK_s)
		cub3d->player.key_down = true;
	if (keysym == XK_A || keysym == XK_a)
		cub3d->player.key_left = true;
	if (keysym == XK_D || keysym == XK_d)
		cub3d->player.key_right = true;
	if (keysym == XK_Left)
		cub3d->player.left_rotate = true;
	if (keysym == XK_Right)
		cub3d->player.right_rotate = true;
	return (0);
}

int	key_release(int keysym, t_data *cub3d)
{
	if (keysym == XK_W || keysym == XK_w)
		cub3d->player.key_up = false;
	if (keysym == XK_S || keysym == XK_s)
		cub3d->player.key_down = false;
	if (keysym == XK_A || keysym == XK_a)
		cub3d->player.key_left = false;
	if (keysym == XK_D || keysym == XK_d)
		cub3d->player.key_right = false;
	if (keysym == XK_Left)
		cub3d->player.left_rotate = false;
	if (keysym == XK_Right)
		cub3d->player.right_rotate = false;
	return (0);
}

int	destroy(t_data *cub3d)
{
	if (cub3d->win_ptr)
		mlx_destroy_window(cub3d->mlx_ptr, cub3d->win_ptr);
	if (cub3d->mlx_ptr)
	{
		mlx_destroy_display(cub3d->mlx_ptr);
		free(cub3d->mlx_ptr);
	}
	exit(0);
}

void put_pixel(int x, int y, int color, t_data *cub3d)
{
	int	idx;

	if(x >= WID || y >= HEI || x < 0 || y < 0)
		return;
	idx = y * cub3d->line_len + x * cub3d->bpp / 8;
	cub3d->addr[idx] = color & 0xFF;
	cub3d->addr[idx + 1] = (color >> 8) & 0xFF;
	cub3d->addr[idx + 2] = (color >> 16) & 0xFF;
}

void draw_square(int x, int y, int size, int color, t_data *cub3d)
{
	for(int i = 0; i < size; i++)
		put_pixel(x + i, y, color, cub3d);
	for(int i = 0; i < size; i++)
		put_pixel(x, y + i, color, cub3d);
	for(int i = 0; i < size; i++)
		put_pixel(x + size, y + i, color, cub3d);
	for(int i = 0; i < size; i++)
		put_pixel(x + i, y + size, color, cub3d);
}

void init_player(t_player *player)
{
	player->x = WID / 2;
	player->y = HEI / 2;
	player->angle = PI / 2;

	player->key_up = false;
	player->key_down = false;
	player->key_right = false;
	player->key_left = false;

	player->left_rotate = false;
	player->right_rotate = false;
}

void move_player(t_player *player)
{
	int speed = 1;
	float angle_speed = 0.03;
	float cos_angle = cos(player->angle);
	float sin_angle = sin(player->angle);

	if (player->left_rotate)
		player->angle -= angle_speed;
	if (player->right_rotate)
		player->angle += angle_speed;
	if (player->angle > 2 * PI)
		player->angle = 0;
	if (player->angle < 0)
		player->angle = 2 * PI;

	if (player->key_up)
	{
		player->x += cos_angle * speed;
		player->y += sin_angle * speed;
	}
	if (player->key_down)
	{
		player->x -= cos_angle * speed;
		player->y -= sin_angle * speed;
	}
	if (player->key_left)
	{
		player->x += sin_angle * speed;
		player->y -= cos_angle * speed;
	}
	if (player->key_right)
	{
		player->x -= sin_angle * speed;
		player->y += cos_angle * speed;
	}
}

int draw_loop(t_data *cub3d)
{
	move_player(&cub3d->player);
	clear_image(cub3d);
	draw_square(cub3d->player.x, cub3d->player.y, 20, 0x00FF00, cub3d);
	//draw_square(WID/2, HEI/2, 10, 0x00FF20, cub3d);
	//draw_map(game);
	mlx_put_image_to_window(cub3d->mlx_ptr, cub3d->win_ptr, cub3d->img_ptr, 0, 0);
	return(0);
}

void clear_image(t_data *cub3d)
{
	for(int y = 0; y < HEI; y++)
		for(int x = 0; x < WID; x++)
			put_pixel(x, y, 0, cub3d);
}