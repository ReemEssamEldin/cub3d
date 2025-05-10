/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_init.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsetya <hsetya@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/13 13:40:01 by reldahli          #+#    #+#             */
/*   Updated: 2025/05/10 00:06:21 by hsetya           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3d.h"

void	init_map(t_data *cub3d, char *argv);
void	init_struct(t_data *cub3d);

/**
 * @brief Initializes the map structure and loads map data from file
 *
 * This function performs the complete map initialization process by:
 * 1. Initializing the main data structure
 * 2. Reading and parsing the map header
 * 3. Validating header completeness
 * 4. Reading the actual map content
 *
 * @param cub3d Pointer to the main data structure
 * @param argv Path to the map file
 *
 * @throws Terminates program with error message if header is incomplete
 */
void	init_map(t_data *cub3d, char *argv)
{
	init_struct(cub3d);
	read_header(cub3d, argv);
	if (header_complete(cub3d) != 1)
		terminate(cub3d, "Error\nIncomplete header.");
	read_content(cub3d, argv);
}

void	init_struct(t_data *cub3d)
{
	cub3d->map_info.no_tex = NULL;
	cub3d->map_info.so_tex = NULL;
	cub3d->map_info.ea_tex = NULL;
	cub3d->map_info.we_tex = NULL;
	cub3d->map_info.fl_col = NULL;
	cub3d->map_info.ce_col = NULL;
	cub3d->map_info.map = NULL;
	cub3d->map_info.map_rows = 0;
	cub3d->map_info.map_cols = 0;
}
