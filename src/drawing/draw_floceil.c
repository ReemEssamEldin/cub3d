/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_floceil.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsetyamu <hsetyamu@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/12 16:23:05 by hsetyamu          #+#    #+#             */
/*   Updated: 2025/05/02 16:51:23 by hsetyamu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3d.h"

/**
 * @brief Converts RGB string to color integer
 * 
 * Parses a string in format "R,G,B" or "F R,G,B" or "C R,G,B" and 
 * converts to a color integer suitable for MLX functions.
 * 
 * @param rgb_str The RGB string to convert
 * @return int The color as an integer (0xRRGGBB), or -1 if invalid
 */
int rgb_to_colour(char *rgb_str)
{
	char **components;
	int r, g, b;
	
	components = ft_split(rgb_str, ',');
	if (!components)
		return (-1);
	int i = 0;
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
	if (!number_check(components[0]))
	{
		r = ft_atoi(components[0]);
		if (r < 0 || r > 255)
		{
			//err_msg(NULL, "Error\nInvalid color value: %s", components[0]);
			printf("Error\nInvalid color value: %s", components[0]);
			exit (-1);
		}
	}
		else
	{
		//err_msg(NULL, "Error\nInvalid color value: %s", components[0]);
		printf("Error\nInvalid color value: %s", components[0]);
		exit (-1);
	}
	if (!number_check(components[1]))
	{
		g = ft_atoi(components[1]);
		if (g < 0 || g > 255)
		{
			//err_msg(NULL, "Error\nInvalid color value: %s", components[1]);
			printf("Error\nInvalid color value: %s", components[1]);
			exit (-1);
		}
	}
	else
	{
		//err_msg(NULL, "Error\nInvalid color value: %s", components[1]);
		printf("Error\nInvalid color value: %s", components[1]);
		exit (-1);
	}
	if (!number_check(components[2]))
	{
		b = ft_atoi(components[2]);
		if (b < 0 || b > 255)
		{
			//err_msg(NULL, "Error\nInvalid color value: %s", components[2]);
			printf("Error\nInvalid color value: %s", components[2]);
			exit (-1);
		}
	}
	else
	{
		//err_msg(NULL, "Error\nInvalid color value: %s", components[2]);
		printf("Error\nInvalid color value: %s", components[2]);
		exit (-1);
	}	
	i = 0;
	while (components[i])
		free(components[i++]);
	free(components);
/* 	if (r < 0 || r > 255 || g < 0 || g > 255 || b < 0 || b > 255)
		return (-1); */
	return ((r << 16) | (g << 8) | b);
}

bool	number_check(char *str)
{
	int		i;
	bool	f_invalid;

	i = 0;
	f_invalid = true;
	while (str[i])
	{
		if (ft_isdigit(str[i]) == 1)
		{
			f_invalid = false;
			return (f_invalid);
		}
		i++;
	}
	return (f_invalid);
}