/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gun.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fducrot <fducrot@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 11/05/2026 10:47:57 by fducrot           #+#    #+#             */
/*   Updated: 11/05/2026 10:47:57 by fducrot          ###   ########.ch       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

static const char	*get_gun_path(int i)
{
	static const char	*paths[ENEMY_FRAMES] = {
		"./images/guns/gun_neutre.xpm",
		"./images/guns/gun-shoot-1.xpm",
		"./images/guns/gun-shoot-2.xpm",
	};

	return (paths[i]);
}

static void	load_one_gun_frame(t_data *data, int i)
{
	const char	*path;
	void		*conn;
	t_tex_img	*f;

	path = get_gun_path(i);
	conn = data->mlx->mlx_connect;
	f = &data->gun.frames[i];
	f->img = mlx_xpm_file_to_image(conn, (char *)path, &f->width, &f->height);
	if (!f->img)
		ft_error_ctx("Texture", (char *)path, data);
	f->addr = mlx_get_data_addr(f->img, &f->bpp, &f->size_line, &f->endian);
}

void	load_gun_textures(t_data *data)
{
	int	i;

	i = 0;
	while (i < GUN_FRAMES)
	{
		load_one_gun_frame(data, i);
		i++;
	}
}
