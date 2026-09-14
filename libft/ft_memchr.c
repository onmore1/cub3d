/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vananiev <vananiev@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/28 12:44:39 by vananiev          #+#    #+#             */
/*   Updated: 2025/05/10 11:53:16 by vananiev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>
// #include <stdio.h>
//memchr is designed to work with memory (binary data)
void	*ft_memchr(const void *s, int c, size_t n)
{
	unsigned char	*ptr;
	unsigned char	num;
	size_t			index;

	ptr = (unsigned char *)s;
	num = (unsigned char)c;
	index = 0;
	while (index < n)
	{
		if (ptr[index] == num)
			return ((void *)&ptr[index]);
		index++;
	}
	return (NULL);
}

/*
int	main(void)
{
	char	str[] = "12345678";
	size_t	number = 4;
	int		c = '4';
	void	*result = ft_memchr(str, c, number);
	printf("%s", (char *)result);
	return (0);
}
*/
