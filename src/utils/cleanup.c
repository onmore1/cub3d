/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleanup.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vananiev <vananiev@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/30 16:24:25 by vananiev          #+#    #+#             */
/*   Updated: 2026/05/29 12:02:35 by vananiev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	free_walls(t_game *game)
{
	int	i;

	if (!game->walls)
		return ;
	i = 0;
	while (i < 4)
	{
		if (game->walls[i].path)
			free(game->walls[i].path);
		if (game->walls[i].img && game->mlx)
			mlx_delete_image(game->mlx, game->walls[i].img);
		i++;
	}
	free(game->walls);
}

void	free_gun(t_game *game, t_anim *gun, int count)
{
	int	i;
	int	w;

	if (!gun)
		return ;
	w = 0;
	while (w < count)
	{
		i = 0;
		while (i < gun->count[w])
		{
			mlx_delete_image(game->mlx, gun->imgs[w][i]);
			i++;
		}
		free(gun->imgs[w]);
		w++;
	}
	free(gun);
}

static void	free_face(t_game *game, t_doom_guy *guy)
{
	int	i;
	int	set;

	if (!guy)
		return ;
	set = 0;
	while (set < 4)
	{
		if (guy->imgs[set])
		{
			i = 0;
			while (i < guy->count[set])
			{
				if (guy->imgs[set][i])
					mlx_delete_image(game->mlx, guy->imgs[set][i]);
				i++;
			}
			free(guy->imgs[set]);
		}
		set++;
	}
	free(guy);
}

static void	clean_up_helper(t_game *game)
{
	if (game->enemies)
		free(game->enemies);
	if (game->dist_field)
		free_double_pointer_int(game->dist_field);
	if (game->doom_guy)
		free_face(game, game->doom_guy);
	if (game->doors)
		free(game->doors);
	if (game->hp_text && game->mlx)
		mlx_delete_image(game->mlx, game->hp_text);
}

void	clean_up(t_game *game)
{
	if (!game)
		return ;
	free_colors(game);
	free_walls(game);
	free_map(game->map);
	if (game->player)
	{
		if (game->player->legs)
			free_gun(game, game->player->legs, 1);
		cleanup_hands(game);
		free_gun(game, game->player->gun, 3);
		free(game->player);
		clean_up_helper(game);
	}
	if (game->mlx)
		mlx_terminate(game->mlx);
	if (game->audio)
		cleanup_audio(game);
	free(game);
}
