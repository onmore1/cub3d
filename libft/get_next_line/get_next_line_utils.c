/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vananiev <vananiev@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/24 11:44:21 by vananiev          #+#    #+#             */
/*   Updated: 2025/09/08 13:52:52 by vananiev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*ft_strjoin_helper(char *joined, const char *s, const char *s2)
{
	size_t	index;
	size_t	len1;
	size_t	len2;

	index = 0;
	len1 = ft_strlen(s);
	len2 = ft_strlen(s2);
	while (index < len1)
	{
		joined[index] = s[index];
		index++;
	}
	index = 0;
	while (index < len2)
	{
		joined[len1 + index] = s2[index];
		index++;
	}
	joined[len1 + len2] = '\0';
	return (joined);
}

char	*ft_strjoin_free(char *leftover, char *buffer)
{
	char	*res;

	if (!leftover && !buffer)
		return (NULL);
	res = ft_strjoin(leftover, buffer);
	if (!res)
	{
		free(leftover);
		return (NULL);
	}
	free(leftover);
	return (res);
}
