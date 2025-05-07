#include "../../inc/cub3d.h"

int get_texture_color(t_texture *texture, int x, int y)
{
    char	*dst;
    int		offset;

    if (x < 0 || y < 0 || x >= texture->width || y >= texture->height)
        return (0);
    
    offset = (y * texture->line_len + x * (texture->bpp / 8));
    dst = texture->addr + offset;
    return (*(unsigned int *)dst);
}

void draw_textured_line(t_data *cub3d, int x, int tex_x)
{
    int		y;
    int		tex_y;
    double	step;
    double	tex_pos;
    int		color;
    t_texture *texture;

    texture = &cub3d->textures[cub3d->calc.tex_num];
    step = 1.0 * texture->height / cub3d->calc.line_height;
    tex_pos = (cub3d->calc.draw_start - HEI / 2 + cub3d->calc.line_height / 2) * step;
    
    y = cub3d->calc.draw_start;
    while (y < cub3d->calc.draw_end)
    {
        tex_y = (int)tex_pos & (texture->height - 1);
        tex_pos += step;
        
        color = get_texture_color(texture, tex_x, tex_y);
        
        // Apply shading for North/South walls
        if (cub3d->calc.side == 1)
            color = (color >> 1) & 0x7F7F7F; // Make darker
        
        put_pixel(x, y, color, cub3d);
        y++;
    }
}

void load_textures(t_data *cub3d)
{
	int width, height;

	// Add this before loading textures
	// cub3d->textures = malloc(sizeof(t_img) * 4);
	// if (!cub3d->textures)
	// 	err_msg(cub3d, "Error\nFailed to allocate memory for textures");
	// North texture
	
	cub3d->textures[1].img = mlx_xpm_file_to_image(cub3d->mlx_ptr,
						cub3d->map_info.so_tex, &width, &height);
	if (!cub3d->textures[1].img)
	err_msg(cub3d, "Error\nFailed to load south texture");
	cub3d->textures[1].addr = mlx_get_data_addr(cub3d->textures[1].img,
						&cub3d->textures[1].bpp, &cub3d->textures[1].line_len,
						&cub3d->textures[1].endian);
	cub3d->textures[1].width = width;
	cub3d->textures[1].height = height;

	cub3d->textures[0].img = mlx_xpm_file_to_image(cub3d->mlx_ptr,
						cub3d->map_info.no_tex, &width, &height);
	if (!cub3d->textures[0].img)
		err_msg(cub3d, "Error\nFailed to load north texture");
	cub3d->textures[0].addr = mlx_get_data_addr(cub3d->textures[0].img,
						&cub3d->textures[0].bpp, &cub3d->textures[0].line_len,
						&cub3d->textures[0].endian);
	cub3d->textures[0].width = width;
	cub3d->textures[0].height = height;

	cub3d->textures[2].img = mlx_xpm_file_to_image(cub3d->mlx_ptr,
						cub3d->map_info.ea_tex, &width, &height);
	if (!cub3d->textures[2].img)
		err_msg(cub3d, "Error\nFailed to load east texture");
	cub3d->textures[2].addr = mlx_get_data_addr(cub3d->textures[2].img,
						&cub3d->textures[2].bpp, &cub3d->textures[2].line_len,
						&cub3d->textures[2].endian);
	cub3d->textures[2].width = width;
	cub3d->textures[2].height = height;
	
	cub3d->textures[3].img = mlx_xpm_file_to_image(cub3d->mlx_ptr,
						cub3d->map_info.we_tex, &width, &height);
	if (!cub3d->textures[3].img)
		err_msg(cub3d, "Error\nFailed to load west texture");
	cub3d->textures[3].addr = mlx_get_data_addr(cub3d->textures[3].img,
						&cub3d->textures[3].bpp, &cub3d->textures[3].line_len,
						&cub3d->textures[3].endian);
	cub3d->textures[3].width = width;
	cub3d->textures[3].height = height;
}
/* 
static int load_single_texture(t_data *cub3d, char *tex_path, int tex_index, char *direction)
{
	int width, height;
	
	cub3d->textures[tex_index].img = 
			mlx_xpm_file_to_image(cub3d->mlx_ptr, tex_path, &width, &height);
	if (!cub3d->textures[tex_index].img)
	{
		printf("Failed to load %s texture: %s\n", direction, tex_path);
		return (0);
	}
	cub3d->textures[tex_index].addr = mlx_get_data_addr(
		cub3d->textures[tex_index].img,
		&cub3d->textures[tex_index].bpp,
		&cub3d->textures[tex_index].line_len,
		&cub3d->textures[tex_index].endian);
	cub3d->textures[tex_index].width = width;
	cub3d->textures[tex_index].height = height;
	return (1);
}

void load_textures(t_data *cub3d)
{
	if (!load_single_texture(cub3d, cub3d->map_info.no_tex, 0, "North"))
		err_msg(cub3d, "Error\nFailed to load north texture");
	if (!load_single_texture(cub3d, cub3d->map_info.so_tex, 1, "South"))
		err_msg(cub3d, "Error\nFailed to load south texture");
	if (!load_single_texture(cub3d, cub3d->map_info.ea_tex, 2, "East"))
		err_msg(cub3d, "Error\nFailed to load east texture");
	if (!load_single_texture(cub3d, cub3d->map_info.we_tex, 3, "West"))
		err_msg(cub3d, "Error\nFailed to load west texture");
} */