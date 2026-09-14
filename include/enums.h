/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   enums.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vananiev <vananiev@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/30 15:33:17 by vananiev          #+#    #+#             */
/*   Updated: 2026/05/28 12:48:54 by vananiev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ENUMS_H
# define ENUMS_H

typedef enum e_hit_type
{
	HIT_NONE,
	HIT_WALL,
	HIT_DOOR
}	t_hit_type;

typedef enum e_weapon
{
	PISTOL,
	SHOTGUN,
	M_GUN,
	LEGS,
	HANDS
}	t_weapon;

typedef enum e_direction
{
	NORTH,
	SOUTH,
	EAST,
	WEST
}	t_direction;

typedef enum e_hand_mode
{
	HAND_IDLE,
	HAND_LEFT,
	HAND_RIGHT
}	t_hand_mode;

typedef enum e_surface
{
	FLOOR,
	CEILING
}	t_surface;

typedef enum e_rgb
{
	RED,
	GREEN,
	BLUE
}	t_rgb;

enum e_coords
{
	X,
	Y
};

enum e_tex_data
{
	TEX_X,
	TEX_Y
};

enum e_draw_data
{
	START,
	END,
	TEX_X_POS
};

enum e_wall_params
{
	DRAW_START,
	TEX_X_PARAM,
	PERP_DIST,
	DRAW_END
};

enum e_ai_coords
{
	NEIGHBOR_X,
	NEIGHBOR_Y,
	CURRENT_X,
	CURRENT_Y
};

enum e_ai_pos
{
	POS_X,
	POS_Y
};

enum e_face
{
	DEFAULT,
	HAPPY,
	HURT
};

typedef enum e_action
{
	ACTION_SHOOT,
	ACTION_KICK
}	t_action;

#endif