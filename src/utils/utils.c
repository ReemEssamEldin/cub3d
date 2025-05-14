/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsetyamu <hsetyamu@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/13 13:41:19 by reldahli          #+#    #+#             */
/*   Updated: 2025/05/14 16:01:57 by hsetyamu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3d.h"

int		destroy(t_data *cub3d);
void	terminate(t_data *cub3d, char *msg);
char	*remove_trailing(char *str, char *c);

/**
 * @brief Clean up resources and exit the program
 *
 * Performs cleanup operations in the following order:
 * 1. If BONUS is enabled, stops audio playback
 * 2. Cleans up all allocated resources via clean_all()
 * 3. Destroys MLX image if it exists
 * 4. Destroys MLX window if it exists
 * 5. Destroys MLX display and frees MLX pointer if it exists
 * 6. Exits program with status code 0
 *
 * @param cub3d Pointer to main program data structure
 * @return Always returns 0 (though function exits before return)
 */
int	destroy(t_data *cub3d)
{
	if (BONUS)
		end_audio();
	clean_all(cub3d);
	if (cub3d->img_ptr)
		mlx_destroy_image(cub3d->mlx_ptr, cub3d->img_ptr);
	if (cub3d->win_ptr)
		mlx_destroy_window(cub3d->mlx_ptr, cub3d->win_ptr);
	if (cub3d->mlx_ptr)
	{
		mlx_destroy_display(cub3d->mlx_ptr);
		free(cub3d->mlx_ptr);
	}
	exit(0);
}

/**
 * @brief Terminates the program with an error message and cleans up resources
 *
 * This function prints an error message, frees allocated memory for map data
 * structures if they exist, and exits the program with failure status.
 *
 * @param cub3d Pointer to main program data structure, can be NULL
 * @param msg Error message string to display before terminating
 */
void	terminate(t_data *cub3d, char *msg)
{
	printf("%s", msg);
	// if (flag)
	// {
	// 	destroy(cub3d);
	// 	exit(EXIT_FAILURE);
	// }
	if (cub3d)
	{
		clean_mapheader(&cub3d->map_info);
		clean_mapcontent(&cub3d->map_info);
		exit(EXIT_FAILURE);
	}
	// exit(EXIT_FAILURE);
}

/**
 * Removes trailing characters specified in 'c' from the end of a string
 *
 * @param str The string to be modified
 * @param c String containing characters to be removed from the end
 * @return The modified string with trailing characters removed
 *
 * This function removes any trailing characters that match those in 'c'
 * from the end of 'str'. It modifies the original string by replacing
 * matching characters with null terminators.
 */
char	*remove_trailing(char *str, char *c)
{
	int	len;

	len = ft_strlen(str);
	while (len > 0 && ft_strchr(c, str[len - 1]) != NULL)
	{
		str[len - 1] = '\0';
		len--;
	}
	return (str);
}
