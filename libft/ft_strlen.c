/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlen.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vananiev <vananiev@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/22 15:05:13 by vananiev          #+#    #+#             */
/*   Updated: 2025/05/07 12:02:49 by vananiev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>

int	ft_strlen(char *buffer)
{
	int	x;

	x = 0;
	while (buffer[x] != '\0')
	{
		x++;
	}
	return (x);
}

/*
int	main(void)
{
	char	buffer[] = "Count me";
	int		result;

	result = ft_strlen(buffer);
	printf("%d", result);
	return (0);
}
*/
