/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vananiev <vananiev@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/05 12:50:12 by vananiev          #+#    #+#             */
/*   Updated: 2025/05/08 19:15:09 by vananiev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>
// #include <stdio.h>
//should return the src len.
//We use this function to see how many of
//chars was supposed to be copied if there was enough
//space.And check if the the whole str fitted into the
//dst or if some of it was trimmed.
//and also copy thing from src to dst.
size_t	ft_strlcpy(char *dst, const char *src, size_t size)
{
	size_t	index;
	size_t	src_len;

	src_len = 0;
	index = 0;
	while (src[src_len])
		src_len++;
	if (size > 0)
	{
		while (src[index] && index < size - 1)
		{
			dst[index] = src[index];
			index++;
		}
		dst[index] = '\0';
	}
	return (src_len);
}

//  int	main(void) 
//  { 
// 	char	src[] = "1234567"; 
// 	char	dst[10]; 
// 	size_t	size = 5; 
// 	size_t	res = ft_strlcpy(dst, src, size); 
// 	printf("%zu\n", res); 
// 	return (0); 
//  } 
