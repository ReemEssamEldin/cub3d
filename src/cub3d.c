/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsetyamu <hsetyamu@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/13 13:41:51 by reldahli          #+#    #+#             */
/*   Updated: 2025/05/14 16:02:20 by hsetyamu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

int	main(int argc, char *argv[])
{
	t_data	cub3d;

	check_args(argc, argv[1]);
	init_map(&cub3d, argv[1]);
	init_player(&cub3d);
	if (BONUS)
		play_audio(AUDIO_FILE);
	init_mlx(&cub3d);
	key_hooks(&cub3d);
	mlx_loop_hook(cub3d.mlx_ptr, render, &cub3d);
	mlx_loop(cub3d.mlx_ptr);
	destroy(&cub3d);
	return (0);
}

void	check_args(int argc, char *argv)
{
	int		fd;
	int		i;
	int		j;

	if (argc != 2)
		terminate(NULL, "Error\nInvalid number of arguments.");
	fd = open(argv, O_RDONLY);
	if (fd == -1)
		terminate(NULL, "Error\nFile does not exist.");
	close(fd);
	i = ft_strlen(argv) - 4;
	j = ft_strncmp(".cub", &argv[i], 4);
	if (j != 0)
		terminate(NULL, "Error\nOnly accepts .cub files.");
}
