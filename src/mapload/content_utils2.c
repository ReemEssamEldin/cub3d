/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   content_utils2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsetyamu <hsetyamu@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/09 15:49:44 by reldahli          #+#    #+#             */
/*   Updated: 2025/05/16 12:09:57 by hsetyamu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3d.h"

int		open_mapfile(char *cub_file);
int		process_mapline(char *line, int *inside_map, int *rows);
void	process_valline(t_data *cub3d, char *line, int *i, int *max_len);
void	grid_cleanup(int file, char *line, t_data *cub3d);

int	open_mapfile(char *cub_file)
{
	int	file;

	file = open(cub_file, O_RDONLY);
	if (file == -1)
		perror("Error\nMap opening failed");
	return (file);
}

/**
 * @brief Process a line from the map file
 *
 * This function determines if a line is a valid map line.
 * If the line is valid, it updates the map section flag and row counter.
 * 
 * @param line The line to process from the map file
 * @param inside_map Pointer to flag indicating if we're in the map section
 * @param rows Pointer to the counter for map rows
 * 
 * @return 1 if processing should continue to the next line, 0 if an error 
 * occurred
 */
int	process_mapline(char *line, int *inside_map, int *rows)
{
	if (valid_mapline(line))
	{
		*inside_map = 1;
		(*rows)++;
		return (1);
	}
	else if (*inside_map)
		return (0);
	return (1);
}

/**
 * @brief Process a valid map line, store it in the map structure and 
 * update max length
 *
 * This function handles a single valid line of map data:
 * - Removes trailing newline character
 * - Stores the processed line in the map array 
 * - Increments the map line counter
 * - Updates the maximum line length if necessary
 *
 * @param cub3d Pointer to main data structure
 * @param line The map line to process
 * @param i Pointer to the current line index (incremented by function)
 * @param max_len Pointer to variable tracking maximum line length
 */
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

void	grid_cleanup(int file, char *line, t_data *cub3d)
{
	free(line);
	close(file);
	terminate(cub3d, "Error\nNon map line (Empty line or invalid symbol) (cg)");
}
