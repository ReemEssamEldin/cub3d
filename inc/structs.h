/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structs.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsetyamu <hsetyamu@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/13 11:40:16 by reldahli          #+#    #+#             */
/*   Updated: 2025/05/09 14:52:34 by hsetyamu         ###   ########.fr       */
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
	char		**map;
	int			map_rows;
	int			map_cols;

	int			col_ceil;
	int			col_floo;
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

typedef struct s_draw
{
	int	x;
	int	y;
	int	size;
	int	col;
	int	top;
	int	bottom;
}	t_draw;

typedef struct s_calculations
{
	//minimap params & ray calcs
	int		mm_wall_col;
	int		mm_space_col;
	int		mm_padding;
	float	mm_raylen;

	//minimap cone rendering
	int		base_col;
	int		bg_col;
	float	ins;
	float	ray_x;
	float	ray_y;
	float	cur_len;
	int		blended_col;

	//raycasting calculations
	int		map_x;
	int		map_y;
	int		step_x;
	int		step_y;
	float	side_distx;
	float	side_disty;
	int		side;
	float	wall_dist;
	float	wall_x;
	int		tex_num;
	int		line_height;
	int		draw_start;
	int		draw_end;
	float	ray_dirx;
	float	ray_diry;
	float	posx;
	float	posy;
	float	delta_distx;
	float	delta_disty;
}	t_calc;

typedef struct s_move
{
	float	speed;
	float	angle_speed;
	float	collision_buffer;
	float	dir_x;
	float	dir_y;
	float	cos_angle;
	float	sin_angle;
}	t_move;

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
	t_draw		draw;
	t_move		move;
}	t_data;

#endif
