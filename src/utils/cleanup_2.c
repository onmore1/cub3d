/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleanup_2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vananiev <vananiev@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/27 12:00:00 by vananiev          #+#    #+#             */
/*   Updated: 2026/05/28 17:49:11 by vananiev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	free_colors(t_game *game)
{
	int	i;

	if (!game->colors)
		return ;
	i = 0;
	while (i < 2)
	{
		if (game->colors[i])
			free(game->colors[i]);
		i++;
	}
	free(game->colors);
}

void	cleanup_hands(t_game *game)
{
	if (!game->player->hands)
		return ;
	if (game->player->hands->anim)
		free_gun(game, game->player->hands->anim, 3);
	free(game->player->hands);
}

void	free_map(t_map *map)
{
	if (!map)
		return ;
	if (map->lines)
		free_double_pointer(map->lines);
	if (map->grid)
		free_double_pointer(map->grid);
	free(map);
}

#ifdef BONUS

void	cleanup_audio(t_game *game)
{
	if (!game->audio)
		return ;
	ma_sound_uninit(&game->audio->m_gun);
	ma_sound_uninit(&game->audio->shotgun);
	ma_sound_uninit(&game->audio->hands_woosh);
	ma_sound_uninit(&game->audio->equip);
	ma_sound_uninit(&game->audio->hands_cracking);
	ma_sound_uninit(&game->audio->getting_hurt);
	ma_sound_uninit(&game->audio->step);
	ma_sound_uninit(&game->audio->pistol);
	ma_sound_uninit(&game->audio->kill_sound);
	ma_sound_uninit(&game->audio->song_1);
	ma_sound_uninit(&game->audio->announcer_1);
	ma_engine_uninit(&game->audio->engine);
	free(game->audio);
}

#else

void	cleanup_audio(t_game *game)
{
	(void)game;
}

#endif
