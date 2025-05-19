# MAIN

## General flow
The idea here is very basic and intuitive, but probably may not be implemented as such. The first thing to do is some basic argument check (`check_args`). Other checks are done throughout the initialization step(s) whenever/wherever it's convenient. 

[[MAP](./docs/MAP.md)] The second stage is initialization of the map (`init_map`), namely; processing the map header and processing the map content and store the min the sruct.

[[INIT](./docs/INIT.md)] The next one is initializing the player (`init_player`) where the player is put in the map according to the instruction of the map (location & direction). Here the movement flags (this relates to key pressing) is initialized as false (dont move).

~~Then the ```init_cub3d``` only sets some pointers to NULL and ```init_mlx``` creates those pointer (the mlx pointer, window pointer, and the image pointer).~~ Here the xpm textures are loaded after the mlx pointer is created (```load_multitexs```).

[[AUDIO](./docs/AUDIO.md)] As a bonus, a `play_audio` module can be activated to play a track. This works, but very badly, because it's difficult figure out a nice way to play the track in a loop, that means the track plays only once.

[[INPUT](./docs/INPUT.md)]Afterwards, the input methods are set (```key_hooks```). Here the setup can accomodate both linux and mac systems.

[[MOVEMENT](./docs/MOVEMENT.md)]

[[DISPLAY](./docs/DISPLAY.md)]The heart of the program is run by looping the ```render``` function (```mlx_loop_hook``` & ```mlx_loop```).

Though the program ideally never get to this point, but for completion's sake, a ```destroy``` line is included as a clean-up before the main returns 0.