/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   header_utils2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsetyamu <hsetyamu@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/14 16:31:22 by hsetyamu          #+#    #+#             */
/*   Updated: 2025/05/19 11:39:36 by hsetyamu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3d.h"

int		rgb_tocol(char *rgb_str, t_data *cub3d);
char	**split_col(char *rgb_str, t_data *cub3d);
bool	check_comma(char *str);
int		convert_col(char *component, t_data *cub3d);
bool	number_check(char *str);

/**
 * @brief Converts RGB string to color integer value
 *
 * @param rgb_str String containing RGB values (format: "R,G,B")
 * @param cub3d Main program data structure
 * @return int Color as 24-bit integer (format: 0xRRGGBB), or -1 if error
 */
int	rgb_tocol(char *rgb_str, t_data *cub3d)
{
	char	**components;
	int		r;
	int		g;
	int		b;

	components = split_col(rgb_str, cub3d);
	if (!components)
		return (-1);
	r = convert_col(components[0], cub3d);
	g = convert_col(components[1], cub3d);
	b = convert_col(components[2], cub3d);
	free_split(components);
	if (r == -1 || g == -1 || b == -1)
		return (-1);
	else
		return ((r << 16) | (g << 8) | b);
}

char	**split_col(char *rgb_str, t_data *cub3d)
{
	char	**components;

	(void)cub3d;
	if (!check_comma(rgb_str))
	{
		printf("RGB values cant be processed (sc)\n");
		return (NULL);
	}
	components = ft_split(rgb_str, ',');
	if (!components)
		return (NULL);
	return (components);
}

bool	check_comma(char *rgb_str)
{
	int	i;
	int	comma_counter;

	i = 0;
	comma_counter = 0;
	while (rgb_str[i])
	{
		if (rgb_str[i] == ',')
			comma_counter++;
		i++;
	}
	if (comma_counter == 2)
		return (1);
	else
		return (0); 
}

/**
 * @brief Validates a single color component
 *
 * @param component String containing a single color value
 * @param cub3d Main program data structure
 * @return int Validated color component value (0-255)
 * @note Terminates program if value is invalid
 */
int	convert_col(char *component, t_data *cub3d)
{
	int		val;
	char	*trimmed;

	(void)cub3d;
	trimmed = trim_string(component);
	//printf("convert_col %s\n", trimmed);
	if (!number_check(trimmed))
	{
		printf("Invalid color value: RGB values cant be processed (cc)\n");
		return (-1);
	}
	val = ft_atoi(component);
	if (val < 0 || val > 255)
	{
		printf(
			"Invalid color value: RGB values not between 0 and 255 (cc)\n"
			);
		return (-1);
	}
	return (val);
}

/**
 * Checks if a string contains only numeric digits.
 *
 * @param str The string to be checked
 * @return Returns true if the string contains only digits (0-9),
 *         false otherwise. An empty string is considered valid.
 *
 * The function iterates through each character of the string and
 * uses ft_isdigit to verify if it's a numeric digit. It stops and
 * returns false at the first non-digit character encountered.
 */
bool	number_check(char *str)
{
	int		i;

	i = 0;
	if (!str || !str[0])
		return (false);
	while (str[i])
	{
		if (!ft_isdigit(str[i]))
			return (false);
		i++;
	}
	return (true);
}
