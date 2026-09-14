/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vananiev <vananiev@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/28 12:03:43 by vananiev          #+#    #+#             */
/*   Updated: 2025/05/06 16:32:48 by vananiev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>
// #include <stdio.h>

int	ft_memcmp(const void *s1, const void *s2, size_t n)
{
	size_t			index;
	unsigned char	*pointer1;
	unsigned char	*pointer2;

	index = 0;
	pointer1 = (unsigned char *)s1;
	pointer2 = (unsigned char *)s2;
	while (index < n)
	{
		if (pointer1[index] != pointer2[index])
			return (pointer1[index] - pointer2[index]);
		index++;
	}
	return (0);
}

/*
int	main(void)
{
	char	str1[] = "Compare";
	char	str2[] = "Compfre";
	size_t	num = 5;
	int		result = ft_memcmp(str1, str2, num);
	printf("%d", result);
	return (0);
}
*/
