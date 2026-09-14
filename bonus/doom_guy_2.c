/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   doom_guy_2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vananiev <vananiev@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/27 12:00:00 by vananiev          #+#    #+#             */
/*   Updated: 2026/06/11 13:36:37 by vananiev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	advance_default_anim(t_doom_guy *doom_guy, double now)
{
	mlx_image_t	**set;
	int			prev;

	if ((now - doom_guy->last_time) * 1000 < doom_guy->delay[0])
		return ;
	set = doom_guy->imgs[doom_guy->current_path];
	prev = doom_guy->current;
	doom_guy->current++;
	set[prev]->instances[0].enabled = false;
	if (doom_guy->current >= 3)
		doom_guy->current = 0;
	set[doom_guy->current]->instances[0].enabled = true;
	doom_guy->last_time = now;
}

void	run_guy_anim(t_game *game)
{
	t_doom_guy	*doom_guy;
	double		now;

	doom_guy = game->doom_guy;
	now = mlx_get_time();
	if (doom_guy->face == HURT)
	{
		got_hurt(now, doom_guy);
		return ;
	}
	else if (doom_guy->face == HAPPY)
	{
		got_happy(now, doom_guy);
		return ;
	}
	advance_default_anim(doom_guy, now);
}

static void	load_single_guy_set(t_game *game, t_doom_guy *doom_guy,
		int i2, double ratio)
{
	mlx_texture_t	*tex;
	mlx_image_t		*img;
	int				i;

	doom_guy->imgs[i2] = malloc(sizeof(mlx_image_t *)
			* (doom_guy->count[i2] + 1));
	if (!doom_guy->imgs[i2])
		return ;
	i = 0;
	while (doom_guy->pathes[i2][i])
	{
		tex = mlx_load_png(doom_guy->pathes[i2][i]);
		if (!tex)
			return (perror("loading texture failed"), clean_up(game));
		img = mlx_texture_to_image(game->mlx, tex);
		mlx_delete_texture(tex);
		if (!img)
			return (perror("converting texture failed"), clean_up(game));
		mlx_resize_image(img, img->width * ratio, img->height * ratio);
		mlx_image_to_window(game->mlx, img, WIDTH / 40, HEIGHT / 1.14);
		img->instances[0].enabled = false;
		doom_guy->imgs[i2][i] = img;
		i++;
	}
	doom_guy->imgs[i2][i] = NULL;
}

static void	pre_render_guy(t_game *game)
{
	t_doom_guy	*doom_guy;
	int			i2;

	doom_guy = game->doom_guy;
	i2 = 0;
	while (i2 < 4)
	{
		load_single_guy_set(game, doom_guy, i2, HEIGHT / 800.0);
		i2++;
	}
}

void	init_doom_guy(t_game *game)
{
	t_doom_guy	*doom_guy;

	doom_guy = game->doom_guy;
	doom_guy->pathes[0] = load_guy_pathes();
	doom_guy->pathes[1] = load_guy_pathes_2();
	doom_guy->pathes[2] = load_guy_pathes_3();
	doom_guy->pathes[3] = load_guy_pathes_4();
	doom_guy->count[0] = 5;
	doom_guy->count[1] = 5;
	doom_guy->count[2] = 5;
	doom_guy->count[3] = 5;
	doom_guy->delay[0] = 1000;
	doom_guy->delay[1] = 1000;
	doom_guy->delay[2] = 800;
	pre_render_guy(game);
	doom_guy->current = 0;
	doom_guy->last_time = 0;
	doom_guy->playing = 1;
	doom_guy->bob_time = 0;
	doom_guy->bob_x = 0;
	doom_guy->bob_y = 0;
	doom_guy->face = DEFAULT;
	doom_guy->current_path = 0;
	doom_guy->imgs[0][0]->instances[0].enabled = true;
}
