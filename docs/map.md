# MAP

## General flow
The `init_map` function is nothing more than a parent function that calls sequentially the three major part of the module. The first part is just an initialization of an empty t_map struct. The second is processing the information contained in the header. Then the third one is processing the map content (grid), though prior to this a validation was done to make sure that all necessary info can be extracted from the header, otherwise no point to continue processing the map content.

### Header info
The purpose here is to make sure that all necessary info about the textures & floor-ceiling color can be extracted properly.

### Map grid

### Starting position & direction