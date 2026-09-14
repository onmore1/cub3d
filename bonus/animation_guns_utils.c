/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   animation_guns_utils.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vananiev <vananiev@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/21 16:50:38 by vananiev          #+#    #+#             */
/*   Updated: 2026/05/28 11:05:04 by vananiev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

char	**load_pistol_pathes(void)
{
	static char	*pistol_paths[] = {
		"assets/pistol/pxArt (16).png", "assets/pistol/pxArt (17).png",
		"assets/pistol/pxArt (18).png", "assets/pistol/pxArt (19).png",
		"assets/pistol/pxArt (20).png", NULL
	};

	return (pistol_paths);
}

char	**load_shotgun_pathes(void)
{
	static char	*pathes[] = {
		"assets/shotgun/pxArt (27).png", "assets/shotgun/pxArt (28).png",
		"assets/shotgun/pxArt (29).png", "assets/shotgun/pxArt (30).png",
		"assets/shotgun/pxArt (31).png", "assets/shotgun/pxArt (6).png",
		"assets/shotgun/pxArt (7) (1).png", "assets/shotgun/pxArt (8).png",
		"assets/shotgun/pxArt (9).png", "assets/shotgun/pxArt (10).png",
		"assets/shotgun/pxArt (11).png", "assets/shotgun/pxArt (12).png",
		"assets/shotgun/pxArt (13).png", "assets/shotgun/pxArt (14).png",
		"assets/shotgun/pxArt (27) (copy).png", NULL
	};

	return (pathes);
}

char	**load_legs_pathes(void)
{
	static char	*pathes[] = {
		"assets/mellee/legs/pxArt (21).png",
		"assets/mellee/legs/pxArt (22).png",
		"assets/mellee/legs/pxArt (23).png",
		"assets/mellee/legs/pxArt (24).png",
		"assets/mellee/legs/pxArt (25).png",
		NULL
	};

	return (pathes);
}

char	**load_mgun_pathes(void)
{
	static char	*pathes[] = {
		"assets/m_gun/New Project.png",
		"assets/m_gun/New Project (1).png",
		"assets/m_gun/New Project (2).png",
		"assets/m_gun/New Project (3).png",
		NULL
	};

	return (pathes);
}

char	**load_hands(void)
{
	static char	*pathes[] = {
		"assets/mellee/hands/PUNSH0.png",
		"assets/mellee/hands/FISAA0.png",
		"assets/mellee/hands/FISAB0.png",
		"assets/mellee/hands/FISAC0.png",
		"assets/mellee/hands/FISAD0.png",
		"assets/mellee/hands/FISAE0.png",
		"assets/mellee/hands/FISAF0.png",
		"assets/mellee/hands/FISAG0.png",
		"assets/mellee/hands/PONGA0.png",
		NULL
	};

	return (pathes);
}
