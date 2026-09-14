/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vananiev <vananiev@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/28 14:33:02 by vananiev          #+#    #+#             */
/*   Updated: 2025/05/07 18:30:17 by vananiev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>
// #include <stdio.h>

char	*ft_strrchr(const char *s, int c)
{
	int				index;
	int				place;
	unsigned char	*pointer;
	unsigned char	character;

	character = (unsigned char)c;
	pointer = (unsigned char *)s;
	index = 0;
	place = -1;
	while (pointer[index])
	{
		if (pointer[index] == character)
			place = index;
		index++;
	}
	if (character == '\0')
		return ((char *)&pointer[index]);
	if (place >= 0)
		return ((char *)&pointer[place]);
	return (NULL);
}

/*
int main()
{
    char str[] = "12A3456789A0";
    int c = 'A';
    char *result = ft_strrchr(str, c);
    printf("%s", result);
    return 0;
}
*/
