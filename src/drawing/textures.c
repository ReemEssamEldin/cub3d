#include "../../inc/cub3d.h"

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