
#include "../../includes/cub3d.h"

bool	can_move(t_data *data, double new_x, double new_y)
{
	if (is_wall_at(data, new_x - COLLISION_MARGIN, new_y - COLLISION_MARGIN))
		return (false);
	if (is_wall_at(data, new_x + COLLISION_MARGIN, new_y - COLLISION_MARGIN))
		return (false);
	if (is_wall_at(data, new_x - COLLISION_MARGIN, new_y + COLLISION_MARGIN))
		return (false);
	if (is_wall_at(data, new_x + COLLISION_MARGIN, new_y + COLLISION_MARGIN))
		return (false);
	return (true);
}

void	move_up(t_data *data, t_raycast *r)
{
	double	new_x;
	double	new_y;

	new_x = r->pos_x + r->dir_x * MOVE_SPEED;
	new_y = r->pos_y + r->dir_y * MOVE_SPEED;
	if (can_move(data, new_x, r->pos_y))
		r->pos_x = new_x;
	if (can_move(data, r->pos_x, new_y))
		r->pos_y = new_y;
}

void	move_down(t_data *data, t_raycast *r)
{
	double	new_x;
	double	new_y;

	new_x = r->pos_x - r->dir_x * MOVE_SPEED;
	new_y = r->pos_y - r->dir_y * MOVE_SPEED;
	if (can_move(data, new_x, r->pos_y))
		r->pos_x = new_x;
	if (can_move(data, r->pos_x, new_y))
		r->pos_y = new_y;
}

void	move_left(t_data *data, t_raycast *r)
{
	double	new_x;
	double	new_y;

	new_x = r->pos_x - r->plane_x * MOVE_SPEED;
	new_y = r->pos_y - r->plane_y * MOVE_SPEED;
	if (can_move(data, new_x, r->pos_y))
		r->pos_x = new_x;
	if (can_move(data, r->pos_x, new_y))
		r->pos_y = new_y;
}

void	move_right(t_data *data, t_raycast *r)
{
	double	new_x;
	double	new_y;

	new_x = r->pos_x + r->plane_x * MOVE_SPEED;
	new_y = r->pos_y + r->plane_y * MOVE_SPEED;
	if (can_move(data, new_x, r->pos_y))
		r->pos_x = new_x;
	if (can_move(data, r->pos_x, new_y))
		r->pos_y = new_y;
}
