#ifndef CUB3D_MESSAGE_H
# define CUB3D_MESSAGE_H

/*================== MESSAGE MANAGEMENT ==================*/

/* Usage / system */
# define ERR_USAGE "Error\nUsage: ./cub3D <map.cub>\n"
# define ERR_MALLOC "Error\nMemory allocation failed\n"

/* File errors */
# define ERR_FILE_EXT "Error\nMap file must have .cub extension\n"
# define ERR_FILE_OPEN "Error\nCannot open map file\n"
# define ERR_FILE_ACCESS "Error\nCannot access map file\n"

/* Configuration errors */
# define ERR_CFG_MISSING "Error\nMissing configuration element \
(NO/SO/WE/EA/F/C)\n"
# define ERR_CFG_DUPLICATE "Error\nDuplicate configuration element\n"
# define ERR_CFG_FORMAT "Error\nInvalid configuration line\n"
# define ERR_TEX_PATH "Error\nInvalid or unreadable texture file\n"
# define ERR_COLOR_FORMAT "Error\nInvalid color format (expected R,G,B)\n"
# define ERR_COLOR_RANGE "Error\nColor value out of range (0-255)\n"

/* Map errors */
# define ERR_MAP_MISSING "Error\nNo map found in file\n"
# define ERR_MAP_CHAR "Error\nInvalid character in map \
(allowed: 0 1 N S E W space)\n"
# define ERR_MAP_NOT_CLOSED "Error\nMap is not closed by walls\n"
# define ERR_MAP_PLAYER "Error\nMap must contain exactly one player\n"
# define ERR_MAP_EMPTY_LINE "Error\nEmpty line inside map\n"

/* MLX errors */
# define ERR_MLX_INIT "Error\nMLX initialization failed\n"
# define ERR_MLX_WIN "Error\nMLX window creation failed\n"
# define ERR_MLX_IMG "Error\nMLX image creation failed\n"

#endif