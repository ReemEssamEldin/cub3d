/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleaning.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsetya <hsetya@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/09 17:38:57 by hsetyamu          #+#    #+#             */
/*   Updated: 2025/05/10 00:05:09 by hsetya           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3d.h"

void	clean_all(t_data *cub3d);
void	clean_mapheader(t_map *map_info);
void	clean_mapcontent(t_map *map_info);
void	clean_textures(t_data *cub3d);

void	clean_all(t_data *cub3d)
{
	if (cub3d)
	{
		clean_mapheader(&cub3d->map_info);
		clean_mapcontent(&cub3d->map_info);
		clean_textures(cub3d);
	}
}

void	clean_mapheader(t_map *map_info)
{
	if (map_info->no_tex)
		free(map_info->no_tex);
	if (map_info->so_tex)
		free(map_info->so_tex);
	if (map_info->ea_tex)
		free(map_info->ea_tex);
	if (map_info->we_tex)
		free(map_info->we_tex);
	if (map_info->fl_col)
		free(map_info->fl_col);
	if (map_info->ce_col)
		free(map_info->ce_col);
}

/**
 * @brief Frees the memory allocated for the map content
 *
 * This function deallocates the memory used by the map array within the
 * map_info structure.
 * It first checks if the map exists, then iterates through each element,
 * freeing each row and setting it to NULL before finally freeing the map array
 * itself.
 *
 * @param map_info Pointer to the map structure containing the map to be freed
 */
void	clean_mapcontent(t_map *map_info)
{
	int	i;

	if (map_info->map == NULL)
		return ;
	i = 0;
	while (map_info->map[i] != NULL)
	{
		free(map_info->map[i]);
		map_info->map[i] = NULL;
		i++;
	}
	free(map_info->map);
}

/**
 * @brief Cleans up and destroys texture images stored in cub3d data structure
 *
 * This function iterates through the texture array and destroys each texture
 * image that has been previously loaded using the MLX library. After destroying
 * each image, it sets the corresponding image pointer to NULL to avoid dangling
 * pointers.
 *
 * @param cub3d Pointer to the main data structure containing game information
 * 				and textures
 */
void	clean_textures(t_data *cub3d)
{
	int	i;

	i = 0;
	while (i < 4)
	{
		if (cub3d->textures[i].img)
		{
			mlx_destroy_image(cub3d->mlx_ptr, cub3d->textures[i].img);
			cub3d->textures[i].img = NULL;
		}
		i++;
	}
}
