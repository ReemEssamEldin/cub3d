/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   header_utils2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsetyamu <hsetyamu@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/14 16:31:22 by hsetyamu          #+#    #+#             */
/*   Updated: 2025/05/14 17:39:29 by hsetyamu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3d.h"

int		rgb_tocol(char *rgb_str, t_data *cub3d);
char	**split_col(char *rgb_str, t_data *cub3d);
bool	valid_colformat(char *str);
int		validate_col(char *component, t_data *cub3d);
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

char **split_col(char *rgb_str, t_data *cub3d)
{
	char **components;
	int i = 0;

	if (!valid_colformat(rgb_str))
		terminate(cub3d, "Error\nInvalid color format");
	char *cleaned = trim_string(rgb_str);
	printf("%s\n", cleaned);
	components = ft_split(cleaned, ',');
	if (!components)
		return (NULL);
	while (components[i])
		i++;
	if (i != 3) {
		i = 0;
		while (components[i])
			free(components[i++]);
		free(components);
		terminate(cub3d, "Error\nColor must have exactly 3 components (R,G,B)");
		return (NULL);
	}
	return (components);
}

/**
 * @brief Validates if a string contains valid color format (digits, commas and
 * spaces only)
 *
 * @param str String to validate
 * @return true if format is valid (contains exactly 2 commas and only allowed
 * characters)
 * @return false if format is invalid
 */
/* bool	valid_colformat(char *str)
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
} */

bool valid_colformat(char *str)
{
	int i = 0;
	int comma_count = 0;
	int digit_found = false;

	while (str[i] && ft_isspace(str[i]))
		i++;
	while (str[i])
	{
		if (ft_isdigit(str[i])) {
			digit_found = true;
		}
		else if (str[i] == ',') {
			if (!digit_found)
				return (false); // No digit before comma
			comma_count++;
			digit_found = false; // Reset for next component
		}
		else if (ft_isspace(str[i])) {
			int j = i;
			while (str[j] && ft_isspace(str[j]))
				j++;
			if (str[j] == ',')
				return (false);
		}
		else
			return (false); // Invalid character
		i++;
	}
	printf("%s\n", str);
	return (comma_count == 2 && digit_found);
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

	// if (!number_check(component))
	// 	terminate(cub3d,
	// 		"Error\nInvalid color value: RGB values must be digits");
	val = ft_atoi(component);
	if (val < 0 || val > 255)
		terminate(cub3d, "Error\nRGB values must be between 0 and 255");
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
	bool	is_valid;

	i = 0;
	is_valid = true;
	while (str[i])
	{
		if (!ft_isdigit(str[i]))
		{
			is_valid = false;
			return (is_valid);
		}
		i++;
	}
	return (is_valid);
}