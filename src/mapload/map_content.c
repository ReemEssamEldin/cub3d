/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_content.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsetyamu <hsetyamu@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/13 13:25:08 by reldahli          #+#    #+#             */
/*   Updated: 2025/05/14 15:00:27 by hsetyamu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3d.h"

/**
 * @brief Reads and processes the map content from a file
 *
 * This function reads a map file, allocates memory for the map grid,
 * populates the grid with the file's content. It uses check_grid to determine
 * the number of rows in the map and save_grid to populate the map array
 * and determine the number of columns.
 *
 * @param cub3d  Pointer to the main data structure containing map information
 * @param cub_file  Path to the map file to be read
 *
 * @note The function will print an error message if memory allocation fails
 */
void	read_content(t_data *cub3d, char *cub_file)
{
	cub3d->map_info.map_rows = check_grid(cub3d, cub_file);
	cub3d->map_info.map = malloc((cub3d->map_info.map_rows + 1) \
	* sizeof(char *));
	if (!cub3d->map_info.map)
		perror("Map allocation failed");
	cub3d->map_info.map_cols = save_grid(cub3d, cub_file);
	if (!verify_boundaries(cub3d))
		terminate(cub3d, "Error\nMap is not enclosed by walls", false);
}

/**
 * @brief Checks the map grid in a .cub file and counts valid rows
 *
 * Validates each line of the map section, ensuring no invalid lines
 * appear after the map section begins.
 *
 * @param cub3d Pointer to the main data structure
 * @param cub_file Path to the .cub file to be checked
 * @return The number of valid map rows found, or exits on error
 */
int	check_grid(t_data *cub3d, char *cub_file)
{
	int		file;
	char	*line;
	int		rows;
	int		inside_map;

	rows = 0;
	inside_map = 0;
	file = open_mapfile(cub_file);
	line = get_next_line(file);
	while (line)
	{
		if (!process_mapline(line, &inside_map, &rows))
		{
			while (line)
			{
				free(line);
				line = get_next_line(file);
			}
			grid_cleanup(file, line, cub3d);
		}
		free(line);
		line = get_next_line(file);
	}
	close(file);
	return (rows);
}

/**
 * @brief Loads map data from a file into the cub3d structure's map grid
 *
 * Reads and processes map lines, storing valid lines in the map grid.
 * Tracks the length of the longest line to determine column count.
 *
 * @param cub3d Pointer to the main data structure
 * @param cub_file Path to the map file to read
 * @return Length of the longest line (columns) or -1 on error
 */
int	save_grid(t_data *cub3d, char *cub_file)
{
	char	*line;
	int		i;
	int		max_len;
	int		file;

	i = 0;
	max_len = 0;
	file = open_mapfile(cub_file);
	line = get_next_line(file);
	while (line)
	{
		if (valid_mapline(line))
			process_valline(cub3d, line, &i, &max_len);
		else
			free(line);
		line = get_next_line(file);
	}
	cub3d->map_info.map[i] = NULL;
	close(file);
	return (max_len);
}

/**
 * @brief Validates if a line contains valid map characters for cub3d
 *
 * This function checks if a line from the map file contains only valid
 * characters for the map representation. It skips leading whitespace and
 * returns 0 for empty lines. Valid map characters include:
 * - '0' for empty spaces
 * - '1' for walls
 * - ' ' for spaces within the map
 * - 'N', 'S', 'E', 'W' for player starting position and orientation
 *
 * @param line The string to validate as a map line
 * @return 1 if the line contains only valid map characters, 0 otherwise
 */
int	valid_mapline(char *line)
{
	int	i;

	i = 0;
	while (line[i] && (line[i] == ' ' || line[i] == '\t'))
		i++;
	if (line[i] == '\n' || line[i] == '\0')
		return (0);
	while (line[i] && line[i] != '\n')
	{
		if (line[i] != '0' && line[i] != '1' && line[i] != ' '
			&& line[i] != 'N' && line[i] != 'S' && line[i] != 'E'
			&& line[i] != 'W')
			return (0);
		i++;
	}
	return (1);
}

/**
 * @brief Validates if the map is properly enclosed by walls
 *
 * Ensures all walkable areas (empty spaces and player positions) are
 * completely surrounded by walls and not adjacent to map boundaries
 * or spaces.
 *
 * @param cub3d Pointer to the main data structure
 * @return 1 if map is valid, 0 if it has open boundaries
 */
int	verify_boundaries(t_data *cub3d)
{
	int	i;
	int	j;

	i = 0;
	while (i < cub3d->map_info.map_rows)
	{
		j = 0;
		while (j < (int)ft_strlen(cub3d->map_info.map[i]))
		{
			if (!validate_position(cub3d, i, j))
				return (0);
			j++;
		}
		i++;
	}
	return (1);
}
