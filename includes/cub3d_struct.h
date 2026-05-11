#ifndef CUB3D_STRUCT_H
# define CUB3D_STRUCT_H

# include <bits/pthreadtypes.h>

typedef struct s_data	t_data;

# define ENEMY_FRAMES 4
# define GUN_FRAMES 3

typedef struct s_thread_data
{
	int			x_start;
	int			x_end;
	t_data		*data;
	pthread_t	id;
}				t_thread_data;

typedef enum e_direction
{
	NORTH,
	SOUTH,
	WEST,
	EAST,
}						t_direction;

typedef enum e_gun_state
{
	GUN_IDLE,
	GUN_SHOOT_1,
	GUN_SHOOT_2,
}						t_gun_state;

typedef struct s_keys
{
	bool				w;
	bool				a;
	bool				s;
	bool				d;
	bool				left;
	bool				right;
}						t_keys;

typedef struct s_raycast
{
	double				pos_x;
	double				pos_y;
	double				dir_x;
	double				dir_y;
	double				plane_x;
	double				plane_y;
	double				time;
	double				old_time;
	double				camera_x;
	double				side_dist_x;
	double				side_dist_y;
	double				delta_dist_x;
	double				delta_dist_y;
	int					map_x;
	int					map_y;
	int					step_x;
	int					step_y;
	double				wall_dist;
	bool				is_hit;
	bool				done;
	char				hit_char;
}						t_raycast;

typedef struct s_sprite_calc
{
	double				sprite_x;
	double				sprite_y;
	double				inv_det;
	double				transform_x;
	double				transform_y;
	int					screen_x;
	int					height;
	int					width;
	int					v_offset;
	int					draw_start_x;
	int					draw_end_x;
	int					draw_start_y;
	int					draw_end_y;
}						t_sprite_calc;

typedef struct s_linked_map
{
	char				*line;
	struct s_linked_map	*next;
}						t_linked_map;

typedef struct s_mlx
{
	void				*mlx_connect;
	void				*mlx_window;
	void				*img;
	char				*img_data;
	int					bits_per_pixel;
	int					size_line;
	int					endian;
}						t_mlx;

typedef struct s_map
{
	char				**map;
	char				**map_copy;
	int					wall_flag;
	int					player_flag;
	int					player_x;
	int					player_y;
	int					player_dir;
	int					map_size;
	int					*line_len;
}						t_map;

typedef struct s_tex_img
{
	void				*img;
	char				*addr;
	int					bpp;
	int					size_line;
	int					endian;
	int					width;
	int					height;
}						t_tex_img;

typedef struct s_texture
{
	t_tex_img			so;
	t_tex_img			no;
	t_tex_img			we;
	t_tex_img			ea;
	t_tex_img			door;
	t_tex_img			ground;
	t_tex_img			ceiling;
	t_tex_img			tex_flag;
	char				*no_path;
	char				*so_path;
	char				*we_path;
	char				*ea_path;
	char				**floor;
	char				**roof;
	int					rgb_floor;
	int					rgb_ceiling;
	int					tex_x;
	int					tex_y;
	double				step;
	double				tex_pos;
	double				wall_x;
}						t_texture;

typedef struct s_minimap
{
	bool				**discovered;
	bool				fullscreen;
	int					pos_x;
	int					pos_y;
	int					width;
	int					height;
	int					scale;
}						t_minimap;

typedef struct s_shoot_calc
{
	double	transform_x;
	double	transform_y;
	int		screen_x;
	int		width;
}			t_shoot_calc;

typedef struct s_draw
{
	int					line_h;
	int					line_start;
	int					line_end;
	int					steps;
	int					wall_side;
	double				raydir_x;
	double				raydir_y;
	t_texture			tex;
}						t_draw;

typedef struct s_enemy
{
	double				pos_x;
	double				pos_y;
	double				dist;
	bool				is_dead;
	struct s_enemy		*next;
}						t_enemy;

typedef struct s_enemy_anim
{
	t_tex_img			frames[ENEMY_FRAMES];
	t_tex_img			dead_frame;
	int					current_frame;
	int					frame_counter;
}						t_enemy_anim;

typedef struct s_gun_draw
{
	int					gun_size;
	int					x_start;
	int					y_start;
	int					x;
	int					y;
	int					tx;
	int					ty;
	int					color;
}						t_gun_draw;

typedef struct s_gun
{
	t_tex_img			frames[GUN_FRAMES];
	t_gun_state			state;
	int					frame_counter;
}						t_gun;

typedef struct s_data
{
	int					fd;
	int					window_y;
	int					window_x;
	bool				mouse_active;
	int					largest_line;
	int					enemy_count;
	double				*z_buffer;
	t_gun				gun;
	t_keys				keys;
	t_minimap			mini_map;
	t_enemy_anim		enemy_anim;
	t_thread_data		*threads;
	t_map				*map;
	t_texture			*texture;
	t_mlx				*mlx;
	t_raycast			*raycast;
	t_draw				*draw;
	t_enemy				*enemies;
	struct s_linked_map	*linked_map;
}						t_data;

#endif
