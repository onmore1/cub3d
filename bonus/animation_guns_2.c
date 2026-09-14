/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   animation_guns_2.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vananiev <vananiev@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/27 12:00:00 by vananiev          #+#    #+#             */
/*   Updated: 2026/05/28 10:50:18 by vananiev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static mlx_image_t	*load_frame(t_game *game, char *path,
		double scale, double x_ratio)
{
	mlx_texture_t	*tex;
	mlx_image_t		*img;
	int				x;

	tex = mlx_load_png(path);
	if (!tex)
		return (perror("loading texture failed"), clean_up(game), NULL);
	img = mlx_texture_to_image(game->mlx, tex);
	mlx_delete_texture(tex);
	if (!img)
		return (perror("converting texture failed"), clean_up(game), NULL);
	mlx_resize_image(img, img->width * scale, img->height * scale);
	x = WIDTH * x_ratio - (int)img->width / 2;
	mlx_image_to_window(game->mlx, img, x, HEIGHT - (int)img->height);
	img->instances[0].enabled = false;
	return (img);
}

static void	setup_gun_counts(t_anim *gun)
{
	gun->ammo[PISTOL] = 50;
	gun->ammo[SHOTGUN] = 30;
	gun->ammo[M_GUN] = 300;
	gun->count[PISTOL] = 5;
	gun->count[SHOTGUN] = 15;
	gun->count[M_GUN] = 4;
	gun->delay[PISTOL] = 60;
	gun->delay[SHOTGUN] = 90;
	gun->delay[M_GUN] = 30;
}

void	pre_render_set(t_game *game, t_anim *anim, int idx, t_render_cfg cfg)
{
	double	scale;
	int		i;

	scale = HEIGHT / cfg.size;
	anim->imgs[idx] = malloc(sizeof(mlx_image_t *) * (anim->count[idx] + 1));
	if (!anim->imgs[idx])
		return ;
	i = 0;
	while (anim->pathes[idx][i])
	{
		anim->imgs[idx][i] = load_frame(game, anim->pathes[idx][i],
				scale, cfg.x_ratio);
		i++;
	}
	anim->imgs[idx][i] = NULL;
}

void	init_gun(t_game *game)
{
	t_anim			*gun;
	t_render_cfg	cfg;

	gun = game->player->gun;
	gun->pathes[PISTOL] = load_pistol_pathes();
	gun->pathes[SHOTGUN] = load_shotgun_pathes();
	gun->pathes[M_GUN] = load_mgun_pathes();
	setup_gun_counts(gun);
	cfg.x_ratio = 1.0 / 1.5;
	cfg.size = 800.0;
	pre_render_set(game, gun, PISTOL, cfg);
	pre_render_set(game, gun, SHOTGUN, cfg);
	cfg.size = 300.0;
	pre_render_set(game, gun, M_GUN, cfg);
	gun->current = 0;
	gun->last_time = 0;
	gun->playing = 0;
	gun->bob_time = 0;
	gun->bob_x = 0;
	gun->bob_y = 0;
	gun->current_weapon = M_GUN;
	gun->imgs[M_GUN][0]->instances[0].enabled = true;
}

void	init_legs(t_game *game)
{
	t_anim			*legs;
	t_render_cfg	cfg;

	legs = game->player->legs;
	legs->pathes[0] = load_legs_pathes();
	legs->count[0] = 5;
	legs->delay[0] = 70;
	cfg.x_ratio = 0.35;
	cfg.size = 400.0;
	pre_render_set(game, legs, 0, cfg);
	legs->current = 0;
	legs->last_time = 0;
	legs->playing = 0;
	legs->bob_time = 0;
	legs->bob_x = 0;
	legs->bob_y = 0;
	legs->current_weapon = 0;
	legs->imgs[0][0]->instances[0].enabled = false;
}
