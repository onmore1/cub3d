/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   audio.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vananiev <vananiev@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/21 11:48:07 by vananiev          #+#    #+#             */
/*   Updated: 2026/06/11 17:59:23 by vananiev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#define MINIAUDIO_IMPLEMENTATION
#include "cub3d.h"

static void	load_sound_buffers_helper(t_audio *audio)
{
	ma_sound_init_from_file(&audio->engine, "assets/audio/cracking.mp3",
		0, NULL, NULL, &audio->hands_cracking);
	ma_sound_init_from_file(&audio->engine, "assets/audio/Dude_augh.wav",
		0, NULL, NULL, &audio->getting_hurt);
	ma_sound_init_from_file(&audio->engine, "assets/audio/step.mp3",
		0, NULL, NULL, &audio->step);
	ma_sound_init_from_file(&audio->engine, "assets/audio/pistol.mp3",
		0, NULL, NULL, &audio->pistol);
	ma_sound_init_from_file(&audio->engine, "assets/audio/kill.mp3",
		0, NULL, NULL, &audio->kill_sound);
	ma_sound_init_from_file(&audio->engine,
		"assets/audio/Bring Me The Horizon - Chelsea Smile.mp3",
		0, NULL, NULL, &audio->song_1);
	ma_sound_init_from_file(&audio->engine, "assets/audio/holy_shit.wav",
		0, NULL, NULL, &audio->announcer_1);
}

static void	load_sound_buffers(t_audio *audio)
{
	ma_sound_init_from_file(&audio->engine, "assets/audio/bizon_01.mp3",
		0, NULL, NULL, &audio->m_gun);
	ma_sound_init_from_file(&audio->engine, "assets/audio/shotgun2.mp3",
		0, NULL, NULL, &audio->shotgun);
	ma_sound_init_from_file(&audio->engine, "assets/audio/whooshe.mp3",
		0, NULL, NULL, &audio->hands_woosh);
	ma_sound_init_from_file(&audio->engine,
		"assets/audio/mm2-equip-weapon.mp3",
		0, NULL, NULL, &audio->equip);
	load_sound_buffers_helper(audio);
}

int	init_sound(t_game *game)
{
	game->audio = malloc(sizeof(t_audio));
	if (!game->audio)
		return (1);
	game->audio->cool_down = 0.5;
	if (ma_engine_init(NULL, &game->audio->engine) != MA_SUCCESS)
		return (free(game->audio), game->audio = NULL, 1);
	load_sound_buffers(game->audio);
	ma_sound_set_volume(&game->audio->song_1, 0.0);
	ma_sound_set_volume(&game->audio->step, 2);
	ma_sound_set_volume(&game->audio->pistol, 2);
	ma_sound_set_volume(&game->audio->shotgun, 0.5);
	ma_sound_set_volume(&game->audio->equip, 3);
	ma_sound_set_volume(&game->audio->hands_cracking, 2);
	ma_sound_set_volume(&game->audio->announcer_1, 1.4);
	return (0);
}

void	play_sound(ma_sound *sound)
{
	ma_sound_seek_to_pcm_frame(sound, 0);
	ma_sound_start(sound);
}
