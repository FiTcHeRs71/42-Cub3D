#ifndef CUB3D_STRUCT_H
# define CUB3D_STRUCT_H

typedef enum e_direction
{
	NORTH,
	SOUTH,
	WEST,
	EAST,
}						t_direction;

typedef struct s_raycast
{
	double	pos_x;
	double	pos_y;
	double	dir_x; // direction vector
	double	dir_y;
	double	plane_x; // 2d raycasting version
	double	plane_y;
	double	time; // used to make movement smoother by using time difference between frames
	double	old_time;
	double	camera_x;
	double	ray_dir_x;
	double	ray_dir_y;
	double	side_dist_x;
	double	side_dist_y;
	double	delta_dist_x;
	double	delta_dist_y;
	int		map_x;
	int		map_y;
	int		step_x;
	int		step_y;
	double	wall_dist;
	int		wall_side;
	bool	is_hit;
	bool	done;
}			t_raycast;

typedef struct s_draw
{
	int		line_h;
	int		line_start;
	int		line_end;
	int		steps;
}			t_draw;

typedef struct s_linked_map
{
	char				*line;
	struct s_linked_map	*next;
}						t_linked_map;

typedef struct	s_mlx
{
	void	*mlx_connect;
	void	*mlx_window;
	void	*img;
	char	*img_data;
	int		bits_per_pixel;
	int		size_line;
	int		endian;
}				t_mlx;

typedef struct s_map
{
	char				**map;
	char				**map_copy;
	int					wall_flag;
	int					player_flag;
	int					player_x;
	int					player_y;
	int					payer_dir;
}						t_map;

typedef struct s_texture
{
	char				*no_path;
	char				*so_path;
	char				*we_path;
	char				*ea_path;
	char				**floor;
	char				**ceiling;
	int					rgb_floor;
	int					rgb_ceiling;
}						t_texture;

typedef struct s_data
{
	int					fd;
	int					window_y;
	int					window_x;
	t_map				*map;
	t_texture			*texture;
	t_mlx				*mlx;
	struct s_linked_map	*linked_map;
}						t_data;

#endif