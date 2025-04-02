/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_header.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: reldahli <reldahli@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/13 13:35:42 by reldahli          #+#    #+#             */
/*   Updated: 2025/03/13 13:39:45 by reldahli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3d.h"

void	read_header(t_data *cub3d, char *cub_file);
int		check_header(char *line);
int		get_col(t_data *cub3d, char *line, char **col_field, char *code);
int		get_tex(t_data *cub3d, char *line, char **tex_field, char *code);
void	load_header(t_data *cub3d, char *line);
int		header_complete(t_data *cub3d);
char	*get_comppath(char *line);
int		verify_file(char *complete_path);

/**
 * @brief Reads and processes the header section of a map file
 *
 * This function opens the specified .cub file and reads it line by line,
 * processing header information. For each line that is identified as a header
 * (via check_header()), the information is loaded into the cub3d data structure.
 * The function handles file opening/closing and
 * memory management for read lines.
 *
 * @param cub3d Pointer to the main data structure to store map information
 * @param cub_file Path to the .cub map file to read from
 *
 * @note Prints an error message if the file cannot be opened
 */
void	read_header(t_data *cub3d, char *cub_file)
{
	int		file;
	char	*line;

	file = open(cub_file, O_RDONLY);
	if (file == -1)
		perror("Map opening failed.");
	line = get_next_line(file);
	while (line)
	{
		if (check_header(line))
			load_header(cub3d, line);
		free(line);
		line = get_next_line(file);
	}
	close(file);
	free(line);
}

/**
 * @brief Checks if a line contains valid map header identifiers.
 *
 * This function determines if the provided line starts with one of the
 * recognized map header identifiers:
 * - "NO " (North texture)
 * - "SO " (South texture)
 * - "EA " (East texture)
 * - "WE " (West texture)
 * - "F " (Floor color)
 * - "C " (Ceiling color)
 *
 * @param line The string to check for header identifiers
 * @return int Returns 1 if line starts with a
 * valid header identifier, 0 otherwise
 */
int	check_header(char *line)
{
	if (ft_strncmp(line, "NO ", 3) == 0
		|| ft_strncmp(line, "SO ", 3) == 0
		|| ft_strncmp(line, "EA ", 3) == 0
		|| ft_strncmp(line, "WE ", 3) == 0
		|| ft_strncmp(line, "F ", 2) == 0
		|| ft_strncmp(line, "C ", 2) == 0)
		return (1);
	return (0);
}

/**
 * @brief Handles loading texture paths for walls
 *
 * @param cub3d Main data structure
 * @param line Current line being processed
 * @param texture_type Type of texture (NO, SO, EA, WE)
 * @param texture_field Pointer to the texture field in map_info
 * @return 1 if successful, 0 otherwise
 */
int	get_tex(t_data *cub3d, char *line, char **tex_field, char *code)
{
	char	*complete_path;

	if (*tex_field != NULL)
	{
		printf("%s\n", code);
		err_msg(cub3d, "Error\nRefilling texture");
		return (0);
	}
	complete_path = get_comppath(line);
	if (verify_file(complete_path))
	{
		*tex_field = ft_strdup(line);
		free(complete_path);
		return (1);
	}
	free(complete_path);
	return (0);
}

/**
 * @brief Handles loading color information
 *
 * @param cub3d Main data structure
 * @param line Current line being processed
 * @param color_field Pointer to the color field in map_info
 * @param color_type Type of color (F or C)
 * @return 1 if successful, 0 otherwise
 */
int	get_col(t_data *cub3d, char *line, char **col_field, char *code)
{
	if (*col_field != NULL)
	{
		printf("%s\n", code);
		err_msg(cub3d, "Error\nRefilling color");
		return (0);
	}
	*col_field = ft_strdup(line);
	return (1);
}

/**
 * @brief Processes map header information from a line of text
 *
 * This function parses a line from the map file and loads texture paths
 * or color definitions into the game data structure.
 *
 * @param cub3d Pointer to the main data structure
 * @param line The line of text to process from the map file
 */
void	load_header(t_data *cub3d, char *line)
{
	if (ft_strncmp(line, "NO ", 3) == 0)
		get_tex(cub3d, line, &cub3d->map_info.no_tex, "NO");
	else if (ft_strncmp(line, "SO ", 3) == 0)
		get_tex(cub3d, line, &cub3d->map_info.so_tex, "SO");
	else if (ft_strncmp(line, "EA ", 3) == 0)
		get_tex(cub3d, line, &cub3d->map_info.ea_tex, "EA");
	else if (ft_strncmp(line, "WE ", 3) == 0)
		get_tex(cub3d, line, &cub3d->map_info.we_tex, "WE");
	else if (ft_strncmp(line, "F ", 2) == 0)
		get_col(cub3d, line, &cub3d->map_info.fl_col, "F");
	else if (ft_strncmp(line, "C ", 2) == 0)
		get_col(cub3d, line, &cub3d->map_info.ce_col, "C");
}

/**
 * @brief Checks if all required map header information is complete
 *
 * This function verifies that all necessary texture paths and color
 * information have been set in the map header. Specifically, it checks
 * that north (NO), south (SO), east (EA), and west (WE) textures,
 * as well as floor (FL) and ceiling (CE) colors are all defined.
 *
 * @param cub3d Pointer to the main data structure containing map information
 * @return 1 if all required header elements are present, 0 otherwise
 */
int	header_complete(t_data *cub3d)
{
	if (cub3d->map_info.no_tex != NULL
		&& cub3d->map_info.so_tex != NULL
		&& cub3d->map_info.ea_tex != NULL
		&& cub3d->map_info.we_tex != NULL
		&& cub3d->map_info.fl_col != NULL
		&& cub3d->map_info.ce_col != NULL)
		return (1);
	return (0);
}

/**
 * @brief Extracts the complete path from a line of text.
 *
 * This function parses a line to extract a path. It works as follows:
 * 1. Skips the initial part of the line until it finds a space
 * 2. Skips any spaces or tabs
 * 3. Captures the remaining content until newline or carriage return
 *
 * @param line The input line containing a path to extract
 * @return A newly allocated string with the extracted path,
 *         or NULL if allocation fails
 *
 * @note The caller is responsible for freeing the returned string
 */
char	*get_comppath(char *line)
{
	/* int	len;
	char	*complete_path;

	len = ft_strlen(line);
	complete_path = ft_substr(line, 3, len);
	return (complete_path); */
	int		i;
	int		start;
	char	*complete_path;

	i = 0;
	while (line[i] && line[i] != ' ')
		i++;
	while (line[i] && (line[i] == ' ' || line[i] == '\t'))
		i++;
	start = i;
	while (line[i] && line[i] != '\n' && line[i] != '\r')
		i++;
	complete_path = ft_substr(line, start, i - start);
	return (complete_path);
}

/**
 * @brief Verifies if a file exists and is readable
 *
 * This function attempts to open the provided file path in read-only mode
 * to check if the file exists and is accessible for reading.
 *
 * @param complete_path The full path to the file to verify
 * @return 1 if the file exists and is readable, 0 otherwise
 * @note If the file cannot be opened, an error message is printed to stdout
 */
int	verify_file(char *complete_path)
{
	int		file;

	file = open(complete_path, O_RDONLY);
	if (file == -1)
	{
		close(file);
		printf("File: %s\n", complete_path);
		perror("File can't be found.");
		return (0);
	}
	else
	{
		close(file);
		return (1);
	}
}
