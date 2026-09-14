/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vananiev <vananiev@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/03 14:57:05 by vananiev          #+#    #+#             */
/*   Updated: 2025/05/07 12:24:50 by vananiev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
// #include <stdio.h>

static int	size_counter(int n)
{
	int	size;

	size = 0;
	if (n <= 0)
		size = 1;
	while (n != 0)
	{
		n /= 10;
		size++;
	}
	return (size);
}

static int	negative_handler(int n, char *ptr)
{
	if (n == -2147483648)
	{
		ptr[0] = '-';
		ptr[1] = '2';
		n = 147483648;
	}
	if (n < 0)
	{
		ptr[0] = '-';
		n = -n;
	}
	return (n);
}

char	*ft_itoa(int n)
{
	int		index;
	int		size;
	char	*ptr;

	index = 0;
	size = size_counter(n);
	ptr = malloc(size + 1);
	if (ptr == NULL)
		return (NULL);
	n = negative_handler(n, ptr);
	if (n == 0)
	{
		ptr[0] = '0';
		ptr[1] = '\0';
		return (ptr);
	}
	index = size - 1;
	while (n > 0)
	{
		ptr[index] = (n % 10) + '0';
		n = n / 10;
		index--;
	}
	ptr[size] = '\0';
	return (ptr);
}

/*
int	main(void)
{
	int		n;
	char	*result;

	n = -2147483648;
	result = ft_itoa(n);
	printf("%s", result);
	return (0);
}
*/
