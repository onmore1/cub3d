/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vananiev <vananiev@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/30 12:15:34 by vananiev          #+#    #+#             */
/*   Updated: 2025/05/10 14:02:46 by vananiev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <limits.h>
#include "libft.h"

void	*ft_calloc(size_t nmemb, size_t size)
{
	size_t	totalbytes;
	void	*ptr;

	if (nmemb == 0 || size == 0)
		totalbytes = 0;
	else if (size != 0 && nmemb > __SIZE_MAX__ / size)
		return (NULL);
	else
		totalbytes = nmemb * size;
	ptr = malloc(totalbytes);
	if (ptr == NULL)
		return (NULL);
	ft_bzero(ptr, totalbytes);
	return (ptr);
}
/*
int	main(void)
{
	int		nmemb = 5;
	size_t	size = sizeof(int);
	int		*result;

	result = (int *)ft_calloc(nmemb, size);

	int index = 0;

	while (index < nmemb)
	{
		printf("%d\n", result[index]);
		index++;
	}
	return (0);
}
*/
