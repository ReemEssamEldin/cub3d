/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_floceil.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: reldahli <reldahli@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/12 16:23:05 by hsetyamu          #+#    #+#             */
/*   Updated: 2025/05/07 16:07:31 by reldahli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3d.h"

bool	is_valid_rgb_format(char *str)
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

char *trim_string(char *str)
{
	char *end;

	while (ft_isspace(*str))
		str++;

	if (*str == 0)
		return str;

	end = str + ft_strlen(str) - 1;
	while (end > str && ft_isspace(*end))
		end--;

	end[1] = '\0';
	return str;
}


/**
 * @brief Converts RGB string to color integer
 *
 * Parses a string in format "R,G,B" or "F R,G,B" or "C R,G,B" and
 * converts to a color integer suitable for MLX functions.
 *
 * @param rgb_str The RGB string to convert
 * @return int The color as an integer (0xRRGGBB), or -1 if invalid
 */
int	rgb_tocol(char *rgb_str, t_data *cub3d)
{
	char	**components;
	int		i;
	int		r;
	int		g;
	int		b;

	rgb_str = trim_string(rgb_str);
	if (!is_valid_rgb_format(rgb_str))
		err_msg(cub3d, "Error\nInvalid RGB format: Only digits, commas, and spaces are allowed");

	components = ft_split(trim_string(rgb_str), ',');
	if (!components)
		return (-1);
	i = 0;
	while (components[i])
		i++;
	if (i != 3)
	{
		i = 0;
		while (components[i])
			free(components[i++]);
		free(components);
		return (-1);
	}
	r = validate_col(components[0], cub3d);
	g = validate_col(components[1], cub3d);
	b = validate_col(components[2], cub3d);
	i = 0;
	while (components[i])
		free(components[i++]);
	free(components);
	return ((r << 16) | (g << 8) | b);
}

int	validate_col(char *component, t_data *cub3d)
{
	int val;

	if (!number_check(component))
		err_msg(cub3d, "Error\nInvalid color value: RGB values must be digits");
	val = ft_atoi(component);
	if (val < 0 || val > 255)
		err_msg(cub3d, "Error\nInvalid color value: RGB values must be between 0 and 255");
	return (val);
}

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

