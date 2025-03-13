/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: reldahli <reldahli@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/13 13:41:51 by reldahli          #+#    #+#             */
/*   Updated: 2025/03/13 13:41:52 by reldahli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

int	main(int argc, char *argv[])
{
	t_data	cub3d;
	char	*audio_file;

	check_args(argc, argv[1]);
	init_map(&cub3d, argv[1]);
	//audio_file = "assets/audio/mixkit-game-level-music-689.wav";
	audio_file = "assets/audio/horror-background-tension-build-up-254933.wav";
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
