/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ui.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vananiev <vananiev@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/28 13:15:34 by vananiev          #+#    #+#             */
/*   Updated: 2026/06/11 14:00:57 by vananiev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static uint32_t	hp_color(int hp)
{
	if (hp >= 100)
		return (0xFF70FF00);
	if (hp >= 75)
		return (0xFF00FFFF);
	if (hp >= 50)
		return (0xFF0080FF);
	if (hp >= 25)
		return (0xFF0000FF);
	return (0xFF0000FF);
}

static void	tint_text(mlx_image_t *img, uint32_t color)
{
	uint32_t	*pixels;
	int			i;
	int			total;

	pixels = (uint32_t *)img->pixels;
	total = img->width * img->height;
	i = 0;
	while (i < total)
	{
		if (pixels[i] != 0)
			pixels[i] = color;
		i++;
	}
}

static void	make_label(t_game *game, mlx_image_t **dst, char *str, int text)
{
	int		pos[2];

	pos[0] = -1;
	pos[1] = -1;
	if (text == 1)
	{
		pos[0] = WIDTH / 26;
		pos[1] = HEIGHT / 1.25;
	}
	else if (text == 2)
	{
		pos[0] = WIDTH / 2.4;
		pos[1] = HEIGHT / 30;
	}
	else if (text == 3)
	{
		pos[0] = WIDTH / 7;
		pos[1] = HEIGHT / 1.1;
	}
	if (*dst)
		mlx_delete_image(game->mlx, *dst);
	*dst = mlx_put_string(game->mlx, str, pos[0], pos[1]);
	if (!*dst)
		return ;
}

static void	change_looks(t_game *game)
{
	double	s;

	s = HEIGHT / 1200.0;
	mlx_resize_image(game->hostiles_text,
		game->hostiles_text->width * 2.0 * s,
		game->hostiles_text->height * 2.0 * s);
	mlx_resize_image(game->hp_text,
		game->hp_text->width * 3.5 * s,
		game->hp_text->height * 3.5 * s);
	mlx_resize_image(game->ammo_text,
		game->ammo_text->width * 2.5 * s,
		game->ammo_text->height * 2.5 * s);
	tint_text(game->hp_text, hp_color(game->player->health));
	tint_text(game->ammo_text, 0xFFFFFFFF);
	tint_text(game->hostiles_text, 0xFF0000FF);
}

void	update_hp_display(t_game *game)
{
	char	hp[60];
	char	host[60];
	char	ammo[60];
	t_anim	*gun;

	gun = game->player->gun;
	if (game->player->health == game->last_displayed_hp
		&& game->map->left == game->last_displayed_enemies
		&& gun->ammo[gun->current_weapon] == game->last_displayed_ammo)
		return ;
	snprintf(hp, sizeof(hp), "HP:%d", game->player->health);
	snprintf(host, sizeof(host), "Hostiles:%d", game->map->left);
	snprintf(ammo, sizeof(ammo), "Ammo:%d", gun->ammo[gun->current_weapon]);
	make_label(game, &game->hp_text, hp, 1);
	make_label(game, &game->hostiles_text, host, 2);
	make_label(game, &game->ammo_text, ammo, 3);
	change_looks(game);
	game->last_displayed_hp = game->player->health;
	game->last_displayed_enemies = game->map->left;
	game->last_displayed_ammo = gun->ammo[gun->current_weapon];
}
