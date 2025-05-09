/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleaning.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsetyamu <hsetyamu@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/09 17:38:57 by hsetyamu          #+#    #+#             */
/*   Updated: 2025/05/09 19:24:51 by hsetyamu         ###   ########.fr       */
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
