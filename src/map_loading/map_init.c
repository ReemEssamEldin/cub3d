/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_init.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsetyamu <hsetyamu@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/13 13:40:01 by reldahli          #+#    #+#             */
/*   Updated: 2025/05/07 21:54:56 by hsetyamu         ###   ########.fr       */
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
