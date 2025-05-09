/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   leftover.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: reldahli <reldahli@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/09 13:53:42 by reldahli          #+#    #+#             */
/*   Updated: 2025/05/09 13:53:43 by reldahli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* void	ray_marching(t_data *cub3d, float start_x, float *ray_x, float *ray_y)
{
    float	cos_angle;
    float	sin_angle;
    float	max_ray_length = BLOCK * 100;
    float	current_length;

    cos_angle = cos(start_x);
    sin_angle = sin(start_x);
    // *ray_x = cub3d->player.x + BLOCK / 4;
	// Start from middle of player square
    // *ray_y = cub3d->player.y + BLOCK / 4;
	// Start from middle of player square
	*ray_x = cub3d->player.x;
    *ray_y = cub3d->player.y;
    max_ray_length = BLOCK * 100;      // Limit ray to 5 blocks length
    current_length = 0;

    while (!touch(*ray_x, *ray_y, cub3d) && current_length < max_ray_length)
    //while (!touch(*ray_x, *ray_y, cub3d))
	{
        put_pixel(*ray_x, *ray_y, RED, cub3d); // This line handles rays
        *ray_x += cos_angle;
        *ray_y += sin_angle;
        current_length += 1;
    }
} */
//texture mapping (previously in draw_line)
/* //--------------------------------------------------------------------------
	// Define variables for texture mapping
	int tex_num = 0;        // Which texture to use (N,S,E,W)
	double wall_x = 0;      // Where exactly the ray hit the wall
	int tex_x;              // X coordinate on the texture

	// Determine which wall was hit and exact position
	// This requires knowing if we hit a vertical or horizontal wall edge
	int map_x = (int)(ray_x / BLOCK);
	//int map_y = (int)(ray_y / BLOCK);

	// Check if we hit a vertical or horizontal wall
	if (fabs(ray_x - map_x * BLOCK) < 0.01
	|| fabs(ray_x - (map_x+1) * BLOCK) < 0.01)
	{
		// Hit vertical wall
		wall_x = ray_y - floor(ray_y / BLOCK) * BLOCK;
		if (cos_angle > 0)
			tex_num = 3;    // West wall
		else
			tex_num = 2;    // East wall
	}
	else
	{
		// Hit horizontal wall
		wall_x = ray_x - floor(ray_x / BLOCK) * BLOCK;
		if (sin_angle > 0)
			tex_num = 0;    // North wall
		else
			tex_num = 1;    // South wall
	}

	// Get the texture X coordinate
	tex_x = (int)(wall_x / BLOCK * cub3d->textures[tex_num].width);

	// Calculate wall height based on distance
	dist = fixed_dist(player->x, player->y, ray_x, ray_y, cub3d);
	height = (BLOCK / dist) * (WID / 2);
	start_y = (HEI - height) / 2;
	end = start_y + height;

	// Draw ceiling
	draw_maindisplay(0, start_y, rgb_to_colour
	(cub3d->map_info.ce_col), cub3d, i);

	// Draw textured wall
	double step = cub3d->textures[tex_num].height / (double)height;
	double tex_pos = 0;

	for (int y = start_y; y < end; y++)
	{
		int tex_y = (int)tex_pos & (cub3d->textures[tex_num].height - 1);
		tex_pos += step;

		// Get pixel color from texture
		int idx = tex_y * cub3d->textures[tex_num].line_len +
				 tex_x * (cub3d->textures[tex_num].bpp / 8);
		unsigned char b = cub3d->textures[tex_num].addr[idx];
		unsigned char g = cub3d->textures[tex_num].addr[idx + 1];
		unsigned char r = cub3d->textures[tex_num].addr[idx + 2];

		// Optional: apply distance shading
		float shade = 1.0f / (1.0f + dist * 0.04f);
		if (shade > 1.0f) shade = 1.0f;
		if (shade < 0.3f) shade = 0.3f;

		r *= shade;
		g *= shade;
		b *= shade;

		// Combine colors into one value
		int color = (r << 16) | (g << 8) | b;

		put_pixel(i, y, color, cub3d);
	}

	// Draw floor
	draw_maindisplay(end, HEI, rgb_to_colour
		(cub3d->map_info.fl_col), cub3d, i); */

// void draw_filled_circle(int x, int y, int radius, int color, t_data *cub3d)
// {
// 	int i, j;

// 	for (j = -radius; j <= radius; j++)
// 	{
// 		for (i = -radius; i <= radius; i++)
// 		{
// 			// Check if the pixel is within the circle's radius
// 			if (i * i + j * j <= radius * radius)
// 			{
// 				put_pixel(x + i, y + j, color, cub3d);
// 			}
// 		}
// 	}
// }
