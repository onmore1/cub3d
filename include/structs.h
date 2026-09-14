/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structs.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vananiev <vananiev@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/23 14:31:22 by vananiev          #+#    #+#             */
/*   Updated: 2026/06/12 15:03:00 by vananiev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCTS_H
# define STRUCTS_H

# include "MLX42/MLX42.h"

typedef struct s_enemy
{
	double		x;
	double		y;
	double		target_x;
	double		target_y;
	double		dist;
	int			hp;
	int			alive;
	int			anim_frame;
	double		anim_timer;
	int			hurt;
	double		hurt_timer;
	int			moving;
	int			close;
	int			attacking;
	int			tried_to_attack;
	int			knockback;
	int			dir_y;
	int			dir_x;
	double		turn_timer;
	double		last_time;
	int			spotted;
	double		spot_time;
	int			marked;
}	t_enemy;

typedef struct s_probe
{
	double		test_x;
	double		test_y;
	double		ray_dist;
	int			weapon;
}	t_probe;

typedef struct s_render_cfg
{
	double	x_ratio;
	double	size;
}	t_render_cfg;

typedef struct s_audio
{
	ma_engine	engine;
	ma_sound	shotgun;
	ma_sound	pistol;
	ma_sound	m_gun;
	ma_sound	hands_punch;
	ma_sound	hands_cracking;
	ma_sound	hands_woosh;
	ma_sound	step;
	ma_sound	kill_sound;
	ma_sound	getting_hurt;
	ma_sound	equip;
	ma_sound	song_1;
	ma_sound	announcer_1;
	double		cool_down;
}	t_audio;

typedef struct s_sprite_draw
{
	struct s_game	*game;
	int				sprite_w;
	int				sprite_h;
	int				frame;
	int				frame_x;
	int				frame_y;
	int				start_x;
	int				start_y;
	int				size;
	int				world_x;
	int				tex_x;
}	t_sprite_draw;

typedef struct s_enemy_render
{
	double		sprite_x;
	double		sprite_y;
	double		inv_det;
	double		transform_x;
	double		transform_y;
}	t_enemy_render;

typedef struct s_texture
{
	char		*path;
	mlx_image_t	*img;
}	t_texture;

typedef struct s_anim
{
	char		**pathes[4];
	mlx_image_t	**imgs[4];
	int			count[4];
	int			ammo[4];
	int			current;
	int			delay[4];
	double		last_time;
	int			playing;
	int			current_weapon;
	double		bob_time;
	double		bob_x;
	double		bob_y;
}	t_anim;

typedef struct s_hands
{
	t_anim			*anim;
	int				side;
	int				just_switched;
	int				mode;
	int				next_punch;
}	t_hands;

typedef struct s_doom_guy
{
	char		**pathes[4];
	int			current_path;
	mlx_image_t	**imgs[4];
	int			count[4];
	int			current;
	int			shown;
	int			delay[3];
	double		last_time;
	int			playing;
	int			face;
	double		bob_time;
	double		bob_x;
	double		bob_y;
}	t_doom_guy;

typedef struct s_map
{
	char		**lines;
	char		**grid;
	int			height;
	int			width;
	int			p_pos;
	char		player_dir;
	int			left;
}	t_map;

typedef struct s_input
{
	int			w;
	int			a;
	int			s;
	int			d;
	int			space;
	int			lshift;
	int			up;
	int			down;
	int			left;
	int			right;
	int			esc;
	int			lbm;
	int			f;
	int			alt;
	int			x;
	int			n1;
	int			n2;
	int			n3;
	int			n4;
}	t_input;

typedef struct s_player
{
	double		pos_x;
	double		pos_y;
	double		dir_x;
	double		dir_y;
	double		plane_x;
	double		plane_y;
	double		pitch;
	double		speed;
	t_anim		*gun;
	t_anim		*legs;
	t_hands		*hands;
	int			health;
}	t_player;

typedef struct s_door
{
	int		x;
	int		y;
	int		orientation;
	double	open_amount;
	double	speed;
	int		is_opening;
	int		is_closing;

}	t_door;

typedef struct s_ray
{
	double		dir_x;
	double		dir_y;
	double		delta_dist_x;
	double		delta_dist_y;
	double		side_dist_x;
	double		side_dist_y;
	double		perp_wall_dist;
	int			map_x;
	int			map_y;
	int			step_x;
	int			step_y;
	int			side;
	t_door		*door;
	int			hit_type;
}	t_ray;

typedef struct s_game
{
	mlx_t		*mlx;
	t_map		*map;
	t_texture	*walls;
	t_player	*player;
	int			**colors;
	mlx_image_t	*frame;
	t_input		input;
	double		last_time;
	double		delta_time;
	mlx_image_t	*minimap;
	t_ray		center_ray;
	mlx_image_t	*enemy_tex;
	t_enemy		*enemies;
	int			enemy_count;
	double		z_buffer[WIDTH * HEIGHT];
	int			**dist_field;
	int			mouse_locked;
	t_anim		*heart_anim;
	mlx_image_t	*hp_text;
	int			last_displayed_hp;
	mlx_image_t	*ammo_text;
	int			last_displayed_ammo;
	t_doom_guy	*doom_guy;
	t_audio		*audio;
	mlx_image_t	*hostiles_text;
	int			last_displayed_enemies;
	int			door_count;
	mlx_image_t	*door_tex;
	t_door		*doors;
}	t_game;

#endif