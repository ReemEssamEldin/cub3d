/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   header_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsetyamu <hsetyamu@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/13 13:35:42 by reldahli          #+#    #+#             */
/*   Updated: 2025/05/14 19:52:24 by hsetyamu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3d.h"

int		get_col(t_data *cub3d, char *line, char **col_field, char *code);
int		get_tex(t_data *cub3d, char *line, char **tex_field, char *code);
char	*get_comppath(char *line);
int		verify_file(char *complete_path);

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
		terminate(cub3d, "Error\nRefilling texture");
		return (0);
	}
	complete_path = get_comppath(line);
	if (verify_file(complete_path))
	{
		*tex_field = ft_strdup(complete_path);
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
		terminate(cub3d, "Error\nRefilling color");
		return (0);
	}
	while (*line && !ft_isdigit(*line))
		line++;
	*col_field = ft_strdup(line);
	if (ft_strncmp(code, "F", 1) == 0)
		cub3d->map_info.col_floo = rgb_tocol(*col_field, cub3d);
	else if (ft_strncmp(code, "C", 1) == 0)
		cub3d->map_info.col_ceil = rgb_tocol(*col_field, cub3d);
	return (1);
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
	char	*ext;

	file = open(complete_path, O_RDONLY);
	if (file == -1)
	{
		close(file);
		printf("File: %s\n", complete_path);
		perror("File can't be found.");
		return (0);
	}
	close(file);
	ext = ft_strrchr(complete_path, '.');
	if (!ext)
	{
		printf("Error\nFile has no extension: %s\n", complete_path);
		return (0);
	}
	if (ft_strncmp(ext, ".xpm", 4) == 0)
		return (1);
	printf("Error\nInvalid file extension: %s\n", complete_path);
	return (0);
}
