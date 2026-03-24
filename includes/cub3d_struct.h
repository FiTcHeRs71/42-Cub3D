#ifndef CUB3D_STRUCT_H
# define CUB3D_STRUCT_H

typedef enum e_direction
{
	NORTH,
	SOUTH,
	WEST,
	EAST
}				t_direction;

typedef struct s_linked_map
{
	char					*line;
	struct s_linked_map			*next;
}				t_linked_map;

typedef struct s_map
{
	char		**map;
	char		**map_copy;
	int			wall_flag;
	int			player_flag;
	int			player_x;
	int			player_y;
	int			payer_dir;
}				t_map;

typedef struct s_texture
{
	char		*no_path;
	char		*so_path;
	char		*we_path;
	char		*ea_path;
	char		**floor;
	char		**ceiling;
	int			rgb_floor;
	int			rgb_ceiling;
}				t_texture;

typedef struct s_data
{
	int				fd;
	t_map			*map;
	t_texture		*texture;
	struct s_linked_map	*linked_map;
}				t_data;

#endif