/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bzero.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpinas <cpinas@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/23 12:45:33 by vananiev          #+#    #+#             */
/*   Updated: 2026/04/20 08:41:54 by cpinas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>
#include "libft.h"

// void	ft_bzero(void *s, size_t n)
// {
// 	unsigned char	*pointer;

// 	pointer = (unsigned char *)s;
// 	ft_memset(s, 0, n);
// }

void	ft_bzero(void *s, size_t n)
{
	ft_memset(s, 0, n);
}

/*
int	main(void)
{
	char	buffer[6] = "123456";
	int		n = 3;

	ft_bzero(buffer, n);
	printf("Result: %s", buffer);
	return (0);
}
*/
