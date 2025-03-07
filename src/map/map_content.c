#include "../cub3d.h"

void	read_content(t_data *cub3d, char *cub_file);
int		check_grid(t_data *cub3d, char *cub_file);
int		save_grid(t_data *cub3d, char *cub_file);
int		valid_mapline(char *line);
int		empty_line(char *line);

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
}

/**
 * @brief Checks the map grid in a .cub file and counts valid rows
 *
 * This function reads a .cub file line by line to validate the map section.
 * It counts the number of valid map lines and ensures that once the map 
 * section begins (after finding the first valid map line), all subsequent 
 * lines are also valid map lines with no empty lines or invalid symbols.
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
	int		in_map_section;

	rows = 0;
	in_map_section = 0;
	file = open(cub_file, O_RDONLY);
	if (file == -1)
		perror("Error\nMap opening failed");
	line = get_next_line(file);
	while (line)
	{
		if (valid_mapline(line))
		{
			in_map_section = 1;
			rows++;
		}
		else if (in_map_section)
		{
			free(line);
			close(file);
			err_msg(cub3d, "Error\nNon map line (Empty line or invalid symbol");
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
 * This function reads a map file line by line, validates each line using
 * valid_mapline(), and saves valid lines to the map grid in cub3d->map_info.map.
 * It also determines the length of the longest line in the map, which is 
 * returned as the column count.
 *
 * @param cub3d Pointer to the main data structure containing map information
 * @param cub_file Path to the map file to be read
 * @return The length of the longest line in the map (number of columns)
 *         or -1 if the file could not be opened
 */
int	save_grid(t_data *cub3d, char *cub_file)
{
	int		file;
	char	*line;
	int		i;
	int		line_len;
	int		line_lentemp;

	i = 0;
	file = open(cub_file, O_RDONLY);
	if (file == -1)
		perror("Error\nMap opening failed");
	cub3d->map_info.map_cols = 0;
	line = get_next_line(file);
	line_len = 0;
	while (line)
	{
		if (valid_mapline(line))
		{
			line = remove_trailing(line, "\n");
			cub3d->map_info.map[i++] = line;
			line_lentemp = ft_strlen(line);
			if (line_len < line_lentemp)
				line_len = line_lentemp;
		}
		else
			free(line);
		line = get_next_line(file);
	}
	cub3d->map_info.map[i] = NULL;
	close(file);
	return(line_len);
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
int valid_mapline(char *line)
{
	int i = 0;
	
	i = 0;
	while (line[i] && (line[i] == ' ' || line[i] == '\t'))
		i++;
	if (line[i] == '\n' || line[i] == '\0')
		return (0);
	while (line[i] && line[i] != '\n')
	{
		if (line[i] != '0' && line[i] != '1' && line[i] != ' ' && 
			line[i] != 'N' && line[i] != 'S' && line[i] != 'E' && line[i] != 'W')
			return (0);
		i++;
	}
	return (1);
}

/**
 * @brief Checks if a line is empty or contains only whitespace characters
 *
 * This function scans through the given line and determines if it's empty.
 * A line is considered empty if it:
 * - Contains only spaces and/or tabs followed by a newline or null terminator
 * - Is just a newline or null terminator
 *
 * @param line The string to check
 * @return int 1 (true) if the line is empty, 0 (false) otherwise
 */
int empty_line(char *line)
{
	int i;

	i = 0;
	while (line[i] && (line[i] == ' ' || line[i] == '\t'))
		i++;
	return (line[i] == '\n' || line[i] == '\0');
}