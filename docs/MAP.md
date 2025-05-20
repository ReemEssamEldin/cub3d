# MAP

## General flow
The `init_map` function is nothing more than a parent function that calls sequentially the three major part of the module. The first part is just an initialization of an empty t_map struct (`init_struct`). The second is processing the information contained in the header. Then the third one is processing the map content (grid), though prior to this a validation is done to make sure that all necessary info can be extracted from the header, otherwise no point to continue processing the map content. 

The get_next_line function is used extensively here to parse the .cub file line-by-line.

### Header info
The purpose here is to make sure that all necessary info about the textures & floor-ceiling color can be extracted properly. The idea is rather simple, basically to check if each line starts with the recognizable symbol(s) such as NO, EA, C, etc. , then store the info contained on that line to the t_map struct.

Checks have to be done to make sure that invalid inputs are dealt with properly, e.g.: identical symbols (2 NOs or 2 Fs), failure in finding the file, etc.

A little complication was encountered for the colour part. Since the textures part only requires for the path to the texture files to be verified and saved, no particular problem arose here, however the colours have have to be processed from their RGB components to yield a final colour value. During the course of the project, this was done in the rendering/display module of the program since at this point the struct only stores the complete string from the .cub header. But then so many scenarios have to be considered for which kind of input should be considered valid/invalid (spaces after comma, before comma) we thought it may be prudent to just move it to the mapload module and take care of everything here.

### Check for complete header
Since the map_info struct was initialized to either NULL (for strings - texture paths & raw RGB colour input) or 0 (for values - processed RGB colour), the check `header_complete` simply goes over the struct to verify each field has been filled (**not** NULL/**not** -1). Whether they are properly filled or not, that is checked during the filling by the responsible function themselves. For example: the textures are checked by `open` whether the file exist/not, if not then leave the field empty and this check will lead to termination. Or maybe the raw RGB colour input deviates from acceptable value (e.g. x < 0 || x >255) then set the field to -1 which will also fail the check.

Basically termination at parsing the .cub map header is done only at this stage, although each step/function will also print out a more verbose message for easier tracing.

### Map grid
If validation is passed (all header info properly extracted), then the content (grid) is read. Two passes are done across the **WHOLE** map file to simplify the approach. 

The real grid reading is done by making checks if the line contains (only) characters that **are** part of a map grid (`valid_mapline`). The first pass serves as error checking, obviously, but also to count the number of rows that are used to malloc the size of the map array to be stored in t_map.

The second pass actually saves each line (simultaneously removes trailing newline chars) to the t_map struct. The number of cols of the map is also saved at this point.

### Unenclosed map
The map is checked for openings, not with flood fill but rather by checking if the floor is surrounded by walls. This is the last check for overall map validity.

I dont want to write this one so here is a GPT generated explanation:

#### How It Works
1. Step 1: Initialization and Iteration Setup
```
int	verify_boundaries(t_data *cub3d)
{
    int	i;
    int	j;

    i = 0;
    while (i < cub3d->map_info.map_rows)
```
The function initializes row counter i and prepares to iterate through every row in the map.

2. Step 2: Inner Loop - Column Iteration
```
        j = 0;
        while (j < (int)ft_strlen(cub3d->map_info.map[i]))
        {
```
For each row, it sets up another counter j to iterate through each column in that row.

3. Step 3: Position Validation
```
            if (!validate_position(cub3d, i, j))
                return (0);
            j++;
        }
        i++;
    }
    return (1);
```
For each cell at position (i,j), it calls `validate_position()`. 
If any position fails validation (returns 0), the entire function immediately returns 0, 
indicating the map is invalid. 
If all positions pass validation, it returns 1.

##### The Validation Process
The `validate_position` function performs three critical checks:

- Is the cell walkable? (`is_walkable`)
If it's not walkable (i.e., it's a wall '1'), it returns 1 (valid)
If it is walkable (i.e., '0', 'N', 'S', 'E', 'W'), it continues checks

- Is the cell on a boundary? (`is_boundpos`)
If it's on a boundary (first/last row or column), it returns 0 (invalid)
This prevents walkable cells from being placed at map edges.

- Are all neighboring cells valid? (`check_neighbours`)
Checks all 8 surrounding cells to ensure none are spaces or out of bounds
If any neighbor is a space or out of bounds, returns 0 (invalid)

##### Example maps:

Valid Map Example:
```
111111
1N0011
100001
111111
```
Here's what happens during validation:

1. Position (0,0) through (0,5) - First Row

	- All are '1' (walls)
	- `validate_position` returns 1 for each (valid)

2. Position (1,1) - Player Start 'N'

	- `is_walkable` returns true
	- `is_boundpos` returns false (not on boundary)
	- `check_neighbours` examines all 8 adjacent cells:
		- Above: (0,0), (0,1), (0,2) - all walls '1'
		- Sides: (1,0), (1,2) - wall '1' and empty '0'
		- Below: (2,0), (2,1), (2,2) - wall '1' and empties '0'
	- All neighbors are valid, so `check_neighbours` returns 1
	- `validate_position` returns 1 (valid)

3. Positions (1,2), (2,1), (2,2), (2,3), (2,4) - Empty Spaces '0'

	- Similar process to Position (1,1)
	- All are properly enclosed by walls or other valid tiles
	- All return valid

The function continues checking all positions and finds all are valid, so `verify_boundaries` returns 1.

Invalid Map Example:
```
111111
1N0 11
100001
111111
```
Notice the space at position (1,3). When validating:

1. Position (1,2) - Empty Space '0'
	- `is_walkable` returns true
	- `is_boundpos` returns false (not on boundary)
	- `check_neighbours` examines neighbors, including (1,3) which is a space ' '
	- A space is invalid adjacent to a walkable area
	- `check_neighbours` returns 0 (invalid)
	- `validate_position` returns 0 (invalid)
	- `verify_boundaries` immediately returns 0 (invalid map)
```