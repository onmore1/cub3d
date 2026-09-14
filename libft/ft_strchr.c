/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vananiev <vananiev@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/09 18:59:22 by vananiev          #+#    #+#             */
/*   Updated: 2025/05/09 19:03:37 by vananiev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>
// #include <stdio.h>
//the cast to unsigned char ensures proper 
//handling of all characters, even those with high ASCII values.
char	*ft_strchr(const char *s, int c)
{
	unsigned char	character;
	unsigned char	*pointer;

	character = (unsigned char)c;
	pointer = (unsigned char *)s;
	while (*pointer)
	{
		if (*pointer == character)
			return ((char *)pointer);
		pointer++;
	}
	if (character == '\0')
		return ((char *)pointer);
	return (NULL);
}

/*
int main()
{
    char str[] = "12A3456789A0";
    int c = 'A'; 
    char *result = ft_strchr(str, c);
    if (result)
        printf("Found: %s\n", result);
    else
        printf("Character not found\n");
    return (0);
}
*/
