#include "../../includes/cub3d.h"

static const char	*get_enemy_path(int i)
{
	static const char	*paths[ENEMY_FRAMES] = {
		"./images/enemies/toad1.xpm",
		"./images/enemies/toad2.xpm",
		"./images/enemies/toad3.xpm",
		"./images/enemies/toad4.xpm",
	};

	return (paths[i]);
}

static void	load_one_frame(t_data *data, int i)
{
	t_tex_img	*f;
	const char	*path;

	f = &data->enemy_anim.frames[i];
	path = get_enemy_path(i);
	f->img = mlx_xpm_file_to_image(data->mlx->mlx_connect, (char *)path,
			&f->width, &f->height);
	if (!f->img)
		ft_error_ctx("Texture", (char *)path, data);
	f->addr = mlx_get_data_addr(f->img, &f->bpp, &f->size_line, &f->endian);
}

void	load_enemy_textures(t_data *data)
{
	t_tex_img	*d;
	int			i;

	i = 0;
	while (i < ENEMY_FRAMES)
	{
		load_one_frame(data, i);
		i++;
	}
	d = &data->enemy_anim.dead_frame;
	d->img = mlx_xpm_file_to_image(data->mlx->mlx_connect,
			"./images/enemies/toad4.xpm", &d->width, &d->height);
	if (!d->img)
		ft_error_ctx("Texture", "./images/enemies/toad4.xpm", data);
	d->addr = mlx_get_data_addr(d->img, &d->bpp, &d->size_line, &d->endian);
}
