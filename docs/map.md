# MAP

## General flow
The `init_map` function is nothing more than a parent function that calls sequentially the three major part of the module. The first part is just an initialization of an empty t_map struct. The second is processing the information contained in the header. Then the third one is processing the map content (grid), though prior to this a validation is done to make sure that all necessary info can be extracted from the header, otherwise no point to continue processing the map content. 

The get_next_line function is used extensively here to parse the .cub file line-by-line.

### Header info
The purpose here is to make sure that all necessary info about the textures & floor-ceiling color can be extracted properly. The idea is rather simple, basically to check if each line starts with the recognizable symbol(s), then store the info contained on that line to the t_map struct.

Checks have to be done to make sure that errors are dealt with properly, e.g.: identical symbols (2 NOs or 2 Fs), failure in finding the file. The sequence of the info is also properly handled.

### Map grid
If validation is passed (all header info properly extracted), then the content (grid) is read. Two passes are done across the **WHOLE** map file to simplify the approach. However the real grid reading is done by making checks if the line contains (only) characters that **are** part of a map grid (`valid_mapline`). The first pass serves as error checking, obviously, but also to count the number of rows that are used to malloc the size of the map array to be stored in t_map.

The second pass actually saves each line (simultaneously removes trailing newline chars) to the t_map struct. The number of cols of the map is also saved at this point for no particular reason.

The map is checked for openings. But not with flood fill but rather by checking if the floor(s) is/are surrounded by walls.
