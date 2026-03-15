#ifndef CUB3D_STRUCT_H
# define CUB3D_STRUCT_H

typedef struct s_map
{
	char		**map;
	char		**map_copy;
	int			wall_flag;
	int			player_flag;
	int			player_x;
	int			player_y;
	char		player_dir;
}				t_map;

typedef struct s_texture
{
	char		*no_path;
	char		*so_path;
	char		*we_path;
	char		*ea_path;
	char		**floor;
	char		**ceiling;
}				t_texture;

typedef struct s_data
{
	int			fd;
	t_map		*map;
	t_texture	*texture;
}				t_data;

#endif