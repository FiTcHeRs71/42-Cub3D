
#include "../../includes/cub3d.h"
#include <stdbool.h>

static bool	can_move(t_data *data, double new_x, double mew_y)
{
	int	x;
	int	y;

	x = (int)new_x;
	y = (int)mew_y;
	if (y < 0 || x < 0 || !data->map->map[y] || x >= (int)ft_strlen(data->map->map[y]))
		return (false);
	if (data->map->map[x][y] == '1' || data->map->map[x][y] == ' ')
		return (false);
	return (true);
}

static void	move_player(t_data *data, t_raycast *r, t_map *pos)
{
	double	new_x;
	double	new_y;

	if (data->keys.w)
	{
		new_x = r->pos_x + r->dir_x * MOVE_SPEED;
		new_y = r->pos_y + r->dir_y * MOVE_SPEED;
		if (can_move(data, new_x, r->pos_y))
			data->map->player_x = new_x;
		if (can_move(data, r->pos_x, new_y))
			data->map->player_y = new_y;
	}
	if (data->keys.s)
	{
		new_x = r->pos_x - r->dir_x * MOVE_SPEED;
		new_y = r->pos_y - r->dir_y * MOVE_SPEED;
		if (can_move(data, new_x, r->pos_y))
			data->map->player_x = new_x;
		if (can_move(data, r->pos_x, new_y))
			data->map->player_y = new_y;
	}
	if (data->keys.d)
	{
		new_x = r->pos_x + r->plane_x * MOVE_SPEED;
		new_y = r->pos_y + r->plane_y * MOVE_SPEED;
		if (can_move(data, new_x, r->pos_y))
			data->map->player_x = new_x;
		if (can_move(data, r->pos_x, new_y))
			data->map->player_y = new_y;
	}
	if (data->keys.a)
	{
		new_x = r->pos_x - r->plane_x * MOVE_SPEED;
		new_y = r->pos_y - r->plane_y * MOVE_SPEED;
		if (can_move(data, new_x, r->pos_y))
			data->map->player_x = new_x;
		if (can_move(data, r->pos_x, new_y))
			data->map->player_y = new_y;
	}
}

static void rotate_player(t_data *data, t_raycast *r)
{
	double	old_dir_x;
	double	old_plane_x;
	double	rot;

	r = data->raycast;
	rot = 0;
	if (data->keys.left)
		rot = -ROT_SPEED;
	else if (data->keys.right)
		rot = ROT_SPEED;
	if (rot == 0)
		return ;
	old_dir_x   = r->dir_x;
	r->dir_x    = r->dir_x * cos(rot) - r->dir_y * sin(rot);
	r->dir_y    = old_dir_x * sin(rot) + r->dir_y * cos(rot);
	old_plane_x = r->plane_x;
	r->plane_x  = r->plane_x * cos(rot) - r->plane_y * sin(rot);
	r->plane_y  = old_plane_x * sin(rot) + r->plane_y * cos(rot);
}

void	update_player(t_data *data)
{
	move_player(data, data->raycast, data->map);
	rotate_player(data, data->raycast);
}