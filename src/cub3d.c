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
char	**init_map(void);
void	draw_map(t_data *cub3d);
bool	touch(float px, float py, t_data *cub3d);
void	draw_line(t_player *player, t_data *cub3d, float start_x, int i);
float	distance(float x, float y);
float	fixed_dist(float x1, float y1, float x2, float y2, t_data *cub3d);
void	key_hooks(t_data *cub3d);

int	main(int argc, char *argv[])
{
	t_data	cub3d;

	//check_args(argc, argv);
	(void) argc;
	(void) argv;
	init_cub3d(&cub3d);
	init_player(&cub3d.player);
	init_mlx(&cub3d);

	key_hooks(&cub3d);
	//mlx_hook(cub3d.win_ptr, KeyPress, KeyPressMask, key_press, &cub3d); //this may not work on mac
	//mlx_hook(cub3d.win_ptr, KeyRelease, KeyReleaseMask, key_release, &cub3d); //this may not work on mac
	//mlx_hook(cub3d.win_ptr, DestroyNotify, StructureNotifyMask, destroy, &cub3d); //this may not work on mac
	//mlx_hook(cub3d.win_ptr, 2, 1L<<0, key_press, &cub3d); //hopefully works on mac (?)
	//mlx_hook(cub3d.win_ptr, 3, 1L<<1, key_release, &cub3d); //hopefully works on mac (?)
	//mlx_hook(cub3d.win_ptr, 17, 0, destroy, &cub3d); //hopefully works on mac (?)

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

void	init_player(t_player *player)
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

void	init_mlx(t_data *cub3d)
{
	cub3d->map = init_map();
	cub3d->mlx_ptr = mlx_init();
	cub3d->win_ptr = mlx_new_window(cub3d->mlx_ptr, WID, HEI, "Prototype");
	cub3d->img_ptr = mlx_new_image(cub3d->mlx_ptr, WID, HEI);
	cub3d->addr = mlx_get_data_addr(cub3d->img_ptr, &cub3d->bpp, &cub3d->line_len, &cub3d->endian);
	mlx_put_image_to_window(cub3d->mlx_ptr, cub3d->win_ptr, cub3d->img_ptr, 0, 0);
}

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

/**
 * put_pixel - Puts a pixel of a specified color at a given position in the image.
 * @x: The x-coordinate of the pixel.
 * @y: The y-coordinate of the pixel.
 * @color: The color of the pixel in RGB format.
 * @cub3d: A pointer to the t_data structure containing image data.
 *
 * This function sets the color of the pixel at the specified (x, y) coordinates
 * in the image represented by the t_data structure. If the coordinates are
 * outside the bounds of the image, the function returns without making any changes.
 *
 * The color is specified in RGB format, and the function extracts the individual
 * red, green, and blue components to store them in the image data.
 */
void	put_pixel(int x, int y, int color, t_data *cub3d)
{
	int	idx;

	if(x >= WID || y >= HEI || x < 0 || y < 0)
		return;
	idx = y * cub3d->line_len + x * cub3d->bpp / 8;
	cub3d->addr[idx] = color & 0xFF;
	cub3d->addr[idx + 1] = (color >> 8) & 0xFF;
	cub3d->addr[idx + 2] = (color >> 16) & 0xFF;
}

void	draw_square(int x, int y, int size, int color, t_data *cub3d)
{
	move_player(&cub3d->player);
	clear_image(cub3d);
	draw_square(cub3d->player.x, cub3d->player.y, 32, RED, cub3d);
	draw_map(cub3d);

	float fraction = PI /3 / WID;
	float start_x = cub3d->player.angle - PI / 6;
	int i = 0;
	while(i < WID)
	{
		draw_line(&cub3d->player, cub3d, start_x, i);
		start_x += fraction;
		i++;
	}
	mlx_put_image_to_window(cub3d->mlx_ptr, cub3d->win_ptr, cub3d->img_ptr, 0, 0);
	return(0);
}

void	init_player(t_player *player)
{
	player->x = (WID / 6); //start pos
	player->y = HEI / 6; //start pos
	player->angle = PI ; //facing which way?

	player->key_up = false;
	player->key_down = false;
	player->key_right = false;
	player->key_left = false;

	player->left_rotate = false;
	player->right_rotate = false;
}

void	move_player(t_player *player)
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

//just a line, not a cone
/* int	draw_loop(t_data *cub3d)
{
	move_player(&cub3d->player);
	clear_image(cub3d);
	draw_square(cub3d->player.x, cub3d->player.y, 32, RED, cub3d);
	draw_map(cub3d);

	float	ray_x = cub3d->player.x;
	float	ray_y = cub3d->player.y;
	float	cos_angle = cos(cub3d->player.angle);
	float	sin_angle = sin(cub3d->player.angle);

	while(!touch(ray_x, ray_y, cub3d))
	{
		put_pixel(ray_x, ray_y, YEL, cub3d);
		ray_x += cos_angle;
		ray_y += sin_angle;
	}
	mlx_put_image_to_window(cub3d->mlx_ptr, cub3d->win_ptr, cub3d->img_ptr, 0, 0);
	return(0);
} */

//top-down ,conical ray
/* int	draw_loop(t_data *cub3d)
{
	move_player(&cub3d->player);
	clear_image(cub3d);
	draw_square(cub3d->player.x, cub3d->player.y, 32, RED, cub3d); //handles top-down view
	draw_map(cub3d); //handles top-down view

	float fraction = PI /3 / WID;
	float start_x = cub3d->player.angle - PI / 6;
	int i = 0;
	while(i < WID)
	{
		draw_line(&cub3d->player, cub3d, start_x, i);
		start_x += fraction;
		i++;
	}
	mlx_put_image_to_window(cub3d->mlx_ptr, cub3d->win_ptr, cub3d->img_ptr, 0, 0);
	return(0);
} */
//first person
int	draw_loop(t_data *cub3d)
{
	move_player(&cub3d->player);
	clear_image(cub3d);

	//top-down
	draw_square(cub3d->player.x, cub3d->player.y, BLOCK/2, BLU, cub3d);
	draw_map(cub3d);

	//1st-person
	float fraction = PI / 3 / WID; //FOV width
	float start_x = cub3d->player.angle - PI / 6;
	int i = 0;
	while(i < WID)
	{
		draw_line(&cub3d->player, cub3d, start_x, i);
		start_x += fraction;
		i++;
	}
	mlx_put_image_to_window(cub3d->mlx_ptr, cub3d->win_ptr, cub3d->img_ptr, 0, 0);
	return(0);
}

void	clear_image(t_data *cub3d)
{
	for(int y = 0; y < HEI; y++)
		for(int x = 0; x < WID; x++)
			put_pixel(x, y, 0, cub3d);
}

char	**init_map(void)
{
	char **map = malloc(sizeof(char *) * 11);
	map[0] = "111111111111111";
	map[1] = "100000000000001";
	map[2] = "100000000000001";
	map[3] = "100000100000001";
	map[4] = "100000000000001";
	map[5] = "100000010000001";
	map[6] = "100001000000001";
	map[7] = "100000000000001";
	map[8] = "100000000000001";
	map[9] = "111111111111111";
	map[10] = NULL;
	return (map);
/* 	char **map = malloc(sizeof(char *) * 25);
	map[0] = "111111111111111111111111";
	map[1] = "100000000000000000000001";
	map[2] = "100000000000000000000001";
	map[3] = "100000000000000000000001";
	map[4] = "100000111110000101010001";
	map[5] = "100000100010000000000001";
	map[6] = "100000100010000100010001";
	map[7] = "100000100010000000000001";
	map[8] = "100000110110000101010001";
	map[9] = "100000000000000000000001";
	map[10] = "100000000000000000000001";
	map[11] = "100000000000000000000001";
	map[12] = "100000000000000000000001";
	map[13] = "100000000000000000000001";
	map[14] = "100000000000000000000001";
	map[15] = "100000000000000000000001";
	map[16] = "111111111000000000000001";
	map[17] = "110100001000000000000001";
	map[18] = "110000101000000000000001";
	map[19] = "110100001000000000000001";
	map[20] = "110111111000000000000001";
	map[21] = "110000000000000000000001";
	map[22] = "111111111000000000000001";
	map[23] = "111111111111111111111111";
	map[24] = NULL;
	return (map); */
}

void	draw_map(t_data *cub3d)
{
	char **map = cub3d->map;
	int color = GRE;
	for(int y = 0; map[y]; y++)
		for(int x = 0; map[y][x]; x++)
			if(map[y][x] == '1')
				draw_square(x * BLOCK, y * BLOCK, BLOCK, color, cub3d);
}

bool	touch(float px, float py, t_data *cub3d)
{
	int	x;
	int	y;

	x = px / BLOCK;
	y = py / BLOCK;
	if(cub3d->map[y][x] == '1')
		return (true);
	return (false);
}

void	draw_line(t_player *player, t_data *cub3d, float start_x, int i)
{
	(void)i;
	float cos_angle = cos(start_x);
	float sin_angle = sin(start_x);
	float ray_x = player->x;
	float ray_y = player->y;

	while(!touch(ray_x, ray_y, cub3d))
	{
		put_pixel(ray_x, ray_y, RED, cub3d); //this line handles rays
		ray_x += cos_angle;
		ray_y += sin_angle;
	}

	//this part handles 1st-person perspective
	float dist = fixed_dist(player->x, player->y, ray_x, ray_y, cub3d); //fix fish-eye
	//float dist = distance(ray_x - player->x, ray_y - player->y); //fish-eye
	float height = (BLOCK / dist) * (WID / 2);
	int start_y = (HEI - height) / 2;
	int end = start_y + height;

	int color = GRE;
	// if (cos_angle > 0) // Wall facing right
	// 	color = (color >> 1) & 0x7F7F7F; // Darken the color
	// else if (cos_angle < 0) // Wall facing left
	// 	color = (color << 1) | 0x808080; // Lighten the color

	while(start_y < end)
	{
		put_pixel(i, start_y, color, cub3d);
		start_y++;
	}
}
//shading based on distance
// void	draw_line(t_player *player, t_data *cub3d, float start_x, int i)
// {
// 	(void)i;
// 	float cos_angle = cos(start_x);
// 	float sin_angle = sin(start_x);
// 	float ray_x = player->x;
// 	float ray_y = player->y;

// 	while(!touch(ray_x, ray_y, cub3d))
// 	{
// 		put_pixel(ray_x, ray_y, RED, cub3d); //this line handles rays
// 		ray_x += cos_angle;
// 		ray_y += sin_angle;
// 	}

// 	//this part handles 1st-person perspective
// 	float dist = fixed_dist(player->x, player->y, ray_x, ray_y, cub3d); //fix fish-eye
// 	//float dist = distance(ray_x - player->x, ray_y - player->y); //fish-eye
// 	float height = (BLOCK / dist) * (WID / 2);
// 	int start_y = (HEI - height) / 2;
// 	int end = start_y + height;

// 	float shading_factor = 1.0 / (1.0 + dist * 0.1);
//     if (shading_factor > 1.0)
//         shading_factor = 1.0;
//     if (shading_factor < 0.2)
//         shading_factor = 0.2;

//     // Apply shading to the color
//     int color = GRE;
//     int shaded_color = ((int)((color & 0xFF) * shading_factor) & 0xFF) |
//                       (((int)(((color >> 8) & 0xFF) * shading_factor) & 0xFF) << 8) |
//                       (((int)(((color >> 16) & 0xFF) * shading_factor) & 0xFF) << 16);

// 	while(start_y < end)
// 	{
// 		//put_pixel(i, start_y, GRE, cub3d);
// 		put_pixel(i, start_y, shaded_color, cub3d);
// 		start_y++;
// 	}
// }

float	distance(float x, float y)
{
	return (sqrt(x * x + y * y));
}

float	fixed_dist(float x1, float y1, float x2, float y2, t_data *cub3d)
{
	float delta_x = x2 - x1;
	float delta_y = y2 - y1;
	float angle = atan2(delta_y, delta_x) - cub3d->player.angle;
	float fix_dist = distance(delta_x, delta_y) * cos(angle); // the correction
	return (fix_dist);
}

void	key_hooks(t_data *cub3d)
{
	#ifdef __APPLE__
		mlx_hook(cub3d->win_ptr, KEYPRESS, 1L<<0, key_press, cub3d);
		mlx_hook(cub3d->win_ptr, KEYRELEASE, 1L<<1, key_release, cub3d);
		mlx_hook(cub3d->win_ptr, DESTROY, 0, destroy, cub3d);
	#else
		mlx_hook(cub3d->win_ptr, KeyPress, KeyPressMask, key_press, cub3d);
		mlx_hook(cub3d->win_ptr, KeyRelease, KeyReleaseMask, key_release, cub3d);
		mlx_hook(cub3d->win_ptr, DestroyNotify, StructureNotifyMask, destroy, cub3d);
	#endif
}
