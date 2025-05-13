/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   content_utils2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsetyamu <hsetyamu@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/09 15:49:44 by reldahli          #+#    #+#             */
/*   Updated: 2025/05/13 15:55:16 by hsetyamu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3d.h"

void	process_valline(t_data *cub3d, char *line, int *i, int *max_len)
{
	int	line_len;

	line = remove_trailing(line, "\n");
	cub3d->map_info.map[*i] = line;
	(*i)++;
	line_len = ft_strlen(line);
	if (*max_len < line_len)
		*max_len = line_len;
}

int	open_mapfile(char *cub_file)
{
	int	file;

	file = open(cub_file, O_RDONLY);
	if (file == -1)
		perror("Error\nMap opening failed");
	return (file);
}

int	process_mapline(char *line, int *in_map_section, int *rows)
{
	if (valid_mapline(line))
	{
		*in_map_section = 1;
		(*rows)++;
		return (1);
	}
	else if (*in_map_section)
		return (0);
	return (1);
}

void	grid_cleanup(int file, char *line, t_data *cub3d)
{
	free(line);
	close(file);
	terminate(cub3d, "Error\nNon map line (Empty line or invalid symbol", false);
}
