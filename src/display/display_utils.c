/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsetyamu <hsetyamu@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/06 19:26:00 by hsetyamu          #+#    #+#             */
/*   Updated: 2025/05/14 16:48:15 by hsetyamu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3d.h"

void	put_pixel(int x, int y, int color, t_data *cub3d);
void	clear_image(t_data *cub3d);
void	define_raydir(t_data *cub3d, float cam_x, float *ray_dirx,
			float *ray_diry);
bool	number_check(char *str);
char	*trim_string(char *str);

/**
 * @brief Puts a pixel of specified color at given coordinates in the window
 *
 * This function writes a single pixel with the specified RGB color to the
 * display buffer at the given (x,y) coordinates. It performs bounds checking
 * to ensure the coordinates are within the window dimensions.
 *
 * @param x The x coordinate of the pixel (must be within window width)
 * @param y The y coordinate of the pixel (must be within window height)
 * @param color The RGB color value to set (24-bit format)
 * @param cub3d Pointer to the main data structure containing display
 * 				information
 *
 * @return void
 * @note Color is written in BGR format in memory (little endian)
 */
void	put_pixel(int x, int y, int color, t_data *cub3d)
{
	int	idx;

	if (x >= WID || y >= HEI || x < 0 || y < 0)
		return ;
	idx = y * cub3d->line_len + x * cub3d->bpp / 8;
	cub3d->addr[idx] = color & 0xFF;
	cub3d->addr[idx + 1] = (color >> 8) & 0xFF;
	cub3d->addr[idx + 2] = (color >> 16) & 0xFF;
}

/**
 * @brief Clears the entire image by setting all pixels to black
 *
 * This function iterates through each pixel in the image defined by WID and HEI
 * constants & sets each pixel to color value 0 (black) using put_pixel function
 *
 * @param cub3d Pointer to the main data structure containing image information
 * @return void
 */
void	clear_image(t_data *cub3d)
{
	int	x;
	int	y;

	y = 0;
	while (y < HEI)
	{
		x = 0;
		while (x < WID)
		{
			put_pixel(x, y, 0, cub3d);
			x++;
		}
		y++;
	}
}

/**
 * Calculates ray direction vector components for raycasting
 * based on player angle and camera position
 *
 * @param cub3d    Main game data structure containing player info
 * @param cam_x    Camera x position in screen space (-1 to 1)
 * @param ray_dirx Pointer to store calculated x component of ray direction
 * @param ray_diry Pointer to store calculated y component of ray direction
 *
 * The function:
 * 1. Calculates direction vector from player angle
 * 2. Computes camera plane vector perpendicular to direction
 * 3. Determines final ray direction by combining direction and plane vectors
 *
 * Uses 0.66 as camera plane length for ~66° FOV
 */
void	define_raydir(t_data *cub3d, float cam_x, float *ray_dirx,
			float *ray_diry)
{
	float	dir_x;
	float	dir_y;
	float	plane_x;
	float	plane_y;

	dir_x = cos(cub3d->player.angle);
	dir_y = sin(cub3d->player.angle);
	plane_x = -dir_y * FOV;
	plane_y = dir_x * FOV;
	*ray_dirx = dir_x + plane_x * cam_x;
	*ray_diry = dir_y + plane_y * cam_x;
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
// bool	number_check(char *str)
// {
// 	int		i;
// 	bool	is_valid;

// 	i = 0;
// 	is_valid = true;
// 	while (str[i])
// 	{
// 		if (!ft_isdigit(str[i]))
// 		{
// 			is_valid = false;
// 			return (is_valid);
// 		}
// 		i++;
// 	}
// 	return (is_valid);
// }

/**
 * Removes leading and trailing whitespace from a string
 *
 * The function modifies the input string by advancing the pointer past leading
 * whitespace and adding a null terminator after the last non-whitespace
 * character. The internal whitespace is preserved.
 *
 * @param str The string to be trimmed
 * @return A pointer to the first non-whitespace character in the trimmed string
 *			If the string contains only whitespace, returns pointer to null
 * 			terminator
 *
 * @note This function modifies the original string
 * @note The function depends on ft_isspace() and ft_strlen() functions
 */
/* char	*trim_string(char *str)
{
	char	*end;

	while (ft_isspace(*str))
		str++;
	if (*str == 0)
		return (str);
	end = str + ft_strlen(str) - 1;
	while (end > str && ft_isspace(*end))
		end--;
	end[1] = '\0';
	return (str);
} */
char *trim_string(char *str)
{
    static char trimmed[256]; // Static buffer for the result
    int i = 0, j = 0;
    bool previous_was_comma = false;
    
    // Skip leading spaces
    while (str[i] && ft_isspace(str[i]))
        i++;
    
    // Process the string
    while (str[i] && j < 255)
    {
        if (ft_isdigit(str[i])) {
            trimmed[j++] = str[i];
            previous_was_comma = false;
        }
        else if (str[i] == ',') {
            trimmed[j++] = str[i];
            previous_was_comma = true;
        }
        else if (ft_isspace(str[i]) && !previous_was_comma) {
            // Skip spaces that are not after a comma
            // (spaces after commas will be eliminated by the loop)
        }
        else {
            // Invalid character
            trimmed[j] = '\0';
            return trimmed;
        }
        i++;
    }
    
    trimmed[j] = '\0';
    return trimmed;
}
