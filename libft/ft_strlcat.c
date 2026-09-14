/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vananiev <vananiev@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/05 13:17:51 by vananiev          #+#    #+#             */
/*   Updated: 2025/05/08 19:26:43 by vananiev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>
// #include <stdio.h>
//1.Add src to the end of dst
//2.dont go over the size
//3.Always end with '\0'
//4.return the dst + src
//(amount of how much bytes from src could be copied if dst had infinite memory)
//5.size = max amount of bytes we dst should have
size_t	ft_strlcat(char *dst, const char *src, size_t size)
{
	size_t	dst_len;
	size_t	src_len;
	size_t	index;

	dst_len = 0;
	while (dst[dst_len] && dst_len < size)
		dst_len++;
	src_len = 0;
	while (src[src_len])
		src_len++;
	if (dst_len == size)
		return (size + src_len);
	index = 0;
	while (src[index] && (dst_len + index + 1) < size)
	{
		dst[dst_len + index] = src[index];
		index++;
	}
	dst[dst_len + index] = '\0';
	return (dst_len + src_len);
}

/* int main() */
/* { */
/*     char dst[10] = "123"; */
/*     const char *src = "4567"; */
/*     size_t size = 6; */
/*     int result = ft_strlcat(dst, src, size); */
/* } */
