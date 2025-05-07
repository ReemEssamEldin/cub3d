/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsetyamu <hsetyamu@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: Invalid date        by                   #+#    #+#             */
/*   Updated: 2025/05/07 19:54:20 by hsetyamu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3d.h"

void ray_casting(t_data *cub3d, float camera_x, float *ray_x, float *ray_y);

/* void ray_casting(t_data *cub3d, float camera_x, float *ray_x, float *ray_y)
{
	float	ray_dir_x;
	float	ray_dir_y;
	define_raydir(cub3d, camera_x, &ray_dir_x, &ray_dir_y);

	// Ray starting position (player position)
	float pos_x = cub3d->player.x / BLOCK;
	float pos_y = cub3d->player.y / BLOCK;

	// Current map cell the ray is in
	int map_x = (int)(pos_x);
	int map_y = (int)(pos_y);
	
	// Length of ray from one x or y-side to next x or y-side
	float delta_dist_x = (ray_dir_x == 0) ? 1e30 : fabs(1 / ray_dir_x);
	float delta_dist_y = (ray_dir_y == 0) ? 1e30 : fabs(1 / ray_dir_y);
	
	// Direction to step in x or y direction (either +1 or -1)
	int step_x;
	int step_y;
	
	// Length of ray from current position to next x or y-side
	float side_dist_x;
	float side_dist_y;
	
	// Calculate step and initial side_dist
	if (ray_dir_x < 0)
	{
		step_x = -1;
		side_dist_x = (pos_x - map_x) * delta_dist_x;
	}
	else
	{
		step_x = 1;
		side_dist_x = (map_x + 1.0 - pos_x) * delta_dist_x;
	}

	if (ray_dir_y < 0)
	{
		step_y = -1;
		side_dist_y = (pos_y - map_y) * delta_dist_y;
	}
	else
	{
		step_y = 1;
		side_dist_y = (map_y + 1.0 - pos_y) * delta_dist_y;
	}

	// Perform DDA
	int hit_flag = 0;
	int side = 0;  // 0 = NS wall, 1 = EW wall
	
	while (hit_flag == 0)
	{
		// Jump to next map square, either in x-direction, or in y-direction
		if (side_dist_x < side_dist_y)
		{
			side_dist_x += delta_dist_x;
			map_x += step_x;
			side = 0;
		}
		else
		{
			side_dist_y += delta_dist_y;
			map_y += step_y;
			side = 1;
		}
		
		// Check if ray has hit a wall
		if (map_y < 0 || map_x < 0 || map_y >= cub3d->map_info.map_rows || 
			map_x >= (int)ft_strlen(cub3d->map_info.map[map_y]) || 
			cub3d->map_info.map[map_y][map_x] == '1')
		{
			hit_flag = 1;
		}
	}
	
	// Calculate exact hit position
	float wall_dist;
	if (side == 0)
		wall_dist = side_dist_x - delta_dist_x;
	else
		wall_dist = side_dist_y - delta_dist_y;

	// Calculate exact hit coordinates for minimap
	if (side == 0)
	{
		*ray_x = map_x * BLOCK;
		if (step_x > 0)
			*ray_x -= 0.001; // Adjust for edge case
		*ray_y = (pos_y + wall_dist * ray_dir_y) * BLOCK;
	 }
	 else
	 {
		*ray_x = (pos_x + wall_dist * ray_dir_x) * BLOCK;
		*ray_y = map_y * BLOCK;
		if (step_y > 0)
			*ray_y -= 0.001; // Adjust for edge case
	}
	
	// Calculate wall height and drawing bounds
	int line_height = (int)(HEI / wall_dist);
	int draw_start = -line_height / 2 + HEI / 2;
	if (draw_start < 0)
		draw_start = 0;
	int draw_end = line_height / 2 + HEI / 2;
	if (draw_end >= HEI)
		draw_end = HEI - 1;
	
	// Calculate where exactly the wall was hit
	float wall_x;
	if (side == 0)
		wall_x = pos_y + wall_dist * ray_dir_y;
	else
		wall_x = pos_x + wall_dist * ray_dir_x;
	wall_x -= floor(wall_x);
	
	// Determine which texture to use
	int tex_num = 0; // Default to north
	if (side == 0)
	{
		tex_num = (step_x > 0) ? 0 : 1;  // 0 = north, 1 = south
	}
	else
	{
		 tex_num = (step_y > 0) ? 2 : 3;  // 2 = east, 3 = west
	}
	
	// Fill the ray hit structure
	cub3d->calc.wall_dist = wall_dist;
	cub3d->calc.map_x = map_x;
	cub3d->calc.map_y = map_y;
	cub3d->calc.side = side;
	cub3d->calc.wall_x = wall_x;
	cub3d->calc.tex_num = tex_num;
	cub3d->calc.line_height = line_height;
	cub3d->calc.draw_start = draw_start;
	cub3d->calc.draw_end = draw_end;
}
 */

/**
* @brief Define a local struct for temporary ray variables
* This should be added at the top of your raycasting.c file
*/
typedef struct s_ray_vars
{
int		map_x;
int		map_y;
int		step_x;
int		step_y;
float	side_dist_x;
float	side_dist_y;
int		side;
float	wall_dist;
float	wall_x;
int		tex_num;
int		line_height;
int		draw_start;
int		draw_end;
}	t_ray_vars;

/**
 * @brief Calculate delta distances for DDA
 *
 * Calculates the distance between consecutive grid boundaries
 */
static void	calculate_delta_dist(float ray_dir_x, float ray_dir_y,
	float *delta_dist_x, float *delta_dist_y)
{
	if (ray_dir_x == 0)
		*delta_dist_x = 1e30;
	else
		*delta_dist_x = fabs(1 / ray_dir_x);
	if (ray_dir_y == 0)
		*delta_dist_y = 1e30;
	else
		*delta_dist_y = fabs(1 / ray_dir_y);
}

/**
* @brief Setup DDA parameters for x direction
*
* Calculates step and initial side distance for x direction
*/
static void	setup_dda_x(float ray_dir_x, float pos_x, int map_x,
	float delta_dist_x, int *step_x, float *side_dist_x)
{
	if (ray_dir_x < 0)
	{
		*step_x = -1;
		*side_dist_x = (pos_x - map_x) * delta_dist_x;
	}
	else
	{
		*step_x = 1;
		*side_dist_x = (map_x + 1.0 - pos_x) * delta_dist_x;
	}
}

/**
* @brief Setup DDA parameters for y direction
*
* Calculates step and initial side distance for y direction
*/
static void	setup_dda_y(float ray_dir_y, float pos_y, int map_y,
	float delta_dist_y, int *step_y, float *side_dist_y)
{
	if (ray_dir_y < 0)
	{
		*step_y = -1;
		*side_dist_y = (pos_y - map_y) * delta_dist_y;
	}
	else
	{
		*step_y = 1;
		*side_dist_y = (map_y + 1.0 - pos_y) * delta_dist_y;
	}
}

/**
* @brief Perform DDA algorithm to find wall intersection
*
* Executes Digital Differential Analysis to find first wall hit
*/
static void	perform_dda(t_data *cub3d, float delta_dist_x, float delta_dist_y,
	t_ray_vars *vars)
{
	int	hit_flag;

	hit_flag = 0;
	while (hit_flag == 0)
	{
		if (vars->side_dist_x < vars->side_dist_y)
		{
			vars->side_dist_x += delta_dist_x;
			vars->map_x += vars->step_x;
			vars->side = 0;
		}
		else
		{
			vars->side_dist_y += delta_dist_y;
			vars->map_y += vars->step_y;
			vars->side = 1;
		}
		if (vars->map_y < 0 || vars->map_x < 0 || 
		vars->map_y >= cub3d->map_info.map_rows || 
		vars->map_x >= (int)ft_strlen(cub3d->map_info.map[vars->map_y]) || 
		cub3d->map_info.map[vars->map_y][vars->map_x] == '1')
			hit_flag = 1;
	}
}

/**
* @brief Calculate wall distance and hit coordinates
*
* Determines perpendicular wall distance and exact hit position
*/
static void	calculate_wall_hit(t_ray_vars *vars, float ray_dir_x,
	float ray_dir_y, float pos_x, float pos_y,
	float delta_dist_x, float delta_dist_y,
	float *ray_x, float *ray_y)
{
	float	wall_dist;

	if (vars->side == 0)
		wall_dist = vars->side_dist_x - delta_dist_x;
	else
		wall_dist = vars->side_dist_y - delta_dist_y;
	vars->wall_dist = wall_dist;
	if (vars->side == 0)
	{
		*ray_x = vars->map_x * BLOCK;
		if (vars->step_x > 0)
			*ray_x -= 0.001;
		*ray_y = (pos_y + wall_dist * ray_dir_y) * BLOCK;
	}
	else
	{
		*ray_x = (pos_x + wall_dist * ray_dir_x) * BLOCK;
		*ray_y = vars->map_y * BLOCK;
		if (vars->step_y > 0)
			*ray_y -= 0.001;
	}
}

/**
* @brief Calculate wall drawing parameters
*
* Determines line height and drawing boundaries
*/
static void	calculate_draw_params(t_ray_vars *vars)
{
	int	line_height;
	int	draw_start;
	int	draw_end;

	line_height = (int)(HEI / vars->wall_dist);
	draw_start = -line_height / 2 + HEI / 2;
	if (draw_start < 0)
		draw_start = 0;
	draw_end = line_height / 2 + HEI / 2;
	if (draw_end >= HEI)
		draw_end = HEI - 1;
	vars->line_height = line_height;
	vars->draw_start = draw_start;
	vars->draw_end = draw_end;
}

/**
* @brief Calculate texture information
*
* Determines exact wall hit position and texture coordinates
*/
static void	calculate_texture_info(t_ray_vars *vars, float ray_dir_x,
	float ray_dir_y, float pos_x, float pos_y)
{
	float	wall_x;
	int		tex_num;
	
	if (vars->side == 0)
		wall_x = pos_y + vars->wall_dist * ray_dir_y;
	else
		wall_x = pos_x + vars->wall_dist * ray_dir_x;
	wall_x -= floor(wall_x);
	tex_num = 0;
	if (vars->side == 0)
	{
		if (vars->step_x > 0)
			tex_num = 0;
		else
			tex_num = 1;
	}
	else
	{
		if (vars->step_y > 0)
			tex_num = 2;
		else
			tex_num = 3;
	}
	vars->wall_x = wall_x;
	vars->tex_num = tex_num;
}

/**
* @brief Update game data with raycasting results
*
* Transfers calculation results to the main data structure
*/
static void	update_calculations(t_data *cub3d, t_ray_vars *vars)
{
	cub3d->calc.wall_dist = vars->wall_dist;
	cub3d->calc.map_x = vars->map_x;
	cub3d->calc.map_y = vars->map_y;
	cub3d->calc.side = vars->side;
	cub3d->calc.wall_x = vars->wall_x;
	cub3d->calc.tex_num = vars->tex_num;
	cub3d->calc.line_height = vars->line_height;
	cub3d->calc.draw_start = vars->draw_start;
	cub3d->calc.draw_end = vars->draw_end;
}

/**
* @brief Main raycasting function
*
* Orchestrates the entire raycasting process
*/
void	ray_casting(t_data *cub3d, float camera_x, float *ray_x, float *ray_y)
{
	float		ray_dir_x;
	float		ray_dir_y;
	float		pos_x;
	float		pos_y;
	float		delta_dist_x;
	float		delta_dist_y;
	t_ray_vars	vars;
	
	define_raydir(cub3d, camera_x, &ray_dir_x, &ray_dir_y);
	pos_x = cub3d->player.x / BLOCK;
	pos_y = cub3d->player.y / BLOCK;
	vars.map_x = (int)(pos_x);
	vars.map_y = (int)(pos_y);
	calculate_delta_dist(ray_dir_x, ray_dir_y, &delta_dist_x, &delta_dist_y);
	setup_dda_x(ray_dir_x, pos_x, vars.map_x, delta_dist_x, 
	&vars.step_x, &vars.side_dist_x);
	setup_dda_y(ray_dir_y, pos_y, vars.map_y, delta_dist_y, 
	&vars.step_y, &vars.side_dist_y);
	perform_dda(cub3d, delta_dist_x, delta_dist_y, &vars);
	calculate_wall_hit(&vars, ray_dir_x, ray_dir_y, pos_x, pos_y,
	delta_dist_x, delta_dist_y, ray_x, ray_y);
	calculate_draw_params(&vars);
	calculate_texture_info(&vars, ray_dir_x, ray_dir_y, pos_x, pos_y);
	update_calculations(cub3d, &vars);
}