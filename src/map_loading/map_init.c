/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_init.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsetyamu <hsetyamu@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/13 13:40:01 by reldahli          #+#    #+#             */
/*   Updated: 2025/05/06 18:43:12 by hsetyamu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3d.h"

void	init_map(t_data *cub3d, char *argv);
void	init_struct(t_data *cub3d);

void	init_map(t_data *cub3d, char *argv)
{
	init_struct(cub3d);
	read_header(cub3d, argv);
	if (header_complete(cub3d) != 1)
		err_msg(cub3d, "Error\nIncomplete header.");
	read_content(cub3d, argv);
	// printf("NO: %s\n", cub3d->map_info.no_tex);
	// printf("SO: %s\n", cub3d->map_info.so_tex);
	// printf("EA: %s\n", cub3d->map_info.ea_tex);
	// printf("WE: %s\n", cub3d->map_info.we_tex);
	// printf("FL: %s\n", cub3d->map_info.fl_col);
	// printf("CE: %s\n", cub3d->map_info.ce_col);
	// int i = 0;
	// while (cub3d->map_info.map[i] != NULL) //map is a 2D array that stores the map data
	// {
	// 	printf("Row %2d: [%s]\n", i, cub3d->map_info.map[i]);
	// 	i++;
	// }
	// printf("# of rows in map = %d\n", cub3d->map_info.map_rows);
	// printf("# of cols in map = %d\n", cub3d->map_info.map_cols);
}

void	init_struct(t_data *cub3d) //initialize the map_info struct
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
