#include "cub3d.h"

// ----------------------------------------------------------------------
// void	init_cub3d(t_data *cub3d);
// void	init_mlx(t_data *cub3d);
// void	init_player(t_player *player);
// //char	**init_map(void);
// ----------------------------------------------------------------------
// int		destroy(t_data *cub3d);
// void	clear_image(t_data *cub3d);
// ----------------------------------------------------------------------
// bool	touch(float px, float py, t_data *cub3d);
// float	distance(float x, float y);
// float	fixed_dist(float x1, float y1, float x2, float y2, t_data *cub3d);
// ----------------------------------------------------------------------
// void	check_args(int argc, char *argv);
// ----------------------------------------------------------------------

int	main(int argc, char *argv[])
{
	t_data	cub3d;

	check_args(argc, argv[1]);
	init_map(&cub3d, argv[1]);

	char	*audio_file;
	audio_file = "assets/audio/mixkit-game-level-music-689.wav";
	play_audio(audio_file);

	init_cub3d(&cub3d);
	init_player(&cub3d.player);
	init_mlx(&cub3d);

	key_hooks(&cub3d);

	mlx_loop_hook(cub3d.mlx_ptr, draw_loop, &cub3d);
	mlx_loop(cub3d.mlx_ptr);

	clean_mapheader(&cub3d.map_info);
	clean_mapcontent(&cub3d.map_info);
	return (0);
}

void	check_args(int argc, char *argv)
{
	int		fd;
	int		i;
	int		j;

	if (argc != 2)
		err_msg(NULL, "Error\nInvalid number of arguments.");
	fd = open(argv, O_RDONLY);
	if (fd == -1)
		err_msg(NULL, "Error\nFile does not exist.");
	close(fd);
	i = ft_strlen(argv) - 4;
	j = ft_strncmp(".cub", &argv[i], 4);
	if (j != 0)
		err_msg(NULL, "Error\nOnly accepts .cub files.");
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

int	destroy(t_data *cub3d)
{
	if (cub3d->img_ptr)
		mlx_destroy_image(cub3d->mlx_ptr, cub3d->img_ptr);
	if (cub3d->win_ptr)
		mlx_destroy_window(cub3d->mlx_ptr, cub3d->win_ptr);
	if (cub3d->mlx_ptr)
	{
		mlx_destroy_display(cub3d->mlx_ptr);
		free(cub3d->mlx_ptr);
	}
	clean_mapheader(&cub3d->map_info);
	clean_mapcontent(&cub3d->map_info);
	end_audio();
	exit(0);
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

void	clear_image(t_data *cub3d)
{
	for(int y = 0; y < HEI; y++)
		for(int x = 0; x < WID; x++)
			put_pixel(x, y, 0, cub3d);
}

bool	touch(float px, float py, t_data *cub3d)
{
	int	x;
	int	y;

	x = px / BLOCK;
	y = py / BLOCK;
	if(cub3d->map_info.map[y][x] == '1')
		return (true);
	return (false);
}

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

