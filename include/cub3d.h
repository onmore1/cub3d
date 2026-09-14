/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vananiev <vananiev@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/17 17:11:30 by vananiev          #+#    #+#             */
/*   Updated: 2026/06/17 17:48:48 by vananiev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# define WIDTH 1550
# define HEIGHT 900
# define PLAYER_RADIUS 0.1
# define MINIMAP_TILES 23
# define SPRITE_COLS 8
# define SPRITE_ROWS 7
# define ENEMY_SPEED 3.5
# define MAX_PATH_LEN 20

# include "libft.h"
# include "../miniaudio/miniaudio.h"
# include "structs.h"
# include "../MLX42/include/MLX42/MLX42.h"
# include <stddef.h>
# include <fcntl.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <errno.h>
# include <string.h>
# include <math.h>
# include "enums.h"

/* main */
int			main(int ac, char **av);
void		start(t_game *game);
void		loop_hook(void *param);

/* init */
t_game		*init_game(char *filename);
int			init_player(t_game *game);
int			init_colors(t_game *game);
int			init_textures(t_game *game);
int			load_assets(t_game *game);
int			check_input(t_game *game);

/* map */
t_map		*init_map(char *filename);
int			check_map(t_map *map);
int			find_map_start(t_map *map);
int			check_if_map_start(char *line);
int			check_if_valid_line(char *line);
int			is_map_line(char *line, int mode, t_map *map);
int			build_grid(t_map *map, int start);
int			check_if_empty_line(char *line);
int			normalize_grid(t_map *map);
int			get_map_height(char **lines, int start, t_map *map);
int			get_max_width(t_map *map);
int			find_player_start(t_map *map);
int			**allocate_visited(int height, int width);
void		free_visited(int **visited, int height);
int			flood_fill(t_map *map, int **visited, int row, int col);
int			validate_map_enclosed(t_map *map);

/* settings */
int			check_settings(t_game *game);
int			check_if_cardinal_direction(char *line);
int			check_if_surface(char *line);
int			extract_path(char *line, t_game *game, int direction);
int			extract_color(char *line, int *rgb);
int			check_all_settings_present(t_game *game, int mode);
int			check_duplicates(t_game *game);
int			check_player_spawn(t_game *game, int x, int y);

/* player */
void		set_direction(t_player *player, char spawn);
void		update_player(t_game *game);
void		key_hook(mlx_key_data_t keydata, void *param);
void		move_forward(t_game *game, double speed);
void		move_backward(t_game *game, double speed);
void		try_move(t_game *game, double dx, double dy, double speed);
int			is_wall(t_game *game, double x, double y);
void		strafe_left(t_game *game, double speed);
void		strafe_right(t_game *game, double speed);
void		rotate_left(t_game *game);
void		rotate_right(t_game *game);
void		handle_weapon_switch_keys(t_game *game,
				mlx_key_data_t keydata, int pressed);
void		handle_action_flags(t_game *game,
				mlx_key_data_t keydata, int pressed);
void		handle_space_action(t_game *game, mlx_key_data_t keydata);

/* render */
void		render(t_game *game);
void		dda(t_game *game, t_ray *ray);
void		draw_column(t_game *game, t_ray *ray, int x, int bounds[2]);
mlx_image_t	*get_tex(t_game *game, t_ray *ray);
double		get_wall_x(t_game *game, t_ray *ray);
int			get_wall_tex(t_ray *ray);
uint32_t	get_color(int r, int g, int b);
void		init_ray_steps_y(t_game *game, t_ray *ray);
void		init_ray_steps_x(t_game *game, t_ray *ray);
void		dda_step(t_ray *ray);
void		draw_pixel(uint32_t *frame, mlx_image_t *tex,
				int coords[2], int tex_data[2]);
int			get_tex_x(mlx_image_t *tex, double wall_x);

/* mouse */
void		update_mouse(t_game *game);
void		rotate(t_game *game, double angle);

/* utils */
int			malloc_field_dist(t_game *game);
char		*get_next_line(int fd);
char		*ft_substr(char const *s, unsigned int start, size_t len);
char		*ft_strdup(const char *s);
char		**ft_split(char const *s, char c);
int			ft_atoi(const char *buffer);
int			ft_isdigit(int c);
void		free_double_pointer(char **arr);
int			is_digits_only(char *str);
char		**get_lines(char *filename);
void		print_map(t_map *map);
void		print_game(t_game *game);
void		clean_up(t_game *game);
void		free_double_pointer_int(int **arr);
void		free_colors(t_game *game);
void		free_hands(t_game *game);
void		cleanup_hands(t_game *game);
void		free_gun(t_game *game, t_anim *gun, int count);
void		free_map(t_map *map);

/* audio (always compiled, body guarded per function) */
void		step_sound(mlx_key_data_t keydata, t_game *game);
void		cleanup_audio(t_game *game);

/* bonus entry points (real in bonus build, stubbed in mandatory build) */
int			init_enemies(t_game *game);
void		render_enemies(t_game *game);
int			init_sound(t_game *game);
int			init_doors(t_game *game);
t_door		*get_door_at(t_game *game, int x, int y);
int			hit_sliding_door(t_game *game, t_ray *ray, t_door *door);
int			is_door_blocking(t_game *game, double x, double y);

# ifdef BONUS

/* combat */
void		attack(t_game *game, int weapon);
void		update_enemy_animations(t_game *game);
int			check_enemy_action(t_game *game, t_probe *p);
void		play_attack_sound(t_game *game);
int			check_ray_hits_enemy(t_game *game, double x, double y,
				double threshold);

/* init bonus */
void		init_gun(t_game *game);
void		init_legs(t_game *game);
void		init_hands(t_game *game);
void		pre_render_set(t_game *game, t_anim *anim, int idx,
				t_render_cfg cfg);

/* minimap */
void		draw_minimap_border(t_game *game, int tile_size);
void		minimap(t_game *game);
void		draw_cross(t_game *game, int tile_x, int tile_y, int tile_size);
void		draw_player(t_game *game, int tile_size);
void		draw_enemy(t_game *game, int tile_x, int tile_y, int tile_size);
void		draw_tile(t_game *game, int coords[4], int tile_size);

/* gun animations */
void		apply_forward_lean(t_anim *gun, t_game *game, int mode);
void		update_gun_bob(t_game *game);
void		run_anim_gun(t_game *game);
void		run_anim_hands(t_game *game);
void		run_anim_legs(t_game *game);
char		**load_shotgun_pathes(void);
char		**load_pistol_pathes(void);
char		**load_legs_pathes(void);
char		**load_mgun_pathes(void);
char		**load_hands(void);
char		**load_punch_r(void);
char		**load_punch_l(void);
void		switch_weapon(t_game *game);
void		lerp(double target, double *to_increase, double rate);

/* render enemies */
void		draw_enemy_sprite(t_game *game, t_enemy *enemy,
				t_enemy_render *r, int screen_x);

/* ai */
int			already_occupied(t_game *game, int self_i, double x, double y);
void		compute_dist_field(t_game *game);
int			enemy_next_step(t_game *game, int enemy_i, int next[2]);
int			is_walkable_tile(t_game *game, int x, int y);
void		update_enemies(t_game *game);
int			update_single_enemy(t_game *game, int i, double move_dist);
void		can_see_player(t_ray *ray, t_game *game);
void		reset_dist_field(t_game *game);
void		push_neighbors(t_game *game, int curr[2], int *queue, int *tail);
int			update_knockback(t_enemy *enemy, t_game *game, int self_i);
int			handle_spotted_enemy(t_game *game, t_enemy *enemy,
				int i, double move_dist);

/* ui */
void		init_doom_guy(t_game *game);
void		run_guy_anim(t_game *game);
void		update_hp_display(t_game *game);
void		check_if_end(t_game *game);
void		got_hurt(double now, t_doom_guy *doom_guy);
void		got_happy(double now, t_doom_guy *doom_guy);
char		**load_guy_pathes(void);
char		**load_guy_pathes_2(void);
char		**load_guy_pathes_3(void);
char		**load_guy_pathes_4(void);

/* audio bonus */
void		play_sound(ma_sound *sound);

/* doors */
void		update_doors(t_game *game);
void		interact_with_doors(t_game *game);
int			is_door_tile(t_game *game, int x, int y);
void		update_single_door(t_door *door, double delta_time);

# endif

#endif