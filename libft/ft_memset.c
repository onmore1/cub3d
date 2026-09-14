/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vananiev <vananiev@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/23 17:03:03 by vananiev          #+#    #+#             */
/*   Updated: 2025/05/06 16:33:34 by vananiev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>
// #include <stdio.h>

void	*ft_memset(void *s, int c, size_t n)
{
	unsigned char	*pointer;
	size_t			index;

	pointer = (unsigned char *)s;
	index = 0;
	while (index < n)
	{
		pointer[index] = (unsigned char)c;
		index++;
	}
	return (s);
}

/*
int	main(void)
{
	char	buffer[20] = "Hello, world!";
	int		c = 'X';
	size_t	number = 5;

	char	*result = ft_memset(buffer, c, number);
	printf("%s\n", result);
	return (0);
}
*/
