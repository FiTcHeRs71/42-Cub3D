
#ifndef CUB3D_H
# define CUB3D_H

# define TITLE "Cub3D - LES RAY-CAST-COUILLES"
# define MOVE_SPEED 0.15
# define ROT_SPEED  0.03
# define MOUSE_SENSITIVITY 0.002
# define MOUSE_MAX_DELTA 5
# define MAGENTA 0xFF00FF
# define COLLISION_MARGIN 0.15

/*================== MINI MAP ==================*/

# define MINIMAP_RATIO 0.15
# define REVEAL_RADIUS 5
# define MM_COLOR_WALL 0x000000
# define MM_COLOR_FLOOR 0x808080
# define MM_COLOR_PLAYER 0xFF0000
# define MM_COLOR_CONE 0xFFFF00
# define MM_CONE_ALPHA 0.4
# define MM_CONE_LENGTH 4.0

/*================== LIBRAIRY & HEADERS ==================*/

# include <X11/keysym.h>
# include <math.h>
# include <pthread.h>
# include "../minilibx-linux/mlx.h"
# include "../libft/include/libft.h"
# include "cub3d_struct.h"
# include "cub3d_message.h"

# include "fred.h"// a suppr
# include "leo.h" // a suppr

/*================== FONCTION ==================*/

/*-------- PARSE ------------*/
void			parse_cub3d(t_data *data, char *file);
void			check_map(t_data *data, t_map *map);
void			node_map_add_back(t_linked_map **lst, t_linked_map *new_one);
void			convert_linked_map_to_array(t_data *data, t_map *map);
bool			extract_config(char *line, t_data *data);
int				get_color_code(t_data *data, char **arry_code);
int				node_map_size(t_linked_map *lst);
t_linked_map	*new_node_map(void *content);
bool			checker_file_extension(char *file, char *extension);
char			*free_and_getline(char *line, int fd);
bool			checker_before_split(char *line, char sep);

/*-------- UTILS ------------*/
void			clean_all(t_data *data);
void			ft_error(char *msg, t_data *data);
void			ft_error_ctx(char *what, char *detail, t_data *data);
void			init_data(t_data *data);
void			init_mini_map(t_data *data);
void			clean_mini_map(t_data *data);

/*-------- TEXTURES ------------*/
void			load_wall_textures(t_data *data, t_texture *texture, t_mlx *mlx);
void			use_texture(t_data *data, t_raycast *ray, t_texture *tex, t_draw *draw);

/*-------- MOUVEMENT ------------*/
void			update_player(t_data *data);
bool			can_move(t_data *data, double new_x, double mew_y);
void			move_up(t_data *data, t_raycast *r);
void			move_down(t_data *data, t_raycast *r);
void			move_left(t_data *data, t_raycast *r);
void			move_right(t_data *data, t_raycast *r);
int				mouse_motion(int x, int y, t_data *data);

/*-------- WINDOW ------------*/
void			init_window(t_data *data, t_mlx *mlx);
int				handle_key_press(int keycode, t_data *data);
int				handle_key_release(int keycode, t_data *data);
int				mouse_motion(int x, int y, t_data *data);
int				focus_in(t_data *data);
int				focus_out(t_data *data);
int				close_window(t_data *data);
void			reset_mouse_to_center(t_data *data);

/*-------- DRAW ------------*/
void			draw_wall(t_data *stats, t_raycast *data,
					t_draw *draw, int x_coord);

/*-------- RAYCASTING ------------*/
void			*raycasting(void *arg);
void			set_data_raycasting(t_raycast *data, t_map *map);

#endif