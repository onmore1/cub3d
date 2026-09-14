/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vananiev <vananiev@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/24 12:50:47 by vananiev          #+#    #+#             */
/*   Updated: 2025/05/07 17:28:44 by vananiev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>
// #include <stdio.h>

void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	unsigned char	*pointer;
	unsigned char	*pointer2;
	size_t			index;

	pointer = (unsigned char *)dest;
	pointer2 = (unsigned char *)src;
	index = 0;
	if (pointer == NULL && pointer2 == NULL)
		return (NULL);
	while (index < n)
	{
		pointer[index] = pointer2[index];
		index++;
	}
	return (dest);
}

/*
int	main(void)
{
	char	dest[20];
	char	src[] = "ABC123 EFG456";
	int		n = 6;
	ft_memcpy(dest, src, n);
	printf("%s", dest);
	return (0);
}
*/
