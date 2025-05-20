/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: reldahli <reldahli@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/13 13:20:45 by reldahli          #+#    #+#             */
/*   Updated: 2025/05/20 14:47:29 by reldahli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3d.h"

void	init_mlx(t_data *cub3d);
void	load_multitexs(t_data *cub3d);
int		load_singletex(t_data *cub3d, char *tex_path, int tex_idx);
void	init_player(t_data *cub3d);

/**
 * Initialize MLX (graphics library) and create window
 * Sets up the graphical environment for the game
 *
 * @param cub3d Pointer to main data structure containing MLX-related variables
 *
 * The function:
 * - Initializes MLX connection
 * - Creates a new window of size WID x HEI titled "Cub3D"
 * - Creates a new image for double buffering
 * - Gets the image data address and info (bits per pixel, line length, endian)
 * - Loads multiple textures needed for the game
 *
 * @note Terminates program with message if MLX init or window creation fails
 */
void	init_mlx(t_data *cub3d)
{
	cub3d->mlx_ptr = NULL;
	cub3d->win_ptr = NULL;
	cub3d->img_ptr = NULL;
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

void	load_multitexs(t_data *cub3d)
{
	if (!load_singletex(cub3d, cub3d->map_info.no_tex, 0))
		terminate(cub3d, "Error\nFailed to load north texture");
	if (!load_singletex(cub3d, cub3d->map_info.so_tex, 1))
		terminate(cub3d, "Error\nFailed to load south texture");
	if (!load_singletex(cub3d, cub3d->map_info.ea_tex, 2))
		terminate(cub3d, "Error\nFailed to load east texture");
	if (!load_singletex(cub3d, cub3d->map_info.we_tex, 3))
		terminate(cub3d, "Error\nFailed to load west texture");
}

int	load_singletex(t_data *cub3d, char *tex_path, int tex_idx)
{
	int	width;
	int	height;

	cub3d->textures[tex_idx].img = mlx_xpm_file_to_image(cub3d->mlx_ptr,
			tex_path, &width, &height);
	if (!cub3d->textures[tex_idx].img)
		return (0);
	cub3d->textures[tex_idx].addr = mlx_get_data_addr(
			cub3d->textures[tex_idx].img,
			&cub3d->textures[tex_idx].bpp,
			&cub3d->textures[tex_idx].line_len,
			&cub3d->textures[tex_idx].endian);
	cub3d->textures[tex_idx].width = width;
	cub3d->textures[tex_idx].height = height;
	return (1);
}

/**
 * @brief Initialize player data structure
 *
 * Sets up initial player state including position and movement flags.
 * Verifies valid player position & initializes movement control flags to false.
 *
 * @param cub3d Pointer to main game data structure
 * @throws Terminates program with error if player position is invalid/missing
 */
void	init_player(t_data *cub3d)
{
	if (!put_player(cub3d))
		terminate(cub3d, "Error\nPlayer position (missing/duplicate) (pp)");
	cub3d->player.key_up = false;
	cub3d->player.key_down = false;
	cub3d->player.key_right = false;
	cub3d->player.key_left = false;
	cub3d->player.left_rotate = false;
	cub3d->player.right_rotate = false;
}
