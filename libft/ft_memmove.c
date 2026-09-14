/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vananiev <vananiev@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/05 14:10:30 by vananiev          #+#    #+#             */
/*   Updated: 2025/05/08 20:01:07 by vananiev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>
// #include <stdio.h>
void	*overlap(char *dst, const char *s, size_t n)
{
	while (n > 0)
	{
		n--;
		dst[n] = s[n];
	}
	return (dst);
}

void	*ft_memmove(void *dest, const void *src, size_t n)
{
	char		*dst;
	const char	*s;
	size_t		index;

	dst = dest;
	s = src;
	if (dst == s || n == 0)
		return (dest);
	if (dst < s)
	{
		index = 0;
		while (index < n)
		{
			dst[index] = s[index];
			index++;
		}
	}
	else if (dst > s)
		overlap(dst, s, n);
	return (dest);
}

// int	main(void)
// {
// 	char	s[6] = "No";

// 	ft_memmove(s + 1, s, 1);  // Moves "N" to "o"
// 	printf("%s", s);  // Expected output: "oNo"
// 	return (0);
// }
