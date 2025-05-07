/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structs.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsetyamu <hsetyamu@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/13 11:40:16 by reldahli          #+#    #+#             */
/*   Updated: 2025/05/07 19:43:15 by hsetyamu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCTS_H
# define STRUCTS_H

# include "cub3d.h"

typedef struct s_player
{
	float	x;
	float	y;
	float	angle;

	bool	key_up;
	bool	key_down;
	bool	key_left;
	bool	key_right;

	bool	left_rotate;
	bool	right_rotate;
}	t_player;

typedef struct s_map
{
	char		*no_tex;
	char		*so_tex;
	char		*we_tex;
	char		*ea_tex;

	char		*fl_col;
	char		*ce_col;
/* 	int			*fl_col;
	int			*ce_col; */
	char		**map;
	int			map_rows;
	int			map_cols;
}	t_map;

typedef struct s_texture
{
	void	*img;
	char	*addr;
	int		width;
	int		height;
	int		bpp;
	int		line_len;
	int		endian;
}	t_texture;

typedef struct s_calculations
{
	// Minimap parameters
	int		mm_wall_col;		// Wall color on minimap
	int		mm_space_col;		// Space color on minimap
	int		mm_padding;			// Padding around minimap

	// Ray calculation variables
	//float	fraction;			// Angle fraction per ray
	//float	start_x;			// Starting ray angle
	float	mm_raylen;				// Maximum ray length for minimap
	//float	ray_angles[WID];	// Store ray angles for later use

	// Minimap ray rendering
	int		base_col;			// Base color for rays (WHI)
	int		bg_col;				// Background color (BLA)
	float	ins;				// Current ray intensity
	//float	cos_angle;			// Cosine of current angle
	//float	sin_angle;			// Sine of current angle
	float	ray_x;				// Current ray x position
	float	ray_y;				// Current ray y position
	float	cur_len;			// Current ray length
	int		blended_col;		// Resulting blended color

	//raycasting calculations
	float	wall_dist;			// Perpendicular distance to wall
	int		map_x;				// Map x-coordinate where hit occurred
	int		map_y;				// Map y-coordinate where hit occurred
	int		side;				// Which side was hit (0 = NS, 1 = EW)
	float	wall_x;				// Exact position where wall was hit (for texturing)
	int		tex_num;			// Which texture to use
	int		line_height;		// Height of line to draw
	int		draw_start;			// Starting pixel y-coordinate
	int		draw_end;			// Ending pixel y-coordinate
}	t_calc;

typedef struct s_data
{
	void		*mlx_ptr;
	void		*win_ptr;
	void		*img_ptr;
	char		*addr;
	int			bpp;
	int			line_len;
	int			endian;

	t_player	player;
	t_map		map_info;
	t_texture	textures[4];
	t_calc		calc;
}	t_data;

#endif
