
#include "../../includes/cub3d.h"
#include <stdio.h>

void	clean_mini_map(t_data *data)
{
	int	i;

	i = 0;
	if (data->mini_map.discovered)
	{
		while (i < data->map->map_size)
		{
			free(data->mini_map.discovered[i]);
			i++;
		}
		free(data->mini_map.discovered);
	}
}

void	free_enemies(t_enemy *enemies)
{
	t_enemy	*tmp;

	while (enemies)
	{
		tmp = enemies;
		enemies = enemies->next;
		free(tmp);
	}
}

void	clean_wall_and_door(t_texture *texture, t_mlx *mlx)
{
	if (texture->no.img)
		mlx_destroy_image(mlx->mlx_connect, texture->no.img);
	if (texture->so.img)
		mlx_destroy_image(mlx->mlx_connect, texture->so.img);
	if (texture->ea.img)
		mlx_destroy_image(mlx->mlx_connect, texture->ea.img);
	if (texture->we.img)
		mlx_destroy_image(mlx->mlx_connect, texture->we.img);
	if (texture->door.img)
		mlx_destroy_image(mlx->mlx_connect, texture->door.img);
}

void	clean_enemies_and_gun(t_mlx *mlx, t_gun *gun, t_enemy_anim *enemy)
{
	int	i;

	i = 0;
	while (i < ENEMY_FRAMES)
	{
		if (enemy->frames[i].img)
		{
			mlx_destroy_image(mlx->mlx_connect, enemy->frames[i].img);
		}
		i++;
	}
	if (enemy->dead_frame.img)
		mlx_destroy_image(mlx->mlx_connect, enemy->dead_frame.img);
	i = 0;
	while (i < GUN_FRAMES)
	{
		if (gun->frames[i].img)
		{
			mlx_destroy_image(mlx->mlx_connect, gun->frames[i].img);
		}
		i++;
	}
}

void	clear_image(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->mlx->size_line * data->window_y)
	{
		data->mlx->img_data[i] = 0;
		i++;
	}
}
