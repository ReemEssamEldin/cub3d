/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structs.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsetyamu <hsetyamu@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/13 11:40:16 by reldahli          #+#    #+#             */
/*   Updated: 2025/05/07 20:27:51 by hsetyamu         ###   ########.fr       */
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
	// Minimap params & Ray calcs
	int		mm_wall_col;		// Wall color on minimap
	int		mm_space_col;		// Space color on minimap
	int		mm_padding;			// Padding around minimap
	float	mm_raylen;			// Maximum ray length for minimap
	
	// Minimap ray rendering
	int		base_col;			// Base color for rays (WHI)
	int		bg_col;				// Background color (BLA)
	float	ins;				// Current ray intensity
	float	ray_x;				// Current ray x position
	float	ray_y;				// Current ray y position
	float	cur_len;			// Current ray length
	int		blended_col;		// Resulting blended color

	//raycasting calculations
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
	float	ray_dir_x;
	float	ray_dir_y;
	float	pos_x;
	float	pos_y;
	float	delta_dist_x;
	float	delta_dist_y;
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
