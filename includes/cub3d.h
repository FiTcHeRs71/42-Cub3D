
#ifndef CUB3D_H
# define CUB3D_H

/*================== LIBRAIRY & HEADERS ==================*/

# include "../libft/include/libft.h"
# include "cub3d_struct.h"

/*================== MESSAGE MANAGEMENT ==================*/

# define INSTRUCTIONS "Error \n Usage: ./cub3d <valid_map.cub>\n"
# define MALLOC_FAILED "Memory allocation failed, exit \n"
# define FD_ERROR "Unable to open map file, exit \n"
# define INVALID_MAP "Invalid map, exit \n"
# define INVALID_SETTINGS "Invalid configuration format or missing elements\n"

/*================== FONCTION ==================*/

/*-------- PARSE ------------*/
void	parse_cub3d(t_data *data, char *file);
bool	extract_config(char *line, t_data *data);
void	check_map(t_data *data, t_map *map);
int		get_color_code(t_data *data, char **arry_code);
/*-------- UTILS ------------*/
/*clear.c*/
void	clean_all(t_data *data);

/*error.c*/
void	ft_error(char *msg, t_data *data);

#endif