/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clear.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fducrot <fducrot@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 11/05/2026 12:07:29 by fducrot           #+#    #+#             */
/*   Updated: 11/05/2026 12:07:29 by fducrot          ###   ########.ch       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"
#include <stdlib.h>

static void	free_linked_map(t_linked_map *linked_map)
{
	t_linked_map	*temp;

	while (linked_map)
	{
		temp = linked_map;
		linked_map = linked_map->next;
		if (temp->line)
			free(temp->line);
		free(temp);
	}
}

static void	free_texture_struct(t_texture *texture)
{
	if (texture)
	{
		if (texture->no_path)
			free(texture->no_path);
		if (texture->so_path)
			free(texture->so_path);
		if (texture->we_path)
			free(texture->we_path);
		if (texture->ea_path)
			free(texture->ea_path);
		if (texture->floor)
			ft_free_2d_array(texture->floor);
		if (texture->roof)
			ft_free_2d_array(texture->roof);
		free(texture);
	}
}

static void	free_map_struct(t_map *map)
{
	if (map)
	{
		if (map->map)
			ft_free_2d_array(map->map);
		if (map->map_copy)
			ft_free_2d_array(map->map_copy);
		if (map->line_len)
			free(map->line_len);
		free(map);
	}
}

static void	destroy_images(t_data *data, t_texture *texture, t_mlx *mlx)
{
	if (!texture)
		return ;
	if (mlx && mlx->mlx_connect)
	{
		mlx_mouse_show(mlx->mlx_connect, mlx->mlx_window);
		clean_wall_and_door(texture, mlx);
		clean_enemies_and_gun(mlx, &data->gun, &data->enemy_anim);
		if (mlx->img)
			mlx_destroy_image(mlx->mlx_connect, mlx->img);
		if (mlx->mlx_window)
			mlx_destroy_window(mlx->mlx_connect, mlx->mlx_window);
		mlx_destroy_display(mlx->mlx_connect);
		free(mlx->mlx_connect);
	}
	if (mlx)
		free(mlx);
}

/**
 * @brief Frees all allocated resources and resets the main data structure.
 *
 * Closes any open file descriptors, frees the map, textures,
 * and linked map, then zeroes out the data structure with ft_memset.
 *
 * @param data  Pointer to the main structure holding all program resources.
 */
void	clean_all(t_data *data)
{
	free(data->draw);
	free(data->raycast);
	free(data->threads);
	if (data->z_buffer)
		free(data->z_buffer);
	if (data->fd)
		close(data->fd);
	clean_mini_map(data);
	free_enemies(data->enemies);
	destroy_images(data, data->texture, data->mlx);
	free_map_struct(data->map);
	free_texture_struct(data->texture);
	free_linked_map(data->linked_map);
	ft_memset(data, 0, sizeof(t_data));
	return ;
}
