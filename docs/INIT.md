# INIT

## General flow
The init step consist of two sub-modules, one has something to do with putting the player on the map and another to initialize all mlx related pointers. A stowaway function to load textures is included here because it seems logical to make the xpm textures to image at this stage after the mlx pointers has been created. 

### Player initialization
Basically the `put_player` function iterates over the map (again!) to find the starting position and sets a correct direction accordingly.

The lines
```
cub3d->player.x = (x * BLOCK) + (BLOCK / 2);
cub3d->player.y = (y * BLOCK) + (BLOCK / 2);
```
in `set_position` serves several purposes:
1. for visual consistency to make sure the player appears properly centered (within walkable areas)
2. for collision handling: when checking for collisions with walls, calculations can be made from the center of the player outward.
3. for raycasting, casting rays from the center of the player's position.
4. for rotation mechanics, having a rotation around a center (rather than a corner) is more natural.

Additional check was done by having a flag that indicates that a player symbol (NSEW) has been found. If this symbol is found again (or as well, does not exists at all) the flag leads to a termination.

This init step also initializes the movement flags of the player (in the player struct) to false (not moving). This will be modified according to the key strokes (set in the input module).

### MLX initialization
Nothing worthy of note here, just initializes mlx relate pointers to NULL and create them by the functions `mlx_init`, `mlx_new_window`, `mlx_new_image`.

At this stage, the textures are loaded via `mlx_xpm_file_to_image` to be used to draw the walls.