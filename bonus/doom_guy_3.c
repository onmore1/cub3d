/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   doom_guy_3.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vananiev <vananiev@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/27 12:00:00 by vananiev          #+#    #+#             */
/*   Updated: 2026/05/28 11:04:49 by vananiev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

char	**load_guy_pathes(void)
{
	static char	*pathes[] = {
		"assets/ui/heart_anim/row-1-column-4.png",
		"assets/ui/heart_anim/row-1-column-5.png",
		"assets/ui/heart_anim/row-1-column-6.png",
		"assets/ui/heart_anim/row-1-column-3.png",
		"assets/ui/heart_anim/row-1-column-1.png",
		NULL
	};

	return (pathes);
}

char	**load_guy_pathes_2(void)
{
	static char	*pathes[] = {
		"assets/ui/heart_anim/row-3-column-4.png",
		"assets/ui/heart_anim/row-3-column-5.png",
		"assets/ui/heart_anim/row-3-column-6.png",
		"assets/ui/heart_anim/row-3-column-3.png",
		"assets/ui/heart_anim/row-3-column-1.png",
		NULL
	};

	return (pathes);
}

char	**load_guy_pathes_3(void)
{
	static char	*pathes[] = {
		"assets/ui/heart_anim/row-4-column-4.png",
		"assets/ui/heart_anim/row-4-column-5.png",
		"assets/ui/heart_anim/row-4-column-6.png",
		"assets/ui/heart_anim/row-4-column-3.png",
		"assets/ui/heart_anim/row-4-column-1.png",
		NULL
	};

	return (pathes);
}

char	**load_guy_pathes_4(void)
{
	static char	*pathes[] = {
		"assets/ui/heart_anim/row-5-column-4.png",
		"assets/ui/heart_anim/row-5-column-5.png",
		"assets/ui/heart_anim/row-5-column-6.png",
		"assets/ui/heart_anim/row-5-column-3.png",
		"assets/ui/heart_anim/row-5-column-1.png",
		NULL
	};

	return (pathes);
}
