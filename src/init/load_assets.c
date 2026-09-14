/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load_assets.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vananiev <vananiev@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/30 14:13:52 by vananiev          #+#    #+#             */
/*   Updated: 2026/06/11 15:00:00 by vananiev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	load_wall_textures(t_game *game)
{
	mlx_texture_t	*tmp;
	int				i;

	i = 0;
	while (i < 4)
	{
		tmp = mlx_load_png(game->walls[i].path);
		if (!tmp)
			return (printf("Error: failed to load texture %s\n",
					game->walls[i].path), 1);
		game->walls[i].img = mlx_texture_to_image(game->mlx, tmp);
		mlx_delete_texture(tmp);
		if (!game->walls[i].img)
			return (printf("Error: failed to convert texture %s\n",
					game->walls[i].path), 1);
		i++;
	}
	return (0);
}

#ifdef BONUS

static int	load_bonus_assets(t_game *game)
{
	mlx_texture_t	*door_tmp;
	mlx_texture_t	*enemy_tmp;

	door_tmp = mlx_load_png("./assets/doors/door_1.png");
	if (!door_tmp)
		return (printf("Error: failed to load door texture\n"), 1);
	game->door_tex = mlx_texture_to_image(game->mlx, door_tmp);
	mlx_delete_texture(door_tmp);
	if (!game->door_tex)
		return (printf("Error: failed door texture conversion\n"), 1);
	enemy_tmp = mlx_load_png("./assets/enemy/enemy_texture.png");
	if (!enemy_tmp)
		return (printf("Error: failed to load enemy texture\n"), 1);
	game->enemy_tex = mlx_texture_to_image(game->mlx, enemy_tmp);
	mlx_delete_texture(enemy_tmp);
	if (!game->enemy_tex)
		return (printf("Error: failed enemy texture conversion\n"), 1);
	game->player->gun = malloc(sizeof(t_anim));
	game->player->legs = malloc(sizeof(t_anim));
	game->doom_guy = malloc(sizeof(t_doom_guy));
	if (!game->player->gun || !game->doom_guy || !game->player->legs)
		return (printf("error mallocing gun or doom guy "), 1);
	return (0);
}

#else

static int	load_bonus_assets(t_game *game)
{
	(void)game;
	return (0);
}

#endif

int	load_assets(t_game *game)
{
	if (load_wall_textures(game))
		return (1);
	if (load_bonus_assets(game))
		return (1);
	return (0);
}
