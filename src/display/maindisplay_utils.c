/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   maindisplay_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsetyamu <hsetyamu@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/07 22:37:49 by hsetyamu          #+#    #+#             */
/*   Updated: 2025/05/13 15:54:39 by hsetyamu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3d.h"

bool	valid_colformat(char *str);
char	**split_col(char *rgb_str, t_data *cub3d);
int		rgb_tocol(char *rgb_str, t_data *cub3d);
int		validate_col(char *component, t_data *cub3d);

/**
 * @brief Validates if a string contains valid color format (digits, commas and
 * spaces only)
 *
 * @param str String to validate
 * @return true if format is valid (contains exactly 2 commas and only allowed
 * characters)
 * @return false if format is invalid
 */
bool	valid_colformat(char *str)
{
	int	i;
	int	comma_count;

	i = 0;
	comma_count = 0;
	while (str[i])
	{
		if (str[i] == ',')
			comma_count++;
		else if (!ft_isdigit(str[i]) && !ft_isspace(str[i]))
			return (false);
		i++;
	}
	return (comma_count == 2);
}

/**
 * @brief Splits an RGB color string into its components
 *
 * @param rgb_str String containing RGB values separated by commas
 * @param cub3d Main program data structure
 * @return char** Array of strings containing R,G,B components, or NULL if error
 */
char	**split_col(char *rgb_str, t_data *cub3d)
{
	char	**components;
	int		i;

	rgb_str = trim_string(rgb_str);
	if (!valid_colformat(rgb_str))
		terminate(cub3d, "Error\nOnly digits, commas, and spaces are allowed", true);
	components = ft_split(trim_string(rgb_str), ',');
	if (!components)
		return (NULL);
	i = 0;
	while (components[i])
		i++;
	if (i != 3)
	{
		i = 0;
		while (components[i])
			free(components[i++]);
		free(components);
		return (NULL);
	}
	return (components);
}

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
	int		i;
	int		r;
	int		g;
	int		b;

	components = split_col(rgb_str, cub3d);
	if (!components)
		return (-1);
	r = validate_col(components[0], cub3d);
	g = validate_col(components[1], cub3d);
	b = validate_col(components[2], cub3d);
	i = 0;
	while (components[i])
		free(components[i++]);
	free(components);
	return ((r << 16) | (g << 8) | b);
}

/**
 * @brief Validates a single color component
 *
 * @param component String containing a single color value
 * @param cub3d Main program data structure
 * @return int Validated color component value (0-255)
 * @note Terminates program if value is invalid
 */
int	validate_col(char *component, t_data *cub3d)
{
	int	val;

	if (!number_check(component))
		terminate(cub3d,
			"Error\nInvalid color value: RGB values must be digits", false);
	val = ft_atoi(component);
	if (val < 0 || val > 255)
		terminate(cub3d, "Error\nRGB values must be between 0 and 255", false);
	return (val);
}
